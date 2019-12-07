#include "OCRMgr.h"
#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>
#include <tesseract/strngs.h>
#include <QCoreApplication>
#include <QDebug>

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

void OCRMgr::qImageToCvMat(const QImage &image, cv::OutputArray &matOut)
{
    switch(image.format()) {
    case QImage::Format_Invalid:
    {
        cv::Mat empty;
        empty.copyTo(matOut);
        break;
    }
    case QImage::Format_RGB32:
    {
        cv::Mat view(image.height(), image.width(), CV_8UC4,
                     static_cast<void*>(const_cast<uchar*>(image.constBits())),
                     size_t(image.bytesPerLine()));
        view.copyTo(matOut);
        break;
    }
    case QImage::Format_RGB888:
    {
        cv::Mat view(image.height(), image.width(), CV_8UC3,
                     static_cast<void*>(const_cast<uchar*>(image.constBits())),
                     size_t(image.bytesPerLine()));
        cvtColor(view, matOut, cv::COLOR_RGB2BGR);
        break;
    }
    default:
    {
        QImage conv = image.convertToFormat(QImage::Format_ARGB32);
        cv::Mat view(conv.height(), conv.width(), CV_8UC4,
                     static_cast<void*>(const_cast<uchar*>(image.constBits())),
                     size_t(image.bytesPerLine()));
        view.copyTo(matOut);
        break;
    }
    }
}

QImage OCRMgr::cvMatToQImage(const cv::Mat &inMat)
{
    switch (inMat.type()) {
    case CV_8UC4:       // 8-bit, 4 channel
    {
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step),
                     QImage::Format_ARGB32);
        return image;
    }
    case CV_8UC3:       // 8-bit, 3 channel
    {
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step),
                     QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    case CV_8UC1:       // 8-bit, 1 channel
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step),
                     QImage::Format_Grayscale8);
#else
        static QVector<QRgb> sColorTable;

        // only create our color table the first time
        if (sColorTable.isEmpty()) {
            sColorTable.resize(256);

            for (int i = 0; i < 256; ++i) {
                sColorTable[i] = qRgb(i, i, i);
            }
        }

        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step),
                     QImage::Format_Indexed8);
        image.setColorTable(sColorTable);
#endif
        return image;
    }
    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

QPixmap OCRMgr::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(cvMatToQImage(inMat));
}

QStringList OCRMgr::test(const cv::Mat &imBinary,
                         const std::vector<std::vector<cv::Point> > &contours,
                         const QSize &erodeSize)
{
    if (imBinary.empty()) {
        return QStringList();
    }

    // Pass it to Tesseract API
    tesseract::TessBaseAPI tess;
    tess.Init(JMain::tessdataDir().toLocal8Bit().data(), "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage(reinterpret_cast<uchar*>(imBinary.data), imBinary.cols, imBinary.rows,
                  1, imBinary.cols);
    tess.SetSourceResolution(300);

    QStringList sections;

    for (auto citer = contours.crbegin(); citer != contours.crend(); ++citer) {
        const auto &contour = *citer;
        //
        const cv::Rect rect = cv::boundingRect(contour);
        //qCritical().noquote() << rect.width << rect.height;
        if ((rect.width >= imBinary.cols)
                || (rect.height >= erodeSize.width() * 2)) {
            continue;
        }
        //
        tess.SetRectangle(rect.x, rect.y, rect.width, rect.height);
        QString text = QString::fromUtf8(tess.GetUTF8Text()).trimmed();
        // remove charactor ',' and ' '
        text.replace(QLatin1Char(','), QLatin1Char('.'));
        text.remove(QLatin1Char(' '));

        sections.append(text);
    }

    tess.Clear();
    tess.End();

    return sections;
}

QStringList OCRMgr::test(cv::Mat imSource, int threshold, const QSize &anchorOpenClose,
                         const QSize &erodeSize, QPixmap *pmSource, QPixmap *pmBinary)
{
    if (imSource.empty()) {
        return QStringList();
    }

    QSize newSize = erodeSize;
    const int factor = 3;

#if 1
    cv::Mat imSourceScaled;
    cv::resize(imSource, imSourceScaled, cv::Size(), factor, factor, cv::INTER_LINEAR);
    imSourceScaled.copyTo(imSource);
    newSize *= 2;
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
    cv::threshold(imGray, imBinary, threshold, 255, cv::THRESH_BINARY);

    if (!removeInvalidLine(imBinary)) {
        return QStringList();
    }

#if 0
    cv::Mat emKernel0 = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    cv::Mat imDilate;
    cv::erode(imBinary, imDilate, emKernel0, cv::Point(-1, -1), 1);
    imDilate.copyTo(imBinary);
#endif
#if 1
    // open / close
    cv::Mat emKernelOpenClose = cv::getStructuringElement(
                cv::MORPH_RECT, cv::Size(anchorOpenClose.width() * factor,
                                         anchorOpenClose.height() * factor));
    cv::Mat imOpened;
    cv::morphologyEx(imBinary, imOpened, cv::MORPH_OPEN, emKernelOpenClose);
    cv::Mat imClosed;
    cv::morphologyEx(imOpened, imClosed, cv::MORPH_CLOSE, emKernelOpenClose);
#endif
    std::vector<std::vector<cv::Point> > contours;
    //
#if 1
    cv::Mat emKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(newSize.width(), newSize.height()));
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
#if 0
    cv::Mat copiedBinary;
    imBinary.copyTo(copiedBinary);
    const int width = copiedBinary.cols;
    const int height = copiedBinary.rows;
    const double aspect = double(width) / double(height);
    cv::resize(copiedBinary, copiedBinary, cv::Size2d(),
               aspect * 2, aspect * 2, cv::INTER_LINEAR);
    tess.SetImage(reinterpret_cast<uchar*>(copiedBinary.data), copiedBinary.cols, copiedBinary.rows,
                  1, copiedBinary.cols);
#else
    tess.SetImage(reinterpret_cast<uchar*>(imBinary.data), imBinary.cols,
                  imSourceScaled.rows, 1, imBinary.cols);
#endif
    tess.SetSourceResolution(96);

    //qCritical().noquote() << "source:" << imSource.cols << imSource.rows;

#if 1
    QStringList sections;

    for (auto citer = contours.crbegin(); citer != contours.crend(); ++citer) {
        const auto &contour = *citer;
        //
        const cv::Rect rect = cv::boundingRect(contour);
        //qCritical().noquote() << rect.width << rect.height;
        if ((rect.width >= imBinary.cols)
                || (rect.height >= newSize.width() * 2)) {
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

QStringList OCRMgr::test(const QString &filePath, int threshold, const QSize &anchorOpenClose,
                         const QSize &erodeSize, QPixmap *pmSource, QPixmap *pmBinary)
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

    return test(imSource, threshold, anchorOpenClose, erodeSize, pmSource, pmBinary);
}

QStringList OCRMgr::test(const QImage &image, int threshold, const QSize &anchorOpenClose,
                         const QSize &erodeSize, QPixmap *pmSource, QPixmap *pmBinary)
{
    if (image.isNull()) {
        return QStringList();
    }

    cv::Mat imSource;

    qImageToCvMat(image, imSource);

    return test(imSource, threshold, anchorOpenClose, erodeSize, pmSource, pmBinary);
}

bool OCRMgr::removeInvalidLine(cv::Mat &imBinary)
{
    int a,k,m;

    for (int i = 0; i < imBinary.rows; ++i) {
        uchar *data = imBinary.ptr<uchar>(i);
        k = 0;
        for (int j = 0; j < imBinary.cols; ++j) {
            a = data[j];
            if (a == 0) {
                k++;
            } else {
                k = 0;
            }

            if (k > imBinary.cols / 8 ) {
                for (m = 0; m < imBinary.cols; ++m) {
                    data[m] = 255;
                }
                j = imBinary.rows;
            }
        }
    }

    return true;
}
