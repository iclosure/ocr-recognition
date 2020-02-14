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
class SettingsView;
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

    int currentIndex() const;
    void setCurrentIndex(int index);

    int threshold() const;
    QSize anchorOpenClose() const;
    QSize anchorErode() const;

    QString filePath() const;

Q_SIGNALS:
    void captured(const QImage &image);
    void filePathChanged(const QString &filePath);
    void binaryImageUpdated();

    void reogAreaChanged(const QSize &size);
    void thresholdChanged(int value);
    void anchorOpenCloseChanged(const QSize &size);
    void anchorErodeChanged(const QSize &size);

    void recognitionClicked();

public Q_SLOTS:
    void startCapture();
    void stopCapture();
    void setSourceImage(const QPixmap &pixmap);

    void setThreshold(int value);
    void setAnchorOpenClose(const QSize &size);
    void setAnchorErode(const QSize &size);

    bool updateImage(cv::Mat &imSource);

private:
    bool updateBoundRect();
    void updateStackCurrentIndex();

private:
    Q_DISABLE_COPY(SourceView)
    QVBoxLayout *layoutMain_;
    SettingsView  *settingsView_;
    QStackedWidget *stackedWidget_;
    VideoWidget *videoWidget_;
    ImageLabel *imageLabel_;
    JRoundButton *buttonResetSettings_;
    JRoundButton *buttonRecognition_;
    JRoundButton *buttonSwitchView_;
    QTimer *timerTrack_;
    //
    cv::Mat binaryImage_;
    std::vector<std::vector<cv::Point> > contours_;
};

#endif
