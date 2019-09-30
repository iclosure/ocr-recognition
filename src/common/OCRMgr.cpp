#include "OCRMgr.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>
#include <tesseract/strngs.h>
#include <QCoreApplication>

// class OCRMgrPrivate

class OCRMgrPrivate
{
public:
    OCRMgrPrivate(OCRMgr *q)
        : J_QPTR(q)
    {

    }

    void init();

private:
    J_DECLARE_PUBLIC(OCRMgr)
};

void OCRMgrPrivate::init()
{
}

// class OCRMgr

J_IMPLEMENT_SINGLE_INSTANCE(OCRMgr, JMain)

OCRMgr::OCRMgr(QObject *parent)
    : QObject(parent)
    , J_DPTR(new OCRMgrPrivate(this))
{
    Q_D(OCRMgr);
    d->init();
}

OCRMgr::~OCRMgr()
{
    Q_D(OCRMgr);
    delete d;
}

bool OCRMgr::init()
{
    return true;
}

QString OCRMgr::test(const QString &filePath)
{
#if 0
    const QString imagePath = QCoreApplication::applicationDirPath()
            .append(QLatin1String("/image/5.png"));
#else
    const QString imagePath = filePath;
#endif
    const std::string sImagePath = imagePath.toStdString();

    // Load image
    cv::Mat im = cv::imread(sImagePath);
    if (im.empty()) {
        std::cout << "Cannot open source image!" << std::endl;
        return QString();
    }

    cv::Mat gray;
    cv::cvtColor(im, gray, CV_BGR2GRAY);

    // ...other image pre-processing here...

    // Pass it to Tesseract API
    tesseract::TessBaseAPI tess;
    tess.Init(nullptr, "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage(reinterpret_cast<uchar*>(gray.data), gray.cols, gray.rows, 1, gray.cols);

    // Get the text
    char* out = tess.GetUTF8Text();
    //std::cout << out << std::endl;

    return QString::fromStdString(std::string(out));
}

