import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import tools.EnvUtils

Product {
    name: 'JFrameworkInstall'
    type: [ 'header.out', 'library.out' ]

    condition: !qbs.targetOS.contains('android')

    Depends { name: 'cpp' }

    readonly property path jframeDir: EnvUtils.jframeDir(project)
    readonly property bool jframeExists: !!jframeDir
    readonly property bool isSelfDirectory: jframeDir == project.sourceDirectory
    property stringList modules: []
    property stringList modulesExt: []
    property bool installJFrameworkdir: false
    property string moduleInstallDir: 'bin'

    // modules - headers

    Group {
        id: modules_headers
        name: 'modules_headers'
        condition: jframeExists && !isSelfDirectory
        prefix: jframeDir + '/include/'
        files: {
            var files = []
            modules.forEach(function(item){
                files.push(item + '/**/*')
            })
            return files
        }
        fileTags: [ name + '.in' ]
    }

    Rule {
        condition: jframeExists && !isSelfDirectory
        inputs: modules_headers.fileTags
        Artifact {
            fileTags: [ 'header.out' ]
            filePath: FileInfo.joinPaths(project.sourceDirectory,
                                         FileInfo.relativePath(product.jframeDir, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'coping ' + input.fileName
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [ cmd ]
        }
    }

    // modules - library

    Group {
        id: modules_dynamic
        name: 'modules_dynamic'
        condition: jframeExists
        prefix: jframeDir + '/lib/' + project.archDir + '/'
        files: {
            var files = []
            modules.forEach(function(item){
                files.push(EnvUtils.libPrefix(qbs) + item + EnvUtils.dylibSuffix(qbs) + '*')
            })
            return files
        }
        fileTags: [ name + '.in' ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: moduleInstallDir
    }

    Group {
        id: modules_library
        name: 'modules_library'
        condition: jframeExists && !isSelfDirectory
        prefix: modules_dynamic.prefix
        files: {
            var files = []
            if (qbs.targetOS.contains('windows')) {
                modules.forEach(function(item){
                    files.push(item + '*.lib')
                    files.push(item + '*.dll')
                })
            } else {
                modules.forEach(function(item){
                    files.push(EnvUtils.libPrefix(qbs) + item + '*' + EnvUtils.dylibExtension(qbs))
                })
            }
            return files
        }
        excludeFiles: [ EnvUtils.incDylibFuzzy(qbs) ]
        fileTags: [ name + '.in' ]
    }

    Rule {
        condition: jframeExists && !isSelfDirectory
        inputs: modules_dynamic.fileTags.concat(modules_library.fileTags)
        Artifact {
            fileTags: [ 'library.out' ]
            filePath: FileInfo.joinPaths(project.sourceDirectory,
                                         FileInfo.relativePath(product.jframeDir, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'coping ' + input.fileName
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [ cmd ]
        }
    }
}
