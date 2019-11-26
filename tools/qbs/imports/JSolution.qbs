import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import qbs.TextFile

Project {
    id: root
    name: projectDisplayName
    minimumQbsVersion: '1.10.0'
    qbsSearchPaths: [ '../' ]

    property string projectName: 'app'
    property string projectDisplayName: 'App'
    property string version: '1.0.0'
    property int buildVersion: 1
    property bool buildQuote: false
    readonly property int versionMajor: parseInt(version.split('.')[0])
    readonly property int versionMinor: parseInt(version.split('.')[1])
    readonly property int versionPatch: parseInt(version.split('.')[2])
    readonly property int versionBuild: parseInt(version.split('.')[3])
    readonly property string variantSuffix: qbs.buildVariant == 'debug' ? 'd' : ''
    readonly property path qtdir: FileInfo.fromWindowsSeparators(Environment.getEnv('Qt5_DIR'))
    readonly property path installRoot: qbs.installRoot
    readonly property path workDirectory: FileInfo.joinPaths(installRoot, projectName)
    readonly property string archDir: {
        if (qbs.targetOS.contains("windows")) {
            return qbs.architecture == 'x86_64' ? 'x64' : ''
        } else {
            return ''
        }
    }
    property stringList globalFiles: [
        'VERSION',
        'CHANGE',
        'LICENSE',
        'README.md'
    ]

    references: {
        var items = []
        // config
        var filePath = sourceDirectory + '/config/config.qbs'
        if (File.exists(filePath)) {
            items.push(filePath)
        }
        // src
        filePath = sourceDirectory + '/src/src.qbs'
        if (File.exists(filePath)) {
            items.push(filePath)
        }
        // setenv
        filePath = sourceDirectory + '/setenv.qbs'
        if (File.exists(filePath)) {
            items.push(filePath)
        }
        // setup
        filePath = sourceDirectory + '/setup/setup.qbs'
        if (File.exists(filePath)) {
            items.push(filePath)
        }
        // tools
        filePath = sourceDirectory + '/tools/tools.qbs'
        if (File.exists(filePath)) {
            items.push(filePath)
        }
        return items
    }

    Probe {
        id: probeVersion
        readonly property string projectVersion: version + '.' + buildVersion
        readonly property path projectDirectory: sourceDirectory
        configure: {
            var filePath = FileInfo.joinPaths(projectDirectory, 'VERSION')
            if (!File.exists(filePath)) {
                filePath = FileInfo.joinPaths(projectDirectory, 'VERSION.txt')
                if (!File.exists(filePath)) {
                    found = false
                    return
                }
            }
            var file = new TextFile(filePath, TextFile.WriteOnly)
            file.truncate()
            file.write(projectVersion)
            file.close()
            found = true
        }
    }

    Product {
        name: 'global'
        type: base.concat(['version.out'])

        Group {
            name: 'files'
            prefix: project.sourceDirectory + '/'
            files: root.globalFiles
            qbs.install: true
            qbs.installPrefix: project.projectName
        }
    }
}
