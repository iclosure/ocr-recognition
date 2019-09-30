import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'protometa'

    Properties {
        condition: qbs.targetOS.contains('darwin')
        cpp.dynamicLibraries: []
        cpp.staticLibraries: [ moduleName + variantSuffix ]
    }
}
