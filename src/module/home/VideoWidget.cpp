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
    , areaSize_(30, 12)
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
        const QString name = cameraInfo.deviceName();
        //if (cameraInfo.deviceName() == QLatin1String("mycamera")) {
        if (true) { //TODO
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

QSize VideoWidget::areaSize() const
{
    return areaSize_;
}

void VideoWidget::setAreaSize(const QSize &size)
{
    if (size != areaSize_) {
        areaSize_ = size;
        update();
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

    QImage image(imageCaptured_.width(), imageCaptured_.height(), QImage::Format_RGBA8888);
    QPainter painterImage(&image);
    painterImage.setPen(QPen(QColor(255, 0, 0), 2));

    for (auto citer = contours_.crbegin(); citer != contours_.crend(); ++citer) {
        const auto &contour = *citer;
        //
        const cv::Rect rect = cv::boundingRect(contour);
        //qCritical().noquote() << rect.width << rect.height;
        if ((rect.width >= binaryImage_.cols)
                || (rect.height >= areaSize_.width() * 2)) {
            continue;
        }
        painterImage.drawRect(rect.x, rect.y, rect.width, rect.height);
    }

    const QRect rect = this->rect();
    QPainter painter(this);
    painter.setPen(QPen(QColor(255, 0, 0), 2));
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.scaled(rect.width(), rect.height(), Qt::KeepAspectRatio);
    painter.drawPixmap(rect.center() - QPointF(pixmap.width(), pixmap.height()) / 2, pixmap);
}
