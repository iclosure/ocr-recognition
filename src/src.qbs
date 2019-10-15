import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import qbs.ModUtils

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
        var defines = base.concat(['PROJECT_APP'])
        if (qbs.buildVariant == 'debug') {
            //defines.push('DESKTOP_DEMO')    //TODO
        }
        defines.push('TEST_STYLESHEET')
        return defines
    }
    cpp.includePaths: base.concat(['.',
                                   Qt.core.incPath + '/ActiveQt',
                                   FileInfo.joinPaths(project.opencvDir, 'include'),
                                   FileInfo.joinPaths(project.tesseractDir, 'include')
                                  ])
    cpp.dynamicLibraries: {
        var items = base
        var suffix = ''
        if (qbs.buildVariant === 'debug') {
            suffix = 'd'
        }
        // OpenCV
        items.push(project.opencvDir + '/x64/vc15/lib/opencv_world411' + suffix + '.lib')
        // tesseract
        items.push(project.tesseractDir + '/lib/tesseract41' + suffix + '.lib')
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
        return items
    }

    Depends { name: 'Qt.concurrent' }
    Depends { name: 'Qt.axcontainer' }
    Depends { name: 'Qt.printsupport' }
    Depends { name: 'module.jwt' }
    Depends { name: 'module.log4cpp' }

    Group {
        name: 'Headers'
        files: [
            '**/*.h',
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
