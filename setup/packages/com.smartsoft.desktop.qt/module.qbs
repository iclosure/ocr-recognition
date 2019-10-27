import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment

PackageQt {
    name: 'com.smartsoft.desktop.qt'
    moduleGeneral: [
        'Concurrent', 'Core', 'Gui', 'Network', 'PrintSupport', 'Widgets',
        'OpenGL', 'Multimedia', 'MultimediaWidgets'
    ]
    moduleTranslations: ['qt_zh_CN.qm', 'qt_help_zh_CN.qm']
}
