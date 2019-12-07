import qbs
import qbs.Environment
import 'tools/qbs/imports' as I

I.JSolution {
    projectName: 'ocr-devinfo'
    projectDisplayName: 'OCR-DevInfo'
    version: '1.0.1'
    buildVersion: 1

    readonly property path opencvDir: Environment.getEnv('OPENCV_HOME')
    //readonly property path tesseractDir: Environment.getEnv('Tesseract_DIR')
    readonly property path tesseractDir: "C:/Program Files/tesseract"
}
