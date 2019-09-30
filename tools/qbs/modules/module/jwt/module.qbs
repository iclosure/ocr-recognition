import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'jwt'

    Depends { name: 'Qt.widgets' }
    Depends { name: 'module.qwt' }
}
