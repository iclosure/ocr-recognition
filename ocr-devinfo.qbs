import qbs
import 'tools/qbs/imports' as I

I.JSolution {
    projectName: 'ocr-devinfo'
    projectDisplayName: 'OCR-DevInfo'

    readonly property path opencvDir: "C:/Users/iclosure/Documents/workspace/ai/opencv/build"
    readonly property path tesseractDir: "C:/Program Files/tesseract"
}
