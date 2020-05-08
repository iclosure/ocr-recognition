import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'protoqml'

    Depends { name: 'Qt'; submodules: ['concurrent', 'network', 'qml', 'quick'] }
//    Depends {
//        condition: qbs.targetOS.contains('windows')
//        name: 'module'; submodules: ['log4cpp', 'qtftp', 'qttelnet'];
//    }
    Depends { name: 'module.protocore' }

    Properties {
        condition: qbs.targetOS.contains('darwin')
        cpp.dynamicLibraries: []
        cpp.staticLibraries: [ moduleName + variantSuffix ]
    }
}
