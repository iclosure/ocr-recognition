import qbs
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import qbs.Environment
import tools.EnvUtils

Product {
    id: root
    name: 'QtInstall'
    type: ['qt.conf.out']

    condition: !qbs.targetOS.contains('android')

    property string installDir: 'bin'
    property bool generateQtConf: true
    property bool useOpenGL: true
    property stringList module3rdpart: {
        var items = [ 'd3dcompiler*.dll' ]
        if (useOpenGL) {
            items.push('opengl32*.dll')
            items.push(EnvUtils.incDylibFuzzy(qbs, false, 'lib*'))
        }
        return items
    }
    property stringList moduleGeneral: [
        'Core', 'Gui', 'Widgets', 'DBus'
    ]
    property stringList modulePlugins: [
        'bearer', 'iconengines', 'imageformats', 'platforms', 'printsupport', 'translations',
        'styles'
    ]
    property stringList moduleQml: []
    property stringList moduleResources: []
    property stringList moduleTranslations: []
    property bool installWebEngineProcess: false

    readonly property path qtCoreBinPath: {
        if (qbs.targetOS.contains('linux')) {
            return Qt.core.libPath
        } else if (qbs.targetOS.contains('darwin')) {
            return Qt.core.libPath
        } else {
            return Qt.core.binPath
        }
    }

    Depends { name: 'cpp' }
    Depends { name: 'Qt.core'; cpp.link: false }
    Depends { name: 'Qt.qml'; cpp.link: false }

    // 3rdpart

    Group {
        name: '3rdpart'
        prefix: qtCoreBinPath + '/'
        files: module3rdpart
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: installDir
        qbs.installSourceBase: prefix
    }

    // general

    Group {
        name: 'general'
        prefix: qtCoreBinPath + '/'
        files: {
            // suffix
            var prefix, suffix
            if (qbs.targetOS.contains('linux')) {
                prefix = EnvUtils.libPrefix(qbs) + 'Qt' + Qt.core.versionMajor
                suffix = EnvUtils.dylibExtensionFuzzy(qbs)
            } else if (qbs.targetOS.contains('darwin')) {
                prefix = 'Qt'
                suffix = EnvUtils.frameworkSuffix(qbs) + '/**/*'
            } else {
                prefix = EnvUtils.libPrefix(qbs) + 'Qt' + Qt.core.versionMajor
                suffix = EnvUtils.dylibSuffix(qbs)
            }
            //
            var files = []
            moduleGeneral.forEach(function(item){
                files.push(prefix + item + suffix)
            })
            return files
        }
        Properties {
            condition: qbs.targetOS.contains('darwin')
            excludeFiles: {
                var items = ['**/Headers', '**/Headers/**/*', '**/*.prl']
                if (qbs.variantSuffix != 'd') {
                    items.push('**/*_debug')
                }
                return items
            }
        }
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: qbs.targetOS.contains('darwin') ? installDir + '/Frameworks'
                                                        : installDir
        qbs.installSourceBase: prefix
    }

    // plugins

    Group {
        name: 'plugins'
        prefix: Qt.core.pluginPath + '/'
        files: {
            var files = []
            var suffix
            if (qbs.targetOS.contains('linux')) {
                suffix = EnvUtils.dylibExtensionFuzzy(qbs)
            } else {
                suffix = EnvUtils.dylibSuffix(qbs)
            }
            modulePlugins.forEach(function(item){
                files.push(item + '/**/*' + suffix)
            })
            return files
        }
        excludeFiles: {
            if (qbs.targetOS.contains('linux')) {
                return []
            } else {
                var items = [ EnvUtils.excDylibFuzzy(qbs, true) ]
                if (qbs.targetOS.contains('darwin')) {
                    items.push('**/*.dSYM/**/*')
                    if (qbs.variantSuffix != 'd') {
                        items.push('**/*_debug.dylib*')
                    }
                }
                return items
            }
        }
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: installDir + '/' + (qbs.targetOS.contains('darwin')
                                            ? project.projectName + '.app/Contents/plugins'
                                            : 'plugins')
        qbs.installSourceBase: prefix
    }

    // qml

    Group {
        name: 'qml'
        prefix: Qt.qml.qmlPath + '/'
        files: {
            var files = []
            moduleQml.forEach(function(item){
                files.push(item + '/**/*')
            })
            return files
        }
        excludeFiles: [ '**/*.qmlc', '**/*.jsc', '**/*.qmltypes', EnvUtils.excDylibFuzzy(qbs, true) ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: installDir + '/' + (qbs.targetOS.contains('darwin')
                                            ? project.projectName + '.app/Contents/qml'
                                            : 'qml')
        qbs.installSourceBase: prefix
    }

    // resources

    Group {
        name: 'resources'
        prefix: Qt.core.libPath + '/../resources/'
        files: moduleResources
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: installDir + '/' + (qbs.targetOS.contains('darwin')
                                            ? project.projectName + '.app/Contents/resources'
                                            : 'resources')
        qbs.installSourceBase: prefix
    }

    // translations

    Group {
        name: 'translations'
        prefix: Qt.core.libPath + '/../translations/'
        files: moduleTranslations
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: installDir + '/' + (qbs.targetOS.contains('darwin')
                                            ? project.projectName + '.app/Contents/translations'
                                            : 'translations')
        qbs.installSourceBase: prefix
    }

    // QtWebEngineProcess

    Group {
        name: 'QtWebEngineProcess'
        condition: installWebEngineProcess
        prefix: {
            if (qbs.targetOS.contains('linux')) {
                return Qt.core.binPath + '/../libexec/'
            } else {
                return Qt.core.binPath + '/'
            }
        }
        files: {
            var items = []
            var webEngineProcess = 'QtWebEngineProcess'
            if (qbs.targetOS.contains('linux')) {
                //
            } else {
                webEngineProcess += (qbs.buildVariant === 'debug' ? 'd' : '')
                        + EnvUtils.execSuffix(qbs)
            }
            items.push(webEngineProcess)
            return items
        }
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: installDir
    }

    // qt.conf
    Rule {
        condition: generateQtConf && !qbs.targetOS.contains('darwin')
        multiplex: true
        Artifact {
            fileTags: [ 'qt.conf.out' ]
            filePath: FileInfo.joinPaths(project.workDirectory, 'bin', 'qt.conf')
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'generating ' + output.fileName + '...'
            cmd.highlight = 'codegen'
            cmd.sourceCode = function() {
                var newLineSuffix
                if (product.qbs.targetOS.contains('windows')) {
                    newLineSuffix = '\r\n'
                } else {
                    newLineSuffix = '\n'
                }
                var file = new TextFile(output.filePath, TextFile.WriteOnly)
                file.write('[Paths]' + newLineSuffix +
                           'Prefix=.' + newLineSuffix +
                           'Binaries=.' + newLineSuffix +
                           'Libraries=.' + newLineSuffix +
                           'Plugins=plugins' + newLineSuffix +
                           'Imports=imports' + newLineSuffix +
                           'Qml2Imports=qml')
                file.close()
            }
            return [ cmd ]
        }
    }
}
