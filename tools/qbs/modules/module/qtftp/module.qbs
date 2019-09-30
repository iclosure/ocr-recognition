import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'qtftp'
    cpp.defines: []
    cpp.dynamicLibraries: []
    cpp.staticLibraries: [ moduleName + variantSuffix ]
}
