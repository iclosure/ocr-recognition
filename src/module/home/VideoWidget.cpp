#include "VideoWidget.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QPainter>
#include <QDebug>

// class ImageLabel

VideoWidget::VideoWidget(QWidget *parent)
    : QCameraViewfinder(parent)
    , camera_(nullptr)
    , cameraImageCapture_(nullptr)
    , defaultAnchorErode_(30, 12)
    , anchorErode_(defaultAnchorErode_)
{

}

VideoWidget::~VideoWidget()
{
    stop();
}

bool VideoWidget::init()
{
    if (camera_) {
        qCritical().noquote() << QLatin1String("CameraView module has been inited!");
        return true;
    }

    // init camera
#if 1
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras) {
        //const QString name = cameraInfo.deviceName();
        //const QString description = cameraInfo.description();
#if 1
        if (cameraInfo.description() == QLatin1String("aoni webcam A25")) {
#else
        if (true) { //TODO
#endif
            camera_ = new QCamera(cameraInfo);
            break;
        }
    }

    if (!camera_) {
        return false;
    }
#else
    camera_ = new QCamera(QCamera::FrontFace, this);
#endif

    cameraImageCapture_ = new QCameraImageCapture(camera_, this);

    QImageEncoderSettings encodingSettings = cameraImageCapture_->encodingSettings();
    encodingSettings.setResolution(1920, 1080);
    //encodingSettings.setResolution(500, 900);
    encodingSettings.setQuality(QMultimedia::VeryHighQuality);
    cameraImageCapture_->setEncodingSettings(encodingSettings);

    camera_->setViewfinder(this);
#if 0
    QCameraViewfinderSettings viewFinderSettings = camera_->viewfinderSettings();
    //viewFinderSettings.setResolution(preferred_resolution);
    viewFinderSettings.setPixelFormat(QVideoFrame::Format_BGRA32);
    viewFinderSettings.setMaximumFrameRate(15);
    camera_->setViewfinderSettings(viewFinderSettings);
#endif
    connect(cameraImageCapture_, &QCameraImageCapture::imageCaptured, this,
            [=](int id, const QImage &preview){
        Q_UNUSED(id)
        Q_EMIT captured(preview);
    });

    camera_->start(); // to start the viewfinder

    return true;
}

void VideoWidget::updateBoundRect(const std::vector<std::vector<cv::Point> > &contours)
{
    contours_ = contours;
    update();
}

QCamera *VideoWidget::camera() const
{
    return camera_;
}

QCameraImageCapture *VideoWidget::cameraImageCapture() const
{
    return cameraImageCapture_;
}

std::vector<std::vector<cv::Point> > &VideoWidget::contours()
{
    return contours_;
}

const std::vector<std::vector<cv::Point> > &VideoWidget::contours() const
{
    return contours_;
}

bool VideoWidget::isCameraValid() const
{
    return (camera_ != nullptr);
}

QImage VideoWidget::imageCaptured() const
{
    return imageCaptured_;
}

void VideoWidget::setImageCaptured(const QImage &image)
{
    imageCaptured_ = image;
    update();
}

QImage VideoWidget::clipedImageCaptured(const QImage &image) const
{
    if (clipedSize_.isValid()) {
        const int imageWidth = image.width();
        const int imageHeight = image.height();
        const int clipedWidth = clipedSize_.width();
        const int clipedHeight = clipedSize_.height();
        if (imageWidth > clipedWidth && imageHeight > clipedHeight) {
            return image.copy((imageWidth - clipedSize_.width()) / 2,
                              (imageHeight - clipedSize_.height()) / 2,
                              clipedSize_.width(), clipedSize_.height());
        }
    }

    return image;
}

QSize VideoWidget::anchorErode() const
{
    return anchorErode_;
}

void VideoWidget::setAnchorErode(const QSize &size)
{
    if (size != anchorErode_) {
        anchorErode_ = size;
        Q_EMIT anchorErodeChanged(size);
        update();
    }
}

QSize VideoWidget::defaultAnchorErode() const
{
    return defaultAnchorErode_;
}

QSize VideoWidget::clipedSize() const
{
    return clipedSize_;
}

void VideoWidget::setClipedSize(const QSize &size)
{
    if (size != anchorErode_) {
        clipedSize_ = size;
        update();
    }
}

QSize VideoWidget::resolution() const
{
    if (cameraImageCapture_) {
        QImageEncoderSettings encodingSettings = cameraImageCapture_->encodingSettings();
        return encodingSettings.resolution();
    } else {
        return QSize();
    }
}

void VideoWidget::setResolution(const QSize &resolution)
{
    if (cameraImageCapture_) {
        QImageEncoderSettings encodingSettings = cameraImageCapture_->encodingSettings();
        encodingSettings.setResolution(resolution);
        cameraImageCapture_->setEncodingSettings(encodingSettings);
    }
}

const cv::Mat &VideoWidget::binaryImage() const
{
    return binaryImage_;
}

void VideoWidget::setBinaryImage(cv::Mat image)
{
    binaryImage_ = image;
}

void VideoWidget::releaseBinaryImage()
{
    if (!binaryImage_.empty()) {
        binaryImage_.release();
        update();
    }
}

bool VideoWidget::start()
{
    if (!camera_) {
        return false;
    }

    if (!camera_->isAvailable()) {
        return false;
    }

    camera_->start();

    return true;
}

void VideoWidget::stop()
{
    if (!camera_) {
        return;
    }

    if (!camera_->isAvailable()) {
        return;
    }

    camera_->stop();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QCameraViewfinder::paintEvent(event);

    if (binaryImage_.empty()) {
        return;
    }

    QImageEncoderSettings encodingSettings = cameraImageCapture_->encodingSettings();
    const QSize resolution = encodingSettings.resolution();
    const int imageWidth = resolution.width();
    const int imageHeight = resolution.height();
    if (resolution.isEmpty()) {
        return;
    }

    QImage image(resolution.width(), resolution.height(), QImage::Format_RGBA8888);
    QPainter painterImage(&image);
    // rectange
    const int x = (imageWidth - clipedSize_.width()) / 2;
    const int y = (imageHeight - clipedSize_.height()) / 2;
    if (clipedSize_.isValid() && imageWidth > clipedSize_.width()
            && imageHeight > clipedSize_.height()) {
        painterImage.setPen(QPen(QColor(0, 0, 255), 8));
        painterImage.drawRect(QRect(x, y, clipedSize_.width(), clipedSize_.height()));
    }
    // contours
    painterImage.setPen(QPen(QColor(255, 0, 0), 4));
    for (auto citer = contours_.crbegin(); citer != contours_.crend(); ++citer) {
        const auto &contour = *citer;
        //
        const cv::Rect rect = cv::boundingRect(contour);
        //qCritical().noquote() << rect.width << rect.height;
        if ((rect.width >= binaryImage_.cols) || (rect.height >= anchorErode_.width() * 2)) {
            continue;
        }
        painterImage.drawRect(x + rect.x, y + rect.y, rect.width, rect.height);
    }

    const QRect rect = this->rect();
    QPainter painter(this);
    painter.setPen(QPen(QColor(255, 0, 0), 2));
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.scaled(rect.width(), rect.height(), Qt::KeepAspectRatio);
    painter.drawPixmap(rect.center() - QPointF(pixmap.width(), pixmap.height()) / 2, pixmap);
}
