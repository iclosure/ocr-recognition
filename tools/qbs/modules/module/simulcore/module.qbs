import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'simulcore'
    cpp.dynamicLibraries: []
    cpp.staticLibraries: [ moduleName + variantSuffix ]
}
