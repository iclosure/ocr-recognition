import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import qbs.Process
import qbs.Utilities

PluginLibrary {

    property pathList dynamicLibraryPaths: [
        project.sourceDirectory + '/lib/' + project.archDir
    ]

    Depends { name: 'Qt.qml' }

    Group {
        id: qmlfiles
        name: 'qmlfiles'
        prefix: product.sourceDirectory + '/'
        files: [ 'qmldir' ]
        fileTags: [ 'qmldir.in' ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: product.installDir
    }

    type: base.concat([ 'qmldir.out', 'qmltype.out' ])
    cpp.defines: base.concat([ 'QML_IMPORTS_PATH="' + Qt.qml.qmlPath + '"'])

    Rule {
        inputs: qmlfiles.fileTags
        Artifact {
            filePath: FileInfo.joinPaths(product.destinationDirectory, input.fileName)
            fileTags: [ 'qmldir.out' ]
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'coping ' + input.fileName
            cmd.sourceCode = function(){ File.copy(input.filePath, output.filePath) }
            return [cmd]
        }
    }

    Rule {
        condition: qbs.buildVariant !== 'debug'
                   && (!qbs.targetOS.contains("windows") || qbs.architecture != 'x86_64')
        multiplex: true
        inputs: [ 'dynamiclibrary' ].concat(qmlfiles.fileTags)
        Artifact { fileTags: [ 'qmltype.out' ] }
        prepare: {
            var envs = ['PATH='
                        + product.Qt.core.binPath
                        + product.qbs.pathListSeparator + product.Qt.core.libPath
                        + product.qbs.pathListSeparator + product.dynamicLibraryPaths.join(product.qbs.pathListSeparator)
                        + product.qbs.pathListSeparator + Environment.getEnv('PATH')]
            // generate
            var cmd = new Command(FileInfo.joinPaths(product.Qt.core.binPath, 'qmlplugindump'),
                                  ['-defaultplatform', '-nonrelocatable', product.uri, product.pluginVersion,
                                   product.destinationRoot, '-output', FileInfo.joinPaths(
                                       product.destinationDirectory, product.name + '.qmltypes')])
            cmd.description = 'generating qmltypes...'
            if (product.qbs.targetOS.contains('linux')) {
                cmd.workingDirectory = product.Qt.core.libPath
            } else {
                cmd.workingDirectory = product.Qt.core.binPath
            }
            cmd.environment = envs
            return [cmd]
        }
    }
}
