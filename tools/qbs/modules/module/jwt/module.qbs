import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'jwt'

    Depends { name: 'Qt.widgets' }
    Depends { name: 'Qt.dbus' }
    Depends { name: 'module.qwt' }
}
