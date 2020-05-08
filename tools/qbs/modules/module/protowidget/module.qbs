import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'protowidget'

    Depends { name: 'Qt'; submodules: ['gui', 'concurrent', 'widgets'] }
//    Depends {
//        condition: qbs.targetOS.contains('windows')
//        name: 'module'; submodules: [
//            'log4cpp', 'qtftp', 'qttelnet'
//        ];
//    }
    Depends { name: 'module'; submodules: [ 'jwt', 'protocore' ] }
}
