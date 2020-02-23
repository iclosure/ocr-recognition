import qbs
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import qbs.Environment
import tools.EnvUtils

Project {

    QtInstall {
        condition: qbs.targetOS.contains('windows') //TODO [fix other platform]
        name: 'setenv-qt'
        moduleGeneral: base.concat([
                                       'Concurrent',
                                       'PrintSupport',
                                       'Network',
                                       'OpenGL',
                                       'Multimedia',
                                       'MultimediaWidgets'
                                   ])
        modulePlugins: base.concat(['mediaservice'])
        moduleTranslations: ['qt_zh_CN.qm', 'qt_help_zh_CN.qm']
        useOpenGL: false
    }

    JFrameworkInstall {
        condition: !project.buildQuote
        id: setenv_jframework
        name: 'setenv-jframework'
        modules: [
            'jwt', 'log4cpp', 'qwt'
        ]
    }

    DataStudioInstall {
        condition: !project.buildQuote && !qbs.targetOS.contains('darwin') //TODO [fix other platform]
        name: 'setenv-datastudio'
        modules: []
        installSOCI: false
        installEmpty: false
        installSQLite3: false
        installMySQL: false
        installODBC: false
    }

    Product {
        name: 'setenv'
        Depends { name: 'setenv-qt'; required: false }
        Depends { name: 'setenv-jframework'; required: false }
        Depends { name: 'setenv-datastudio'; required: false }
        Depends { name: 'setenv-3rdpart'; required: false }
    }

    Product {
        name: 'setenv-3rdpart'
        Depends { name: 'cpp' }
        Group {
            name: 'opencv'
            condition: !project.useVcPkgStatic
            prefix: project.useVcPkg ? project.vcpkgLibBin : project.opencvDir + '/bin/'
            files: {
                var items = []
                if (project.useVcPkg) {
                    items.push('jpeg62.dll')
                    items.push('zlib' + project.variantSuffix + '1.dll')
                    items.push('webp' + EnvUtils.dylibSuffix(qbs))
                    items.push('libpng16' + EnvUtils.dylibSuffix(qbs))
                    items.push('tiff' + EnvUtils.dylibSuffix(qbs))
                    items.push('lzma' + EnvUtils.dylibSuffix(qbs))
                    items.push('opencv_core' + EnvUtils.dylibSuffix(qbs))
                    items.push('opencv_imgcodecs' + EnvUtils.dylibSuffix(qbs))
                    items.push('opencv_imgproc' + EnvUtils.dylibSuffix(qbs))
                    items.push('opencv_photo' + EnvUtils.dylibSuffix(qbs))
                    items.push('leptonica-1.78.0' + EnvUtils.dylibSuffix(qbs))
                } else {
                    if (qbs.architecture == 'x86_64') {
                        items.push('opencv_videoio_ffmpeg' + project.opencvVersion + '_64.dll')
                        items.push('../x64/vc15/bin/opencv_world' + project.opencvVersion + '.dll')
                    } else {
                        items.push('opencv_videoio_ffmpeg' + project.opencvVersion + '.dll')
                        //items.push('../x86/vc15/bin/opencv_world' + project.opencvVersion + '.dll')
                    }
                }
                return items
            }
            qbs.install: true
            qbs.installPrefix: project.projectName
            qbs.installDir: 'bin'
        }
        Group {
            name: 'tesseract'
            condition: !project.useVcPkgStatic
            prefix: project.useVcPkg ? project.vcpkgLibBin : project.tesseractDir + '/bin/'
            files: {
                var items = []
                if (project.useVcPkg) {
                    //
                } else {
                    if (qbs.buildVariant == 'debug') {
                        items.push('tesseract41d.dll')
                    } else {
                        items.push('tesseract41.dll')
                    }
                }
                return items
            }
            qbs.install: true
            qbs.installPrefix: project.projectName
            qbs.installDir: 'bin'
        }
        Group {
            name: 'tessdata'
            prefix: project.sourceDirectory + '/tools/tessdata/'
            files: [ '*.traineddata' ]
            qbs.install: true
            qbs.installPrefix: project.projectName
            qbs.installDir: 'tessdata'
        }
    }
}
