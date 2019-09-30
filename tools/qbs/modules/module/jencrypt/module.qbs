import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'jencrypt'
    cpp.defines: []
    cpp.dynamicLibraries: []
    cpp.staticLibraries: [ moduleName + variantSuffix ]
}
