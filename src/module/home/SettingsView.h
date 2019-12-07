#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include "global.h"
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "jwt/widget/JGroupBox.h"

// class SettingsView

class QSpinBox;

class SettingsView : public JGroupBox
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget *parent = nullptr);
    ~SettingsView() J_OVERRIDE;

    bool init();

    qreal threshold() const;
    QSize anchorOpenClose() const;
    QSize anchorErode() const;

Q_SIGNALS:
    void thresholdChanged(int value);
    void anchorOpenCloseChanged(const QSize &size);
    void anchorErodeChanged(const QSize &size);

public Q_SLOTS:
    void setThreshold(int value);
    void setAnchorOpenClose(const QSize &size);
    void setAnchorErode(const QSize &size);

private:
    Q_DISABLE_COPY(SettingsView)
    QSpinBox *spinThreshold_;
    QSpinBox *spinAnchorOpenWidth_;
    QSpinBox *spinAnchorOpenHeight_;
    QSpinBox *spinAnchorErodeWidth_;
    QSpinBox *spinAnchorErodeHeight_;
};

#endif
