import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'qrencode'
    cpp.defines: []
    cpp.dynamicLibraries: []
    cpp.staticLibraries: [ moduleName + variantSuffix ]
}
