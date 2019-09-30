import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'log4cpp'

    Properties {
        condition: !qbs.targetOS.contains('windows')
        cpp.defines: base.concat(['LOG4CPP_FIX_ERROR_COLLISION'])
    }
}
