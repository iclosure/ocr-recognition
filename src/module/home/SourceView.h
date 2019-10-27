#ifndef SOURCEVIEW_H
#define SOURCEVIEW_H

#include "global.h"
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

// class SourceView

class ImageLabel;
class QCameraViewfinder;
class JRoundButton;
class QVBoxLayout;
class QTimer;
class VideoWidget;
class QStackedWidget;

class SourceView : public QWidget
{
    Q_OBJECT
public:
    explicit SourceView(QWidget *parent = nullptr);
    ~SourceView() J_OVERRIDE;

    bool init();

    const cv::Mat &binaryImage() const;
    const std::vector<std::vector<cv::Point> > &contours() const;
    QSize areaSize() const;

    int currentIndex() const;
    void setCurrentIndex(int index);

Q_SIGNALS:
    void captured(const QImage &image);
    void filePathChanged(const QString &filePath);
    void binaryImageUpdated();

public Q_SLOTS:
    void startCapture();
    void stopCapture();
    void setSourceImage(const QPixmap &pixmap);

private:
    bool updateBoundRect();

private:
    Q_DISABLE_COPY(SourceView)
    QVBoxLayout *layoutMain_;
    QStackedWidget *stackedWidget_;
    VideoWidget *videoWidget_;
    ImageLabel *imageLabel_;
    JRoundButton *buttonCapture_;
    JRoundButton *buttonSwitchView_;
    QTimer *timerTrack_;
};

#endif
