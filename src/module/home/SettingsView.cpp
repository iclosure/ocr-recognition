#include "SettingsView.h"
#include "ImageLabel.h"
#include "jwt/widget/JRoundButton.h"
#include "common/OCRMgr.h"
#include "VideoWidget.h"
#include <QCamera>
#include <QCameraImageCapture>
#include <QFormLayout>
#include <QTimer>
#include <QCoreApplication>
#include <QStackedWidget>
#include <QSpinBox>
#include <QSlider>
#include <QDebug>

SettingsView::SettingsView(QWidget *parent)
    : JGroupBox(tr("Parameter Settings"), parent)
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);

    QFormLayout *layoutField = new QFormLayout();
    layoutField->setLabelAlignment(Qt::AlignRight);
    layoutMain->addLayout(layoutField);

    // threshold

    QHBoxLayout *layoutThreshold = new QHBoxLayout();
    layoutField->addRow(tr("Threshold:"), layoutThreshold);

    spinThreshold_ = new QSpinBox(this);
    spinThreshold_->setRange(0, 255);
    spinThreshold_->setFixedWidth(120);
    layoutThreshold->addWidget(spinThreshold_);

    QSlider *sliderThreshold = new QSlider(Qt::Horizontal, this);
    sliderThreshold->setRange(0, 255);
    layoutThreshold->addWidget(sliderThreshold);

    // open-close anchor width

    QHBoxLayout *layoutOpenWidth = new QHBoxLayout();
    layoutField->addRow(tr("Open-Close Width:"), layoutOpenWidth);

    spinAnchorOpenWidth_ = new QSpinBox(this);
    spinAnchorOpenWidth_->setRange(1, 100);
    spinAnchorOpenWidth_->setFixedWidth(120);
    layoutOpenWidth->addWidget(spinAnchorOpenWidth_);

    QSlider *sliderAnchorOpenWidth = new QSlider(Qt::Horizontal, this);
    sliderAnchorOpenWidth->setRange(1, 100);
    layoutOpenWidth->addWidget(sliderAnchorOpenWidth);

    // open-close anchor height

    QHBoxLayout *layoutOpenHeight = new QHBoxLayout();
    layoutField->addRow(tr("Open-Close Height:"), layoutOpenHeight);

    spinAnchorOpenHeight_ = new QSpinBox(this);
    spinAnchorOpenHeight_->setRange(1, 100);
    spinAnchorOpenHeight_->setFixedWidth(120);
    layoutOpenHeight->addWidget(spinAnchorOpenHeight_);

    QSlider *sliderAnchorOpenHeight = new QSlider(Qt::Horizontal, this);
    sliderAnchorOpenHeight->setRange(1, 100);
    layoutOpenHeight->addWidget(sliderAnchorOpenHeight);

    // erode anchor width

    QHBoxLayout *layoutAnchorErodeWidth = new QHBoxLayout();
    layoutField->addRow(tr("Erode Width:"), layoutAnchorErodeWidth);

    spinAnchorErodeWidth_ = new QSpinBox(this);
    spinAnchorErodeWidth_->setRange(1, 100);
    spinAnchorErodeWidth_->setFixedWidth(120);
    layoutAnchorErodeWidth->addWidget(spinAnchorErodeWidth_);

    QSlider *sliderAnchorErodeWidth = new QSlider(Qt::Horizontal, this);
    sliderAnchorErodeWidth->setRange(1, 100);
    layoutAnchorErodeWidth->addWidget(sliderAnchorErodeWidth);

    // erode anchor height

    QHBoxLayout *layoutAnchorErodeHeigh = new QHBoxLayout();
    layoutField->addRow(tr("Erode Height:"), layoutAnchorErodeHeigh);

    spinAnchorErodeHeight_ = new QSpinBox(this);
    spinAnchorErodeHeight_->setRange(1, 100);
    spinAnchorErodeHeight_->setFixedWidth(120);
    layoutAnchorErodeHeigh->addWidget(spinAnchorErodeHeight_);

    QSlider *sliderAnchorErodeHeight = new QSlider(Qt::Horizontal, this);
    sliderAnchorErodeHeight->setRange(1, 100);
    layoutAnchorErodeHeigh->addWidget(sliderAnchorErodeHeight);

    // threshold
    connect(spinThreshold_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &SettingsView::thresholdChanged);
    connect(spinThreshold_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            sliderThreshold, &QSlider::setValue);
    connect(sliderThreshold, &QSlider::valueChanged, spinThreshold_, &QSpinBox::setValue);
    // anchor open-close width
    connect(spinAnchorOpenWidth_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [=](int value){
        Q_EMIT anchorOpenCloseChanged(QSize(value, spinAnchorOpenHeight_->value()));
    });
    connect(spinAnchorOpenWidth_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            sliderAnchorOpenWidth, &QSlider::setValue);
    connect(sliderAnchorOpenWidth, &QSlider::valueChanged, spinAnchorOpenWidth_, &QSpinBox::setValue);
    // anchor open-close height
    connect(spinAnchorOpenHeight_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [=](int value){
        Q_EMIT anchorOpenCloseChanged(QSize(spinAnchorOpenWidth_->value(), value));
    });
    connect(spinAnchorOpenHeight_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            sliderAnchorOpenHeight, &QSlider::setValue);
    connect(sliderAnchorOpenHeight, &QSlider::valueChanged, spinAnchorOpenHeight_, &QSpinBox::setValue);
    // anchor erode width
    connect(spinAnchorErodeWidth_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [=](int value){
        Q_EMIT anchorErodeChanged(QSize(value, spinAnchorErodeHeight_->value()));
    });
    connect(spinAnchorErodeWidth_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            sliderAnchorErodeWidth, &QSlider::setValue);
    connect(sliderAnchorErodeWidth, &QSlider::valueChanged, spinAnchorErodeWidth_, &QSpinBox::setValue);
    // anchor erode height
    connect(spinAnchorErodeHeight_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [=](int value){
        Q_EMIT anchorErodeChanged(QSize(spinAnchorErodeWidth_->value(), value));
    });
    connect(spinAnchorErodeHeight_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            sliderAnchorErodeHeight, &QSlider::setValue);
    connect(sliderAnchorErodeHeight, &QSlider::valueChanged, spinAnchorErodeHeight_, &QSpinBox::setValue);
}

SettingsView::~SettingsView()
{

}

bool SettingsView::init()
{
    bool result = true;

    //

    return result;
}

qreal SettingsView::threshold() const
{
    return spinThreshold_->value();
}

QSize SettingsView::anchorOpenClose() const
{
    return QSize(spinAnchorOpenWidth_->value(), spinAnchorOpenHeight_->value());
}

QSize SettingsView::anchorErode() const
{
    return QSize(spinAnchorErodeWidth_->value(), spinAnchorErodeHeight_->value());
}

void SettingsView::setThreshold(int value)
{
    spinThreshold_->setValue(value);
}

void SettingsView::setAnchorOpenClose(const QSize &size)
{
    spinAnchorOpenWidth_->setValue(size.width());
    spinAnchorOpenHeight_->setValue(size.height());
}

void SettingsView::setAnchorErode(const QSize &size)
{
    spinAnchorErodeWidth_->setValue(size.width());
    spinAnchorErodeHeight_->setValue(size.height());
}
