import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import qbs.ModUtils
import tools.EnvUtils

WidgetApp {
    targetName: project.projectName
    version: project.version

    translations: [ 'zh_CN.ts' ]
    defaultTranslation: true
    desc.iconName: sourceDirectory + '/resource/image/favicon.ico'
    desc.fileDesc: project.projectDisplayName
    Qt.core.resourceFileBaseName: project.projectName

    cpp.useCxxPrecompiledHeader: false
    cpp.defines: {
        var items = base.concat(['PROJECT_APP'])
        if (qbs.buildVariant == 'debug') {
            //items.push('DESKTOP_DEMO')    //TODO
        }
        items.push('TEST_STYLESHEET')
        // opencv
        //items.push('TESS_IMPORTS')
        // tesseract
        //items.push('TESS_IMPORTS')
        return items
    }
    cpp.includePaths: {
        var items = base
        items.push('.')
        items.push(Qt.core.incPath + '/ActiveQt')
        if (project.useVcPkg) {
            items.push(FileInfo.joinPaths(project.vcpkgLibHome, 'include'))
        } else{
            items.push(FileInfo.joinPaths(project.opencvDir, 'include'))
            items.push(FileInfo.joinPaths(project.tesseractDir, 'include'))
        }
        return items
    }
    cpp.dynamicLibraries: {
        var items = base
        var suffix = ''
        if (qbs.buildVariant === 'debug') {
            suffix = 'd'
        }
        if (project.useVcPkg) {
            if (!project.useVcPkgStatic) {
                var debugDir = qbs.buildVariant == 'debug' ? '/debug' : ''
                var prefixDir = project.vcpkgLibHome + debugDir + '/lib/'
                var libSuffix = project.variantSuffix + EnvUtils.libExtension(qbs, true)
                var libSuffixStatic = project.variantSuffix + EnvUtils.libExtension(qbs, false)
                items.push(prefixDir + 'opencv_core' + libSuffix)
                items.push(prefixDir + 'opencv_imgcodecs' + libSuffix)
                items.push(prefixDir + 'opencv_imgproc' + libSuffix)
                items.push(prefixDir + 'opencv_photo' + libSuffix)
                items.push(prefixDir + 'leptonica-1.78.0' + libSuffix)
                items.push(prefixDir + 'tesseract41' + libSuffixStatic)
            }
        } else {
            // OpenCV
            items.push(project.opencvDir + '/x64/vc15/lib/opencv_world411' + suffix + '.lib')
            // tesseract
            items.push(project.tesseractDir + '/lib/tesseract41' + suffix + '.lib')
        }
        return items
    }
    cpp.staticLibraries: {
        var items = base.concat(['ole32', 'oleaut32', 'user32', 'gdi32', 'advapi32'])
        //
        var suffix = ''
        if (qbs.buildVariant === 'debug') {
            suffix = 'd'
        }
        items.push(Qt.core.libPath + '/Qt5AxBase' + suffix)
        items.push(Qt.core.libPath + '/Qt5AxContainer' + suffix)
        if (project.useVcPkg && project.useVcPkgStatic) {
            items.push(project.vcpkgLibHome + '/lib/opencv_core.lib')
            items.push(project.vcpkgLibHome + '/lib/tesseract41.lib')
        }
        return items
    }

    Depends {
        name: 'Qt'
        submodules: [
            'concurrent', 'axcontainer', 'printsupport', 'multimedia', 'multimediawidgets'
        ]
    }
    Depends { name: 'module.log4cpp' }
    Depends { name: 'module.jwt' }

    Group {
        name: 'Headers'
        files: [
            '**/*.h'
        ]
    }

    Group {
        name: 'Sources'
        files: [ '**/*.cpp' ]
    }

    Group {
        name: 'Resources'
        prefix: 'resource/'
        excludeFiles: [ '**/*.ts', '**/*.psd' ]
        files: [ '**/*' ]
        fileTags: [ 'qt.core.resource_data' ]
        Qt.core.resourcePrefix: '/desktop'
        Qt.core.resourceSourceBase: 'resource'
    }
}
