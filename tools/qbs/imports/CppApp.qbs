import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import tools.EnvUtils

CppApplication {
    version: '1.0.0'

    property var pairInstallNames: undefined
    property bool linkQtCore: false
    property bool checkMemoryLeak: false
    property string vldPath: ''
    readonly property bool __vldEnabled: checkMemoryLeak && qbs.targetOS.contains('windows')
                                         && qbs.buildVariant == 'debug'
    readonly property string __vldPath: {
        if (vldPath) {
            return vldPath
        }
        var path = project.sourceDirectory + '/tools/libraries/VLD'
        if (File.exists(path + '/bin')) {
            return path
        }
        path = Environment.getEnv('VLD_PATH')
        if (path) {
            return path
        }
        if (qbs.architecture == 'x86_64') {
            return 'C:/Program Files/Visual Leak Detector'
        } else {
            return 'C:/Program Files (x86)/Visual Leak Detector'
        }
    }

    Depends { name: 'Qt.core'; cpp.link: linkQtCore }
    Depends { name: 'Qt.qminimal'; condition: Qt.core.staticBuild }
    Depends { name: 'desc'; required: false }
    Depends { name: 'setenv'; required: false; cpp.link: false }

    targetName: name
    destinationDirectory: {
        if (project.workDirectory) {
            return FileInfo.joinPaths(project.workDirectory, 'bin')
        } else if (project.projectName) {
            return FileInfo.joinPaths(qbs.installRoot, project.projectName, 'bin')
        } else {
            return qbs.installRoot
        }
    }

    desc.condition: true
    desc.fileDesc: 'Smartsoft® Application'
    desc.version: version
    desc.productName: name

    Properties {
        condition: __vldEnabled
        cpp.includePaths: base.concat([__vldPath + '/include'])
        cpp.libraryPaths: {
            var items = base
            if (qbs.architecture == 'x86') {
                items.push(__vldPath + '/lib/Win32')
            } else {
                items.push(__vldPath + '/lib/Win64')
            }
            return items
        }
    }

    Group {
        name: 'VLD Files'
        condition: __vldEnabled
        files: {
            var items = [__vldPath + '/vld.ini']
            var sys, arch
            if (qbs.architecture == 'x86') {
                sys = '32'; arch = '86'
            } else {
                sys = '64'; arch = '64'
            }
            items.push(__vldPath + '/bin/Win' + sys + '/Microsoft.DTfW.DHL.manifest')
            items.push(__vldPath + '/bin/Win' + sys + '/dbghelp.dll')
            items.push(__vldPath + '/bin/Win' + sys + '/vld_x' + arch + '.dll')
            return items
        }
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: 'bin'
    }

    cpp.defines: {
        var items = [ 'PROJECT_DIR="' + project.sourceDirectory + '"' ]
        //
        if (qbs.targetOS.contains('windows')) {
            items.push('WIN32')
            if (qbs.architecture == 'x86_64') {
                items.push('_X64')
            }
        }
        //
        if (qbs.buildVariant === 'debug') {
            items.push('DEBUG')
            items.push('_DEBUG')
        } else {
            items.push('NDEBUG')
        }
        // build version
        items.push('BUILD_VERSION="' + project.buildVersion + '"')
        // check memory leak
        if (__vldEnabled) {
            items.push('J_CHECK_MEMORY_LEAK')
        }
        return items
    }
    cpp.variantSuffix: project.variantSuffix
    cpp.separateDebugInformation: qbs.debugInformation

    Properties {
        condition: qbs.targetOS.contains('windows')
        cpp.dynamicLibraries: [ 'user32' ]
    }

    Properties {
        condition: qbs.targetOS.contains('linux')
        cpp.dynamicLibraries: [ 'dl' ]
    }

    // rc
    Group {
        name: 'windres'
        condition: desc.condition && qbs.targetOS.contains('windows')
        // We need the version in two separate formats for the .rc file
        //  RC_VERSION=1,0,0,0 (quadruple)
        //  RC_VERSION_STRING='1.0.0-xxx' (free text)
        // Also, we need to replace space with \x20 to be able to work with both rc and windres
        cpp.defines: {
            var defines = outer.concat(['RC_ICON1="' + desc.iconName + '"',
                                        'RC_FILEDESC=' + desc.fileDesc.replace(/ /g, '\\x20'),
                                        'RC_PRODUCTNAME=' + desc.productName.replace(/ /g, '\\x20'),
                                        'RC_COMPANYNAME=' + desc.companyName.replace(/ /g, '\\x20'),
                                        'RC_VERSION=' + desc.version.replace(/\./g, ',') + ',0',
                                        'RC_VERSION_STRING=' + desc.displayVersion,
                                        'RC_COPYRIGHT=2016-' + desc.copyrightYear
                                        + ' ' + desc.companyName.replace(/ /g, '\\x20')])
            if (desc.iconName && File.exists(desc.iconName)) {
                defines.push('GENERATE_ICON')
            }
            return defines
        }
        files: 'resource/windows/application.rc'
    }

    Rule {
        inputs: ['j.scxml.compilable']
        Artifact {
            filePath: FileInfo.joinPaths(product.moduleProperty('Qt.core', 'generatedHeadersDir'),
                                         input.baseName + '.h')
            fileTags: [ 'hpp', 'unmocable' ]
        }
        Artifact {
            filePath: input.baseName + '.cpp'
            fileTags: [ 'cpp' ]
        }
        prepare: {
            var compilerName = product.moduleProperty('Qt.scxml', 'qscxmlcName')
            var compilerPath = FileInfo.joinPaths(input.moduleProperty('Qt.core', 'binPath'),
                                                  compilerName)
            var args = ['--header', outputs['hpp'][0].filePath,
                        '--impl', outputs['cpp'][0].filePath]
            var cxx98 = input.moduleProperty('cpp', 'cxxLanguageVersion') === 'c++98'
            if (cxx98)
                args.push('-no-c++11')
            var className = input.moduleProperty('Qt.scxml', 'className')
            if (className)
                args.push('--classname', className)
            var namespace = input.moduleProperty('Qt.scxml', 'namespace')
            if (namespace)
                args.push('--namespace', namespace)
            args.push('--statemethods')
            args.push(input.filePath)
            // create command compilier
            var cmd = new Command(compilerPath, args)
            cmd.description = 'compiling ' + input.fileName
            cmd.highlight = 'codegen'
            return [ cmd ]
        }
    }
}
