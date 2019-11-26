import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'CANBUS'

    cpp.defines: [ ]
    cpp.libraryPaths: [ project.sourceDirectory + '/lib/' + project.archDir ]
    cpp.dynamicLibraries: [ ]

    Properties {
        condition: qbs.targetOS.contains('windows')
        cpp.dynamicLibraries: [ 'CanCmd' ]
    }
}
