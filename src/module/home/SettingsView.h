#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include "global.h"
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "jwt/widget/JGroupBox.h"

// class SettingsView

class QSpinBox;
class QSlider;
class QFormLayout;
class QHBoxLayout;

class SettingsView : public JGroupBox
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget *parent = nullptr);
    ~SettingsView() J_OVERRIDE;

    bool init();

    QSize reogArea() const;
    int threshold() const;
    QSize anchorOpenClose() const;
    QSize anchorErode() const;

    QSize defaultReogArea() const;
    int defaultThreshold() const;
    QSize defaultAnchorOpenClose() const;
    QSize defaultAnchorErode() const;

Q_SIGNALS:
    void ReogAreaChanged(const QSize &size);
    void thresholdChanged(int value);
    void anchorOpenCloseChanged(const QSize &size);
    void anchorErodeChanged(const QSize &size);

public Q_SLOTS:
    void setReogArea(const QSize &size);
    void setThreshold(int value);
    void setAnchorOpenClose(const QSize &size);
    void setAnchorErode(const QSize &size);

    void reset();

    void setReogAreaVisible(bool visible);

private:
    Q_DISABLE_COPY(SettingsView)
    QSize defaultReogArea_;
    int defaultThreshold_;
    QSize defaultAnchorOpenClose_;
    QSize defaultAnchorErode_;
    QFormLayout *layoutField_;
    QHBoxLayout *layoutReogAreaWidth_;
    QHBoxLayout *layoutReogAreaHeight_;
    QSpinBox *spinReogAreaWidth_;
    QSpinBox *spinReogAreaHeight_;
    QSlider *sliderReogAreaWidth_;
    QSlider *sliderReogAreaHeight_;
    QSpinBox *spinThreshold_;
    QSpinBox *spinAnchorOpenWidth_;
    QSpinBox *spinAnchorOpenHeight_;
    QSpinBox *spinAnchorErodeWidth_;
    QSpinBox *spinAnchorErodeHeight_;
};

#endif
