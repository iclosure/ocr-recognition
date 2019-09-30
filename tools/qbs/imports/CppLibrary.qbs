import qbs
import qbs.File
import qbs.FileInfo
import tools.EnvUtils

Library {
    version: '1.0.0'
    property bool useQt: true
    property bool useQtCore: true
    property bool isBundle: false
    property bool isDynamicLibrary: true

    type: {
        var items = ['translation']
        if (isDynamicLibrary) {
            items.push('dynamiclibrary')
            if (isForAndroid) {
                items.push('android.nativelibrary')
            }
        } else {
            items.push('staticlibrary')
        }
        return items
    }

    Depends { name: 'cpp' }
    Depends { name: "bundle" }
    Depends { condition: useQt && useQtCore; name: 'Qt.core' }
    Depends { name: 'desc'; cpp.link: false }
    Depends { name: 'setenv'; required: false; cpp.link: false }

    Properties {
        condition: qbs.targetOS.contains('android')
        qbs.architectures: ["armv7a"]
        Android.sdk.platform: 'android-21'
        java.additionalClassPaths: {
            var items = base
            console.warn("=====:" + java.jdkPath)
            return items
        }
    }

    // module
    property string modulePath: ''
    property string namePath: name
    readonly property path includePath: FileInfo.joinPaths(project.sourceDirectory,
                                                           'include', modulePath, namePath)

    readonly property path precompPath: path + '/common'

    // translation
    property path langPath: sourceDirectory + '/resource/lang'
    property pathList noRecursivePaths: []
    property pathList recursivePaths: []
    property stringList translationFileTags: [ 'hpp', 'cpp' ]
    property stringList translations: []
    property bool defaultTranslation: false

    // default flags
    property string relativeDirectory: ''
    property bool defaultCopyHeader: true
    property bool defaultCopyDynamic: true

    // destination
    property string relativeDestination: {
        if (qbs.targetOS.contains('ios')) {
            return 'ios'
        } else if (qbs.targetOS.contains('android')) {
            return 'android'
        } else {
            return ''
        }
    }

    property string destinationRoot: FileInfo.joinPaths(project.sourceDirectory, 'lib', modulePath)

    // install
    property stringList installFileTags: {
        var items = []
        if (isDynamicLibrary) {
            items.push('dynamiclibrary')
            items.push('dynamiclibrary_symlink')
            if (isForAndroid) {
                items.push('android.nativelibrary')
            }
        } else {
            items.push('staticlibrary')
        }
        return items
    }
    property bool defaultInstall: isDynamicLibrary
    property string installPrefix: 'bin'
    property string installDir: ''

    // export
    property bool defaultExport: true

    targetName: name
    desc.condition: true
    desc.fileDesc: 'Smartsoft® Runtime Library'
    desc.version: version
    desc.productName: name

    cpp.includePaths: base.concat([ precompPath ])
    cpp.defines: {
        var items = base
        var upperName = product.name.toUpperCase()
        upperName = upperName.replace(/-/g, '_')
        if (isDynamicLibrary) {
            items.push(upperName + '_LIB')
            items.push(upperName + '_BUILD')
        }
        if (!useQt) {
            items.push('J_NO_QT')
        }
        //
        if (qbs.targetOS.contains('windows')) {
            items.push('WIN32')
        }
        //
        if (qbs.buildVariant === 'debug') {
            items.push('DEBUG')
            items.push('_DEBUG')
        } else {
            items.push('NDEBUG')
        }
        return items
    }
    cpp.variantSuffix: project.variantSuffix

    // destination
    destinationDirectory: FileInfo.joinPaths(destinationRoot, relativeDestination)

    Properties {
        condition: qbs.targetOS.contains("darwin")
        //Depends { name: "Qt.qios" }
        //Depends { name: "ib" }
        Depends { name: "bundle" }
        // for apple
        bundle.isBundle: isBundle
        cpp.separateDebugInformation: qbs.debugInformation
        cpp.cxxLanguageVersion: 'c++11'
        cpp.cxxStandardLibrary: 'libc++'

        Properties {
            condition: !isDynamicLibrary
            cpp.visibility: 'hidden'
        }

        Properties {
            condition: qbs.targetOS.contains('ios')
            relativeDestination: 'ios'
        }
    }

    //    Properties {
    //        condition: qbs.targetOS.contains('android')
    //        //qbs.architectures: ["mips", "x86"]
    //        //Depends { productTypes: ["android.nativelibrary"] }
    //        relativeDestination: 'android'
    //    }

    Group {
        fileTagsFilter: installFileTags
        qbs.install: defaultInstall
        qbs.installPrefix: project.projectName
        qbs.installDir: FileInfo.joinPaths(installPrefix, installDir)
    }

    Rule {
        condition: product.defaultCopyHeader
        inputs: [ 'hpp.in' ]
        Artifact {
            filePath: product.includePath  + '/' + FileInfo.relativePath(
                          FileInfo.joinPaths(product.sourceDirectory, product.relativeDirectory),
                          input.filePath)
            fileTags: [ 'hpp' ]
        }
        prepare: {
            var cmd = new JavaScriptCommand()
            cmd.description = 'coping ' + input.fileName
            //cmd.silent = true
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [cmd]
        }
    }

    Rule {
        condition: defaultTranslation && translations.length > 0
        multiplex: true
        inputs: translationFileTags
        Artifact { fileTags: [ 'translation' ] }
        prepare: {
            var commands = []
            // translation
            var commandTranslation = EnvUtils.createTranslationCommand(product)
            if (commandTranslation) {
                commands.push(commandTranslation)
            }
            return commands
        }
    }

    Export {
        condition: product.defaultExport
        Depends { name: 'cpp' }
        cpp.defines: [ product.name.toUpperCase() + '_LIB' ]
        cpp.includePaths: [FileInfo.joinPaths(project.sourceDirectory, 'include', product.modulePath)]

        Properties {
            condition: qbs.targetOS.contains('windows') && product.isDynamicLibrary

            cpp.dynamicLibraries: {
                var items = []
                //
                var fullPath = EnvUtils.libFullName(product, product.targetName,
                                                    product.cpp.variantSuffix,
                                                    product.isDynamicLibrary)
                var path = FileInfo.joinPaths(project.sourceDirectory, 'lib', product.modulePath, fullPath)
                items.push(path)
                return items
            }
        }
        Properties {
            condition: qbs.targetOS.contains('windows') && !product.isDynamicLibrary
            cpp.staticLibraries: {
                var items = []
                //
                var fullPath = EnvUtils.libFullName(product, product.targetName,
                                                    product.cpp.variantSuffix,
                                                    product.isDynamicLibrary)
                var path = FileInfo.joinPaths(project.sourceDirectory, 'lib', product.modulePath, fullPath)
                items.push(path)
                return items
            }
        }
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
        files: 'resource/windows/library.rc'
    }
}
