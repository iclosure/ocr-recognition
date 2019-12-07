#include "SourceView.h"
#include "ImageLabel.h"
#include "jwt/widget/JRoundButton.h"
#include "common/OCRMgr.h"
#include "SettingsView.h"
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
    , defaultThreshold_(130)
    , defaultAnchorOpenClose_(17, 3)
    , threshold_(defaultThreshold_)
    , anchorOpenClose_(defaultAnchorOpenClose_)
{
    layoutMain_ = new QVBoxLayout(this);

    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->setSpacing(10);
    layoutMain_->addLayout(layoutTop);

    settingsView_ = new SettingsView(this);
    layoutTop->addWidget(settingsView_);

    QVBoxLayout *layoutRight = new QVBoxLayout();
    layoutRight->setSpacing(8);
    layoutTop->addLayout(layoutRight);

    buttonResetSettings_ = new JRoundButton(tr("Reset Settings"), this);
    buttonResetSettings_->setFixedSize(150, 40);
    buttonResetSettings_->setBorderRadius(20);
    layoutRight->addWidget(buttonResetSettings_);

    buttonSwitchView_ = new JRoundButton(tr("Switch View"), this);
    buttonSwitchView_->setFixedSize(150, 40);
    buttonSwitchView_->setBorderRadius(20);
    layoutRight->addWidget(buttonSwitchView_);

    buttonCapture_ = new JRoundButton(tr("Capture"), this);
    buttonCapture_->setFixedSize(150, 40);
    buttonCapture_->setBorderRadius(20);
    buttonCapture_->hide();
    layoutRight->addWidget(buttonCapture_);

    stackedWidget_ = new QStackedWidget(this);
    stackedWidget_->setObjectName(QLatin1String("home.sourceview.stack"));
    layoutMain_->addWidget(stackedWidget_);

    videoWidget_ = new VideoWidget(this);
    videoWidget_->setClipedSize(QSize(480, 800));
    //videoWidget_->setResolution(QSize(480, 800));
    stackedWidget_->addWidget(videoWidget_);

    imageLabel_ = new ImageLabel(this);
    imageLabel_->setObjectName(QLatin1String("_image_"));
    imageLabel_->setClickable(true);
    stackedWidget_->addWidget(imageLabel_);

    connect(settingsView_, &SettingsView::thresholdChanged, this, [=](int value){
        setThreshold(value);
    });
    connect(settingsView_, &SettingsView::anchorOpenCloseChanged, this, [=](const QSize &size){
        setAnchorOpenClose(size);
    });
    connect(settingsView_, &SettingsView::anchorErodeChanged, this, [=](const QSize &size){
        setAnchorErode(size);
    });

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
        videoWidget_->setImageCaptured(videoWidget_->clipedImageCaptured(image));
        updateBoundRect();
        if (isFirst) {
            //Q_EMIT captured(image);
        }
    });
    connect(videoWidget_, &VideoWidget::anchorErodeChanged, this, &SourceView::anchorErodeChanged);

    connect(imageLabel_, &ImageLabel::filePathChanged, [=](const QString &filePath){
        Q_EMIT filePathChanged(filePath);
    });
    connect(buttonResetSettings_, &JRoundButton::clicked, [=](){
        settingsView_->setThreshold(defaultThreshold());
        settingsView_->setAnchorOpenClose(defaultAnchorOpenClose());
        if (videoWidget_) {
            settingsView_->setAnchorErode(videoWidget_->defaultAnchorErode());
        }
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

    //
    settingsView_->setThreshold(threshold());
    settingsView_->setAnchorOpenClose(anchorOpenClose());
    settingsView_->setAnchorErode(anchorErode());
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

int SourceView::currentIndex() const
{
    return stackedWidget_->currentIndex();
}

void SourceView::setCurrentIndex(int index)
{
    stackedWidget_->setCurrentIndex(index);
}

int SourceView::threshold() const
{
    return threshold_;
}

QSize SourceView::anchorOpenClose() const
{
    return anchorOpenClose_;
}

QSize SourceView::anchorErode() const
{
    if (videoWidget_) {
        return videoWidget_->anchorErode();
    } else {
        return QSize();
    }
}

int SourceView::defaultThreshold() const
{
    return defaultThreshold_;
}

QSize SourceView::defaultAnchorOpenClose() const
{
    return defaultAnchorOpenClose_;
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

void SourceView::setThreshold(int value)
{
    if (value < 0 || value > 255) {
        return;
    }

    if (value != threshold_) {
        threshold_ = value;
        Q_EMIT thresholdChanged(value);
        if (videoWidget_) {
            videoWidget_->update();
        }
    }
}

void SourceView::setAnchorOpenClose(const QSize &size)
{
    if (size != anchorOpenClose_) {
        anchorOpenClose_ = size;
        Q_EMIT anchorOpenCloseChanged(size);
        if (videoWidget_) {
            videoWidget_->update();
        }
    }
}

void SourceView::setAnchorErode(const QSize &size)
{
    if (videoWidget_) {
        videoWidget_->setAnchorErode(size);
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

    const QSize anchorErode = videoWidget_->anchorErode();

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
    cv::threshold(imGray, imBinary, threshold_, 255, cv::THRESH_BINARY);

    // remove invalid line
    if (!OCRMgr::removeInvalidLine(imBinary)) {
        //
    }

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
    cv::Mat emKernelOpenClose = cv::getStructuringElement(
                cv::MORPH_RECT, cv::Size(anchorOpenClose_.width(), anchorOpenClose_.height()));
    cv::Mat imOpened;
    cv::morphologyEx(imBinary, imOpened, cv::MORPH_OPEN, emKernelOpenClose);
    cv::Mat imClosed;
    cv::morphologyEx(imOpened, imClosed, cv::MORPH_CLOSE, emKernelOpenClose);
#endif
    //
#if 1
    cv::Mat emKernel = cv::getStructuringElement(
                cv::MORPH_RECT, cv::Size(anchorErode.width(), anchorErode.height()));
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
