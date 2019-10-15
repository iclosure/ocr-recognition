import qbs
import qbs.FileInfo
import qbs.Environment

Project {
    name: projectDisplayName + ' Setup'
    minimumQbsVersion: '1.9.1'
    qbs.enableDebugCode: true
    qbsSearchPaths: [ '../' ]

    property string projectName: 'app'
    property string projectDisplayName: 'App'
    property string version: '1.0.0'
    property string variantSuffix: ''
    property string installRoot: ''
    readonly property bool isSetup: true
    readonly property int versionMajor: parseInt(version.split('.')[0])
    readonly property int versionMinor: parseInt(version.split('.')[1])
    readonly property int versionPatch: parseInt(version.split('.')[2])
    readonly property path qtdir: FileInfo.fromWindowsSeparators(Environment.getEnv('QTDIR'))
    readonly property path projectInstallRoot: {
        var path = sourceDirectory + '/' + installRoot
        if (FileInfo.cleanPath) {
            path = FileInfo.cleanPath(path)
        }
        return path
    }
    readonly property path workDirectory: FileInfo.joinPaths(projectInstallRoot, projectName)
    readonly property string archDir: {
        if (qbs.targetOS.contains("windows")) {
            return qbs.architecture == 'x86_64' ? 'x64' : ''
        } else {
            return ''
        }
    }

    references: {
        if (qbs.buildVariant == 'debug' || variantSuffix == 'd') {
            return []
        }
        return [
            sourceDirectory + '/setup/setup.qbs',
            sourceDirectory + '/tools/tools.qbs'
        ]
    }
}
