import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'tinyxml'
    cpp.defines: []
    cpp.dynamicLibraries: []
    cpp.staticLibraries: [ moduleName + variantSuffix ]
}
