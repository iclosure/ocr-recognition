import qbs
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import qbs.Environment
import qbs.Utilities

PackageProduct {
    version: project.version

    property bool installGlobal: true
    property bool installSystem32Api: true
    property bool installMsvcRuntime: true
    property stringList globalFiles: [
        'VERSION',
        'LICENSE',
        'README.md'
    ]

    Group {
        name: 'data-global'
        condition: installGlobal
        prefix: project.sourceDirectory + '/'
        files: globalFiles
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
    }

    // system32 - api*
    Group {
        name: 'data-sys-api'
        condition: installSystem32Api && qbs.targetOS.contains('windows')
        prefix: {
            var vsVersion = Environment.getEnv('VisualStudioVersion')
            var versionFlag = Utilities.versionCompare(vsVersion, '15.0')
            var path = undefined
            if (versionFlag >= 0) {
                //path = FileInfo.joinPaths(Environment.getEnv('DevEnvDir'))
                path = FileInfo.joinPaths(Environment.getEnv('VS150PROCOMNTOOLS'))
            }
            if (path == undefined) {
                path = FileInfo.joinPaths(Environment.getEnv('SystemRoot'), 'system32')
            }
            return path + '/'
        }
        files: [ 'api-ms-win-*.dll' ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'bin'
    }

    // msvc-runtime
    Group {
        name: 'data-runtime'
        condition: installMsvcRuntime && qbs.targetOS.contains('windows')
        prefix: {
            var config = qbs.buildVariant === 'debug' ? 'debug_nonredist' : ''
            var vsVersion = Environment.getEnv('VisualStudioVersion')
            var versionFlag = Utilities.versionCompare(vsVersion, '15.0')
            var debugFlag = (qbs.buildVariant ==='debug')
            var redistDir = FileInfo.fromNativeSeparators(
                        Environment.getEnv(versionFlag >= 0 ? 'VCToolsRedistDir' : 'VCINSTALLDIR'))
            if (versionFlag < 0) {
                redistDir += 'redist'
            }
            var config = debugFlag ? 'debug_nonredist' : ''
            var crtDir = 'Microsoft.VC*.' + (debugFlag ? 'Debug' : '') + 'CRT'
            var archName = ''
            if (qbs.architecture == 'x86_64') {
                archName = 'x64'
            } else {
                archName = qbs.architecture
            }
            var path = FileInfo.joinPaths(redistDir, config, archName, crtDir) + '/'
            return path
        }
        files: [ 'concrt*.dll', 'msvcr*.dll', 'msvcp*.dll', 'vccorlib*.dll', 'vcruntime*.dll' ]
        qbs.install: true
        qbs.installPrefix: installPrefix
        qbs.installDir: FileInfo.joinPaths(installDir, 'bin')
    }

    // system32 - api*
    Group {
        name: 'data-system32-ucrtbase'
        condition: installSystem32Api && qbs.targetOS.contains('windows')
        prefix: {
            var path = FileInfo.joinPaths(Environment.getEnv('SystemRoot'), 'system32')
            return path + '/'
        }
        files: [ 'ucrtbase' + project.variantSuffix + '.dll' ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'bin'
    }
}
