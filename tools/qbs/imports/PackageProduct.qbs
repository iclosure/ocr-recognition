import qbs
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import qbs.Environment

Product {
    type: [ 'setup.package' ]

    Depends { name: 'cpp' }
    Depends { name: 'Qt.core'; cpp.link: false }
    Depends { name: 'Qt.qml'; cpp.link: false }
    Depends { name: 'pack.data'; cpp.link: false }
    Depends { name: 'pack.meta'; cpp.link: false }

    readonly property path qtdir: Qt.core.binPath + '/..'
    readonly property path projectDir: FileInfo.joinPaths(project.projectInstallRoot, project.projectName)
    readonly property string domain: FileInfo.relativePath(project.packagesPath, sourceDirectory).replace(/\//g, '.')
    readonly property string installPrefix: FileInfo.joinPaths(project.setupDir, 'packages')
    readonly property string installDir: FileInfo.joinPaths(domain, 'data')
    readonly property path dataSourcePath: pack.data.sourcePath
    readonly property path dataTargetPath: pack.data.targetPath
    readonly property path metaSourcePath: pack.meta.sourcePath
    readonly property path metaTargetPath: pack.meta.targetPath
    readonly property string dataInstallPrefix: pack.data.installPrefix
    readonly property string metaInstallPrefix: pack.meta.installPrefix
    //
    property bool replaceMeta: true
    property string projectName: project.projectName
    property string appName: projectName + project.variantSuffix
    property string displayName: project.projectDisplayName

    Group {
        fileTagsFilter: [ 'data.bin' ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
    }

    Group {
        fileTagsFilter: [ 'data.plugins' ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'plugins'
        qbs.installSourceBase: Qt.core.pluginPath
    }

    Group {
        fileTagsFilter: [ 'data.qml' ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'qml'
        qbs.installSourceBase: Qt.qml.qmlPath
    }

    Rule {
        condition: replaceMeta
        inputs: [ 'meta.in' ]
        Artifact {
            fileTags: [ 'meta.out' ]
            filePath: FileInfo.joinPaths(product.metaTargetPath, FileInfo.relativePath(
                                             product.metaSourcePath, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.highlight = 'gencode'
            cmd.description = 'replacing content of \'' + input.fileName + '\' and moving to packages...'
            cmd.sourceCode = function() {
                var fileName = input.fileName
                if (fileName.endsWith('.js') || fileName.endsWith('.xml')) {
                    var source = new TextFile(input.filePath, TextFile.ReadOnly)
                    var target = new TextFile(output.filePath, TextFile.WriteOnly)
                    var content = source.readAll()
                    source.close()
                    // replace @VERSION@
                    content = content.replace(/@VERSION@/g, product.version)
                    // replace @PROJECT_NAME@
                    content = content.replace(/@PROJECT@/g, product.projectName)
                    // replace @APPNAME@
                    content = content.replace(/@APPNAME@/g, product.appName)
                    // replace @PROJECT_DISPLAY_NAME@
                    content = content.replace(/@PROJECT_DISPLAY_NAME@/g, product.displayName)
                    //
                    target.write(content)
                    target.close()
                }
            }
            return [ cmd ]
        }
    }
}
