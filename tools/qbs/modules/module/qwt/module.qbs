import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'qwt'

    cpp.defines: [ moduleName.toUpperCase() + '_DLL' ]
}
