#include "OCRMgr.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>
#include <tesseract/strngs.h>
#include <QCoreApplication>
#include <QDebug>

QImage cvMatToQImage(const cv::Mat &inMat)
{
    switch (inMat.type())
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );
#else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
            sColorTable.resize( 256 );

            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
#endif

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

QPixmap cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(cvMatToQImage(inMat));
}

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

QStringList OCRMgr::test(const QString &filePath, const QSize &size,
                         QPixmap *pmSource, QPixmap *pmBinary)
{
#if 0
    const QString imagePath = QCoreApplication::applicationDirPath()
            .append(QLatin1String("/image/5.png"));
#else
    const QString imagePath = filePath;
#endif
    const std::string sImagePath = imagePath.toStdString();

    // Load image
    cv::Mat imSource = cv::imread(sImagePath);
    if (imSource.empty()) {
        qCritical().noquote() << QLatin1String("Cannot open source image!");
        return QStringList();
    }
#if 0
    cv::Mat imSourceSmall;
    cv::resize(imSource, imSourceSmall, cv::Size(), 0.5, 0.5, cv::INTER_AREA);
    imSource = imSourceSmall;
#endif
#if 0
    //
    cv::Mat imBlur;
    cv::blur(imSource, imBlur, cv::Size(5, 5));

    //
    cv::Mat imMask;
    cv::Rect rect;
    cv::floodFill(imBlur, imMask, cv::Point(imBlur.cols - 1, imBlur.rows - 1),
                  cv::Scalar(255, 255, 255), &rect, cv::Scalar(3, 3, 3), 8);
#endif
    //
    cv::Mat imGray;
    cv::cvtColor(imSource, imGray, CV_BGR2GRAY);

    //
    //cv::blur(imGray, imGray, cv::Size(5, 5));

    //
    cv::Mat imNoMarker, imBinary;
    cv::threshold(imGray, imBinary, 100, 255, cv::THRESH_BINARY);
#if 0
    cv::Mat emKernel0 = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    cv::Mat imDilate;
    cv::erode(imBinary, imDilate, emKernel0, cv::Point(-1, -1), 1);
    imDilate.copyTo(imBinary);
#endif
#if 1
    // open / close
    cv::Mat emKernelOpenClose = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3));
    cv::Mat imOpened;
    cv::morphologyEx(imBinary, imOpened, cv::MORPH_OPEN, emKernelOpenClose);
    cv::Mat imClosed;
    cv::morphologyEx(imOpened, imClosed, cv::MORPH_CLOSE, emKernelOpenClose);
#endif
    std::vector< std::vector<cv::Point> > contours;
    //
#if 1
    cv::Mat emKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size.width(), size.height()));
    cv::Mat imErode;
    cv::erode(imClosed, imErode, emKernel);
    cv::findContours(imErode, contours, cv::RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
#else
    cv::Mat emKernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(6, 6));
    cv::Mat imDilate;
    cv::dilate(imBinary, imDilate, emKernel, cv::Point(-1, -1), 1);
    cv::findContours(imDilate, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
#endif

    qCritical().noquote() << QLatin1String("count of contours:") << contours.size();

    // Pass it to Tesseract API
    tesseract::TessBaseAPI tess;
    tess.Init(JMain::tessdataDir().toLocal8Bit().data(), "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetSourceResolution(70);
    tess.SetImage(reinterpret_cast<uchar*>(imBinary.data), imBinary.cols, imBinary.rows,
                  1, imBinary.cols);

    //qCritical().noquote() << "source:" << imSource.cols << imSource.rows;

#if 1
    QStringList sections;

    for (auto citer = contours.crbegin(); citer != contours.crend(); ++citer) {
        const auto &contour = *citer;
        //
        const cv::Rect rect = cv::boundingRect(contour);
        //qCritical().noquote() << rect.width << rect.height;
        if ((rect.width >= imBinary.cols)
                || (rect.height >= size.width() * 2)) {
            continue;
        }
        //
        cv::rectangle(imSource, rect, cv::Scalar(0, 0, 255), 2);
        //
        tess.SetRectangle(rect.x, rect.y, rect.width, rect.height);
        QString text = QString::fromUtf8(tess.GetUTF8Text()).trimmed();
        // remove charactor ',' and ' '
        text.replace(QLatin1Char(','), QLatin1Char('.'));
        text.remove(QLatin1Char(' '));

        sections.append(text);
    }
#else
    //cv::drawContours(resultImage, contours, -1, cv::Scalar(255),4);
    cv::drawContours(imContours, contours, -1, cv::Scalar::all(255));
#endif

#if 1
    //cv::imshow("source image", imSource);
    //cv::imshow("binary image", imBinary);
    //cv::imshow("opened image", imOpened);
    //cv::imshow("closed image", imClosed);
#if 0
    cv::imshow("gray image", imGray);
    //cv::imshow("no-marker image", imNoMarker);
    cv::imshow("erode image", imErode);
    //cv::imshow("dilate image", imDilate);
#endif
#endif
    //cv::waitKey(0);

    if (pmSource) {
        *pmSource = cvMatToQPixmap(imSource);
    }

    if (pmBinary) {
        *pmBinary = cvMatToQPixmap(imBinary);
    }

    tess.Clear();
    tess.End();

    return sections;
}
