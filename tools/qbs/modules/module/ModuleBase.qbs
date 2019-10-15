import qbs
import tools.EnvUtils

Module {
    version: '1.0.0'

    property string moduleName: name
    property string variantSuffix: qbs.buildVariant == 'debug' ? 'd' : ''
    property bool isDynamicLibrary: true
    property path includePaths: project.sourceDirectory + '/include'
    property path libraryPaths: project.sourceDirectory + '/lib/' + project.archDir

    Depends { name: "cpp" }

    cpp.defines: [ moduleName.toUpperCase() + '_LIB' ]
    cpp.includePaths: [ includePaths ]
    cpp.libraryPaths: [ libraryPaths ]
    cpp.dynamicLibraries: [ libraryPaths + '/'
        + EnvUtils.libFullName(product, moduleName,
                               variantSuffix, isDynamicLibrary)]
}
