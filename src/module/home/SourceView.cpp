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
#include <QSettings>
#include <QDebug>

SourceView::SourceView(QWidget *parent)
    : QWidget(parent)
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

    buttonRecognition_ = new JRoundButton(tr("Recognition"), this);
    buttonRecognition_->setFixedSize(150, 40);
    buttonRecognition_->setBorderRadius(20);
    layoutRight->addWidget(buttonRecognition_);

    stackedWidget_ = new QStackedWidget(this);
    stackedWidget_->setObjectName(QLatin1String("home.sourceview.stack"));
    layoutMain_->addWidget(stackedWidget_);

    videoWidget_ = new VideoWidget(this);
    videoWidget_->setClipedSize(settingsView_->reogArea());
    //videoWidget_->setResolution(QSize(480, 800));
    stackedWidget_->addWidget(videoWidget_);

    imageLabel_ = new ImageLabel(this);
    imageLabel_->setObjectName(QLatin1String("_image_"));
    imageLabel_->setClickable(true);
    stackedWidget_->addWidget(imageLabel_);

    connect(settingsView_, &SettingsView::ReogAreaChanged, this, [=](const QSize &size){
        videoWidget_->setClipedSize(size);
        Q_EMIT reogAreaChanged(size);
        if (stackedWidget_->currentIndex() == 0) {
            if (videoWidget_) {
                videoWidget_->update();
            }
        }
    });
    connect(settingsView_, &SettingsView::thresholdChanged, this, [=](int value){
        Q_EMIT thresholdChanged(value);
        if (stackedWidget_->currentIndex() == 0) {
            if (videoWidget_) {
                videoWidget_->update();
            }
        }
    });
    connect(settingsView_, &SettingsView::anchorOpenCloseChanged, this, [=](const QSize &size){
        Q_EMIT anchorOpenCloseChanged(size);
        if (stackedWidget_->currentIndex() == 0) {
            if (videoWidget_) {
                videoWidget_->update();
            }
        }
    });
    connect(settingsView_, &SettingsView::anchorErodeChanged, this, [=](const QSize &size){
        Q_EMIT anchorErodeChanged(size);
        if (videoWidget_) {
            videoWidget_->setAnchorErode(size);
        }
        if (stackedWidget_->currentIndex() == 0) {
            if (videoWidget_) {
                videoWidget_->update();
            }
        }
    });
#if 0
    connect(videoWidget_, &VideoWidget::readyForCaptureChanged, this, [=](bool ready){
        Q_UNUSED(ready)
        updateStackCurrentIndex();
    });
#endif
    connect(videoWidget_, &VideoWidget::captured, this, [=](const QImage &image){
        const QImage imageCaptured = videoWidget_->imageCaptured();
        bool isFirst = imageCaptured.isNull();
        videoWidget_->setImageCaptured(videoWidget_->clipedImageCaptured(image));
        updateBoundRect();
        if (isFirst) {
            //Q_EMIT captured(image);
        }
        //
        if (videoWidget_) {
            videoWidget_->capture();
        }
    });
    connect(videoWidget_, &VideoWidget::anchorErodeChanged, this, &SourceView::anchorErodeChanged);

    connect(stackedWidget_, &QStackedWidget::currentChanged, this, [=](int index){
        Q_UNUSED(index)
        Q_EMIT filePathChanged(QString());
        updateStackCurrentIndex();
    });
    connect(imageLabel_, &ImageLabel::filePathChanged, [=](const QString &filePath){
        if (filePath.isEmpty()) {
            setSourceImage(QPixmap());
        }
        Q_EMIT filePathChanged(filePath);
    });
    connect(buttonResetSettings_, &JRoundButton::clicked, [=](){
        settingsView_->reset();
    });
    connect(buttonRecognition_, &JRoundButton::clicked, this, [=](){
        switch (stackedWidget_->currentIndex()) {
        case 0:
        {
            const QImage imageCaptured = videoWidget_->imageCaptured();
            if (imageCaptured.isNull()) {
                videoWidget_->capture();
            } else {
                Q_EMIT captured(imageCaptured);
            }
            break;
        }
        case 1:
        {
            Q_EMIT recognitionClicked();
            break;
        }
        default:
            break;
        }
    });
    connect(buttonSwitchView_, &JRoundButton::clicked, [=](){
        if (currentIndex() == 0) {
            setCurrentIndex(1);
        } else {
            setCurrentIndex(0);
        }
    });

    //
    if (videoWidget_) {
        videoWidget_->setAnchorErode(settingsView_->anchorErode());
    }

    timerTrack_ = new QTimer(this);
    timerTrack_->setSingleShot(true);
    connect(timerTrack_, &QTimer::timeout, this, [=](){
        if (videoWidget_) {
            if (!videoWidget_->start()) {
                timerTrack_->start(50);
            }
        }
    });
    timerTrack_->start(50);

    if (videoWidget_) {
        videoWidget_->setAnchorErode(settingsView_->anchorErode());
    }

    //
    startCapture();
}

SourceView::~SourceView()
{
    stopCapture();

    Jwt::saveWidgetState(stackedWidget_);

    QSettings settings;
    settings.beginGroup(QLatin1String("parameters"));
    settings.setValue(QLatin1String("reogArea"), settingsView_->reogArea());
    settings.setValue(QLatin1String("threshold"), threshold());
    settings.setValue(QLatin1String("anchorOpenClose"), anchorOpenClose());
    settings.setValue(QLatin1String("anchorErode"), anchorErode());
    settings.endGroup();
}

bool SourceView::init()
{
    bool result = true;

    result = result && videoWidget_->init();

    Jwt::restoreWidgetState(stackedWidget_);

    QSettings settings;
    settings.beginGroup(QLatin1String("parameters"));
    if (settings.contains(QLatin1String("reogArea"))) {
        settingsView_->setReogArea(settings.value(QLatin1String("reogArea")).toSize());
    }
    if (settings.contains(QLatin1String("threshold"))) {
        setThreshold(settings.value(QLatin1String("threshold")).toInt());
    }
    if (settings.contains(QLatin1String("anchorOpenClose"))) {
        setAnchorOpenClose(settings.value(QLatin1String("anchorOpenClose")).toSize());
    }
    if (settings.contains(QLatin1String("anchorErode"))) {
        setAnchorErode(settings.value(QLatin1String("anchorErode")).toSize());
    }
    settings.endGroup();

    //
    updateStackCurrentIndex();

    return result;
}

const cv::Mat &SourceView::binaryImage() const
{
    if (stackedWidget_->currentIndex() == 0) {
        return videoWidget_->binaryImage();
    } else {
        return binaryImage_;
    }
}

const std::vector<std::vector<cv::Point> > &SourceView::contours() const
{
    if (stackedWidget_->currentIndex() == 0) {
        return videoWidget_->contours();
    } else {
        return contours_;
    }
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
    return int(settingsView_->threshold());
}

QSize SourceView::anchorOpenClose() const
{
    return settingsView_->anchorOpenClose();
}

QSize SourceView::anchorErode() const
{
    return settingsView_->anchorErode();
}

QString SourceView::filePath() const
{
    if (imageLabel_) {
        return imageLabel_->filePath();
    } else {
        return QString();
    }
}

void SourceView::startCapture()
{
    if (!timerTrack_->isActive()) {
        timerTrack_->start();
    }
#if 0
    if (videoWidget_->isCameraValid()) {
        videoWidget_->start();
    }
#endif
}

void SourceView::stopCapture()
{
    if (timerTrack_->isActive()) {
        timerTrack_->stop();
        QCoreApplication::removePostedEvents(this, QEvent::Timer);
    }

    if (videoWidget_) {
        videoWidget_->stop();
        QCoreApplication::processEvents();
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
    settingsView_->setThreshold(value);
}

void SourceView::setAnchorOpenClose(const QSize &size)
{
    settingsView_->setAnchorOpenClose(size);
}

void SourceView::setAnchorErode(const QSize &size)
{
    settingsView_->setAnchorErode(size);
}

bool SourceView::updateImage(cv::Mat &imSource)
{
    setSourceImage(QPixmap());
    binaryImage_.release();
    contours_.clear();

    const QString filePath = this->filePath();
    QPixmap pmSource;
    //
    if (!OCRMgr::boundRectImage(contours_, filePath, imSource, binaryImage_,
                                settingsView_->threshold(), settingsView_->anchorOpenClose(),
                                settingsView_->anchorErode(), &pmSource)) {
        return false;
    }

    setSourceImage(pmSource);

    return true;
}

bool SourceView::updateBoundRect()
{
    videoWidget_->releaseBinaryImage();
    update();

    //
    const QImage imageCaptured = videoWidget_->imageCaptured();
    std::vector<std::vector<cv::Point> > &contours = videoWidget_->contours();
    cv::Mat imSource, imBinary;

    //
    if (!OCRMgr::boundRectImage(contours, imageCaptured, imSource, imBinary,
                                settingsView_->threshold(), settingsView_->anchorOpenClose(),
                                settingsView_->anchorErode())) {
        videoWidget_->update();
        return false;
    }

    videoWidget_->setBinaryImage(imBinary);     // save

    Q_EMIT binaryImageUpdated();

    videoWidget_->update();

    return true;
}

void SourceView::updateStackCurrentIndex()
{
    switch (stackedWidget_->currentIndex()) {
    case 0:
        settingsView_->setReogAreaVisible(true);
        startCapture();
        if (videoWidget_->isCameraValid()) {
            buttonRecognition_->show();
        }
        break;
    case 1:
        settingsView_->setReogAreaVisible(false);
        stopCapture();
        Q_EMIT filePathChanged(imageLabel_->filePath());
        break;
    default:
        break;
    }
}
