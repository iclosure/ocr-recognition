import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'simulcpp'
    cpp.dynamicLibraries: []
    cpp.staticLibraries: [ moduleName + variantSuffix ]
}
