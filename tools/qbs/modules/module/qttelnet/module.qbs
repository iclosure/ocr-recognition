import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'qttelnet'

    Depends { name: 'Qt.network' }

    cpp.defines: []
    cpp.dynamicLibraries: {
        var items = []
        if (qbs.targetOS.contains('windows')) {
            items.push('ws2_32')
        }
        return items
    }

    cpp.staticLibraries: [ moduleName + variantSuffix ]

}
