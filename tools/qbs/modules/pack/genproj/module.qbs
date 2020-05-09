import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import qbs.TextFile

Module {
    additionalProductTypes: [ 'setup.genproj' ]

    Depends { name: 'cpp' }
    Depends { name: 'Qt.core'; cpp.link: false }

    Group {
        name: 'files'
        files: [ 'setup.qbs.in' ]
        fileTags: [ 'setup.genproj.in' ]
    }

    Probe {
        id: probeSetup
        condition: project.qbs.buildVariant != 'debug'
        readonly property var _project: project
        readonly property var _product: product
        configure: {
            // setup
            var source = path + '/setup.qbs.in'
            if (!File.exists(source)) {
                console.warn('Source file "' + source + ' is not exists!')
                return
            }
            var sourceFile = new TextFile(source, TextFile.ReadOnly)
            var content = sourceFile.readAll()
            sourceFile.close()
            // replace @QBS_MIN_VER@
            content = content.replace(/@QBS_MIN_VER@/g, _project.minimumQbsVersion)
            // replace @VERSION@
            content = content.replace(/@VERSION@/g, _project.version)
            // replace @BUILD_VERSION@
            content = content.replace(/@BUILD_VERSION@/g, _project.buildVersion)
            // replace @VARIANT_SUFFIX@
            content = content.replace(/@VARIANT_SUFFIX@/g, _project.variantSuffix)
            // replace @PROJECT_INSTALL_ROOT@
            var relativeInstallRoot = '../' + FileInfo.relativePath(_project.sourceDirectory + '/..', _project.installRoot)
            content = content.replace(/@PROJECT_INSTALL_ROOT@/g, relativeInstallRoot)
            // replace @PROJECT_NAME@
            content = content.replace(/@PROJECT_NAME@/g, _project.projectName)
            // replace @PROJECT_DISPLAY_NAME@
            content = content.replace(/@PROJECT_DISPLAY_NAME@/g, _project.projectDisplayName)
            //
            var target = FileInfo.joinPaths(_project.sourceDirectory,
                                            _project.projectName + '-' + FileInfo.completeBaseName(source))
            var targetFile = new TextFile(target, TextFile.WriteOnly)
            targetFile.write(content)
            targetFile.close()
            // remove project setup dir
            var setupBuildDir = _project.sourceDirectory + '/../build-'
                    + _project.projectName + '-setup-Qt_'
                    + _product.Qt.core.version.replace(/\./g, '_')
                    + '-' + (_product.qbs.buildVariant == 'debug'
                             ? 'Debug' : 'Release')
            if (FileInfo.cleanPath) {
                setupBuildDir = FileInfo.cleanPath(setupBuildDir)
            }
            File.remove(target + '.user')
            try { File.remove(setupBuildDir) } catch (msg) { console.warn(msg) }

            found = true
        }
    }
}
