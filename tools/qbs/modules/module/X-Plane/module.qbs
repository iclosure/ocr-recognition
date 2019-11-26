import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'X-Plane'

    readonly property string xplaneSDKDir: project.sourceDirectory + '/tools/libraries/X-Plane'

    cpp.defines: [ ]
    includePaths: [ xplaneSDKDir ]
    cpp.libraryPaths: {
        var items = []
        var item = xplaneSDKDir + '/XPL/Libraries'
        if (qbs.targetOS.contains('windows)) {
            item += '/Win'
        } else if (qbs.targetOS.contains('macos)) {
            item += '/Mac'
        }
        items.push(item)
        return items
    }
    cpp.dynamicLibraries: {
        var items = []
        // XPLM
        var itemXPLM = 'XPLM', itemXPWidgets = 'XPWidgets'
        if (qbs.targetOS.contains("windows")) {
            if (qbs.architecture == 'x86_64') {
                itemXPLM += '_64'
                itemXPWidgets += '_64'
            }
        }
        items.push(itemXPLM)
        items.push(itemXPWidgets)
        return items
    }
}
