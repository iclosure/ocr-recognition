import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import qbs.TextFile
import tools.EnvUtils

PackageApp {
    name: 'com.smartsoft.desktop.app'
    type: base.concat([ 'data.tools.exe.out' ])

    installSystem32Api: false

    // config
    Group {
        name: 'data-config'
        prefix: FileInfo.joinPaths(project.sourceDirectory, 'config') + '/'
        files: [ '**/*.*' ]
        excludeFiles: [ '**/*.pr[io]', '**/*.qbs', "**/~*" ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'config'
        qbs.installSourceBase: prefix
    }

    // app
    Group {
        name: 'data-app'
        prefix: FileInfo.joinPaths(projectDir, 'bin') + '/'
        files: [ project.projectName + project.variantSuffix + '.exe' ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'bin'
    }

    // tools
    Group {
        id: dataTools
        condition: false
        name: 'data-tools'
        prefix: project.sourceDirectory + '/tools/'
        files: [ 'WinSnap/*' ]
        fileTags: [ 'data.tools.exe.in' ]
    }

    Rule {
        inputs: [ 'data.tools.exe.in' ]
        Artifact {
            fileTags: [ 'data.tools.exe.out' ]
            filePath: {
                var filePath = input.filePath;
                if (filePath.endsWith('.exe.in')) {
                    filePath = FileInfo.path(filePath) + '/' + input.completeBaseName;
                }
                var filePath = FileInfo.joinPaths(product.dataTargetPath,
                                                  FileInfo.relativePath(project.sourceDirectory, filePath));
                return filePath;
            }
        }
        prepare: {
            var cmd = new JavaScriptCommand;
            cmd.description = 'coping file ' + output.filePath;
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath); }
            return [ cmd ];
        }
    }

    // 3rdpart - opencv
    Group {
        name: 'data-app-opencv'
        condition: !project.useVcPkgStatic
        prefix: {
            if (project.useVcPkg) {
                return project.useVcPkg ? project.vcpkgLibBin : project.opencvDir + '/bin/'
            } else {
                return project.opencvDir + '/'
            }
        }
        files: {
            var items = []
            if (project.useVcPkg) {
                if (!project.useVcPkgStatic) {
                    items.push('jpeg62.dll')
                    items.push('zlib' + project.variantSuffix + '1.dll')
                    items.push('webp' + EnvUtils.dylibSuffix(qbs))
                    items.push('libpng16' + EnvUtils.dylibSuffix(qbs))
                    items.push('tiff' + EnvUtils.dylibSuffix(qbs))
                    items.push('lzma' + EnvUtils.dylibSuffix(qbs))
                    items.push('opencv_core' + EnvUtils.dylibSuffix(qbs))
                    items.push('opencv_imgcodecs' + EnvUtils.dylibSuffix(qbs))
                    items.push('opencv_imgproc' + EnvUtils.dylibSuffix(qbs))
                    items.push('opencv_photo' + EnvUtils.dylibSuffix(qbs))
                    items.push('leptonica-1.78.0' + EnvUtils.dylibSuffix(qbs))
                }
            } else {
                items = [
                            'bin/opencv_videoio_ffmpeg' + project.opencvVersion + '_64.dll',
                            'x64/vc15/bin/opencv_world' + project.opencvVersion + '.dll'
                        ]
            }
            return items
        }

        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'bin'
    }

    // 3rdpart - tesseract
    Group {
        name: 'data-app-tesseract'
        condition: !project.useVcPkg && !project.useVcPkgStatic
        prefix: FileInfo.joinPaths(project.tesseractDir, 'bin') + '/'
        files: [ 'pvt.cppan.demo.*.dll', 'tesseract*[^d].dll' ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'bin'
    }

    // 3rdpart - tessdata
    Group {
        name: 'data-app-tessdata'
        prefix: project.sourceDirectory + '/tools/tessdata/'
        files: [
            '*.traineddata'
        ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'tessdata'
    }
}
