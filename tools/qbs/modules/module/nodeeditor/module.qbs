import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'nodeeditor'

    cpp.defines: [ 'NODE_EDITOR_SHARED' ]
    cpp.includePaths: {
        var prefix = project.sourceDirectory + '/include/'
        var paths = []
        paths.push(prefix)
        paths.push(prefix + moduleName)
        paths.push(prefix + moduleName + '/nodes')
        return paths;
    }
}
