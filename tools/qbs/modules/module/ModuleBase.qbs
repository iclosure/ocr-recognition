import qbs
import tools.EnvUtils

Module {
    version: '1.0.0'

    property string moduleName: name
    property string variantSuffix: {
        var suffix = ''
        if (qbs.architecture == 'x86_64') {
            suffix += '64'
        }
        if (qbs.buildVariant == 'debug') {
            suffix += 'd'
        }
        return suffix
    }
    property bool isDynamicLibrary: true
    property path includePaths: project.sourceDirectory + '/include'
    property path libraryPaths: project.sourceDirectory + "/lib"

    Depends { name: "cpp" }

    cpp.defines: [ moduleName.toUpperCase() + '_LIB' ]
    cpp.includePaths: [ includePaths ]
    cpp.libraryPaths: [ libraryPaths ]
    cpp.dynamicLibraries: [ libraryPaths + '/'
        + EnvUtils.libFullName(product, moduleName,
                               variantSuffix, isDynamicLibrary)]
}
