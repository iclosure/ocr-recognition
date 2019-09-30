import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'PCI-Dask'

    cpp.defines: [ 'PCIS_DASK_LIB' ]
    cpp.includePaths: [ project.sourceDirectory + '/include/PCIS-DASK' ]
    cpp.libraryPaths: [ project.sourceDirectory + '/lib' ]

    Properties {
        condition: qbs.targetOS.contains('windows')
        cpp.dynamicLibraries: [ moduleName ]
    }
}
