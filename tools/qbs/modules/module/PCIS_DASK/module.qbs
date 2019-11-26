import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'PCI-Dask'

    cpp.defines: [ 'PCIS_DASK_LIB' ]
    cpp.libraryPaths: [ project.sourceDirectory + '/lib/PCIS-DASK/' + project.archDir ]

    Properties {
        condition: qbs.targetOS.contains('windows')
        cpp.dynamicLibraries: [ moduleName ]
    }
}
