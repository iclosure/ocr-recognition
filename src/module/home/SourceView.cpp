#include "SourceView.h"
#include "ImageLabel.h"
#include "jwt/widget/JRoundButton.h"
#include "common/OCRMgr.h"
#include "VideoWidget.h"
#include <QCamera>
#include <QCameraImageCapture>
#include <QLayout>
#include <QTimer>
#include <QCoreApplication>
#include <QStackedWidget>
#include <QDebug>

SourceView::SourceView(QWidget *parent)
    : QWidget(parent)
{
    layoutMain_ = new QVBoxLayout(this);
    layoutMain_->setContentsMargins(3, 3, 3, 3);
    layoutMain_->setSpacing(3);

    stackedWidget_ = new QStackedWidget(this);
    stackedWidget_->setObjectName(QLatin1String("home.sourceview.stack"));
    layoutMain_->addWidget(stackedWidget_);

    videoWidget_ = new VideoWidget(this);
    stackedWidget_->addWidget(videoWidget_);

    imageLabel_ = new ImageLabel(this);
    imageLabel_->setObjectName(QLatin1String("_image_"));
    imageLabel_->setClickable(true);
    stackedWidget_->addWidget(imageLabel_);

    QHBoxLayout *layoutBottom = new QHBoxLayout();
    layoutBottom->setAlignment(Qt::AlignHCenter);
    layoutMain_->addLayout(layoutBottom);

    buttonCapture_ = new JRoundButton(tr("Capture"), this);
    buttonCapture_->setFixedWidth(120);
    buttonCapture_->hide();
    layoutBottom->addWidget(buttonCapture_);

    buttonSwitchView_ = new JRoundButton(tr("Switch View"), this);
    buttonSwitchView_->setFixedWidth(120);
    layoutBottom->addWidget(buttonSwitchView_);

    connect(stackedWidget_, &QStackedWidget::currentChanged, this, [=](int index){
        switch (index) {
        case 0:
            startCapture();
            if (videoWidget_->isCameraValid()) {
                buttonCapture_->show();
                Q_EMIT filePathChanged(QString());
            }
            break;
        case 1:
            stopCapture();
            buttonCapture_->hide();
            Q_EMIT filePathChanged(imageLabel_->filePath());
            break;
        default:
            break;
        }
    });

    connect(videoWidget_, &VideoWidget::captured, this, [=](const QImage &image){
        const QImage imageCaptured = videoWidget_->imageCaptured();
        bool isFirst = imageCaptured.isNull();
        videoWidget_->setImageCaptured(image);
        updateBoundRect();
        if (isFirst) {
            //Q_EMIT captured(image);
        }
    });

    connect(imageLabel_, &ImageLabel::filePathChanged, [=](const QString &filePath){
        Q_EMIT filePathChanged(filePath);
    });
    connect(buttonCapture_, &JRoundButton::clicked, this, [=](){
        const QImage imageCaptured = videoWidget_->imageCaptured();
        if (imageCaptured.isNull()) {
            if (videoWidget_->cameraImageCapture()) {
                videoWidget_->cameraImageCapture()->capture();
            }
        } else {
            Q_EMIT captured(imageCaptured);
        }
    });
    connect(buttonSwitchView_, &JRoundButton::clicked, [=](){
        if (currentIndex() == 0) {
            setCurrentIndex(1);
        } else {
            setCurrentIndex(0);
        }
    });


    timerTrack_ = new QTimer(this);
    timerTrack_->setInterval(300);
    connect(timerTrack_, &QTimer::timeout, this, [=](){
        if (videoWidget_->cameraImageCapture()) {
            videoWidget_->cameraImageCapture()->capture();
        }
    });
    timerTrack_->start();
}

SourceView::~SourceView()
{
    stopCapture();

    Jwt::saveWidgetState(stackedWidget_);
}

bool SourceView::init()
{
    bool result = true;

    result = result && videoWidget_->init();

    if (result) {
        //videoWidget_->show();
        buttonCapture_->show();
    }

    Jwt::restoreWidgetState(stackedWidget_);

    return result;
}

const cv::Mat &SourceView::binaryImage() const
{
    return videoWidget_->binaryImage();
}

const std::vector<std::vector<cv::Point> > &SourceView::contours() const
{
    return videoWidget_->contours();
}

QSize SourceView::areaSize() const
{
    return videoWidget_->areaSize();
}

int SourceView::currentIndex() const
{
    return stackedWidget_->currentIndex();
}

void SourceView::setCurrentIndex(int index)
{
    stackedWidget_->setCurrentIndex(index);
}

void SourceView::startCapture()
{
    if (timerTrack_->isActive()) {
        return;
    }

    timerTrack_->start();
    if (videoWidget_->isCameraValid()) {
        videoWidget_->start();
    }
}

void SourceView::stopCapture()
{
    if (!timerTrack_->isActive()) {
        return;
    }

    timerTrack_->stop();
    QCoreApplication::removePostedEvents(this, QEvent::Timer);
    if (videoWidget_->cameraImageCapture()) {
        videoWidget_->cameraImageCapture()->cancelCapture();
    }
}

void SourceView::setSourceImage(const QPixmap &pixmap)
{
    if (imageLabel_) {
        imageLabel_->setPixmap(pixmap);
    }
}

bool SourceView::updateBoundRect()
{
    videoWidget_->releaseBinaryImage();
    update();
    //
    std::vector<std::vector<cv::Point> > &contours = videoWidget_->contours();
    contours.clear();

    const QImage imageCaptured = videoWidget_->imageCaptured();
    if (imageCaptured.isNull()) {
        videoWidget_->update();
        return false;
    }

    cv::Mat imSource;

    OCRMgr::qImageToCvMat(imageCaptured, imSource);

    if (imSource.empty()) {
        videoWidget_->update();
        return false;
    }

    const QSize areaSize = videoWidget_->areaSize();

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
    cv::threshold(imGray, imBinary, 120, 255, cv::THRESH_BINARY);

    videoWidget_->setBinaryImage(imBinary);     // save

    Q_EMIT binaryImageUpdated();

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
    //
#if 1
    cv::Mat emKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(areaSize.width(), areaSize.height()));
    cv::Mat imErode;
    cv::erode(imClosed, imErode, emKernel);
    cv::findContours(imErode, contours, cv::RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
#else
    cv::Mat emKernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(6, 6));
    cv::Mat imDilate;
    cv::dilate(imBinary, imDilate, emKernel, cv::Point(-1, -1), 1);
    cv::findContours(imDilate, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
#endif

    //qCritical().noquote() << QLatin1String("count of contours:") << contours.size();

    videoWidget_->update();

    return true;
}
