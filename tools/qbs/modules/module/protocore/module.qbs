import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'protocore'
    cpp.defines: base.concat(['SOCI_DLL'])
    Properties {
        condition: qbs.targetOS.contains('darwin')
        cpp.dynamicLibraries: []
        cpp.staticLibraries: [ moduleName + variantSuffix ]
    }
}
