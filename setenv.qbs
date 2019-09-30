import qbs
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import qbs.Environment

Project {

    QtInstall {
        condition: qbs.targetOS.contains('windows') //TODO [fix other platform]
        name: 'setenv-qt'
        moduleGeneral: base.concat([ 'Concurrent' ])
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
        modules: ['protocore', 'protowidget']
        installSOCI: false
        installEmpty: false
        installSQLite: false
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
            prefix: project.opencvDir + '/bin/'
            files: {
                var items = []
                if (qbs.architecture == 'x86_64') {
                    items.push('opencv_videoio_ffmpeg411_64.dll')
                } else {
                    items.push('opencv_videoio_ffmpeg411.dll')
                }
                return items
            }
            qbs.install: true
            qbs.installPrefix: project.projectName
            qbs.installDir: 'bin'
        }
        Group {
            name: 'tesseract'
            prefix: project.tesseractDir + '/bin/'
            files: {
                var items = []
                if (qbs.buildVariant == 'debug') {
                    items.push('tesseract41d.dll')
                } else {
                    items.push('tesseract41.dll')
                }
                return items
            }
            qbs.install: true
            qbs.installPrefix: project.projectName
            qbs.installDir: 'bin'
        }
    }
}
