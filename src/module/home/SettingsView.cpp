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
    , defaultReogArea_(480, 900)
    , defaultThreshold_(130)
    , defaultAnchorOpenClose_(17, 3)
    , defaultAnchorErode_(30, 12)
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);

    layoutField_ = new QFormLayout();
    layoutField_->setLabelAlignment(Qt::AlignRight);
    layoutMain->addLayout(layoutField_);

    // reognition area width

    layoutReogAreaWidth_ = new QHBoxLayout();
    layoutField_->addRow(tr("Reognition Area Width:"), layoutReogAreaWidth_);

    spinReogAreaWidth_ = new QSpinBox(this);
    spinReogAreaWidth_->setRange(50, 1920 - 1);
    spinReogAreaWidth_->setFixedWidth(120);
    layoutReogAreaWidth_->addWidget(spinReogAreaWidth_);

    sliderReogAreaWidth_ = new QSlider(Qt::Horizontal, this);
    sliderReogAreaWidth_->setRange(50, 1920 - 1);
    layoutReogAreaWidth_->addWidget(sliderReogAreaWidth_);

    // reognition area height

    layoutReogAreaHeight_ = new QHBoxLayout();
    layoutField_->addRow(tr("Reognition Area Height:"), layoutReogAreaHeight_);

    spinReogAreaHeight_ = new QSpinBox(this);
    spinReogAreaHeight_->setRange(50, 1080 - 1);
    spinReogAreaHeight_->setFixedWidth(120);
    layoutReogAreaHeight_->addWidget(spinReogAreaHeight_);

    sliderReogAreaHeight_ = new QSlider(Qt::Horizontal, this);
    sliderReogAreaHeight_->setRange(50, 1080 - 1);
    layoutReogAreaHeight_->addWidget(sliderReogAreaHeight_);

    // threshold

    QHBoxLayout *layoutThreshold = new QHBoxLayout();
    layoutField_->addRow(tr("Threshold:"), layoutThreshold);

    spinThreshold_ = new QSpinBox(this);
    spinThreshold_->setRange(0, 255);
    spinThreshold_->setFixedWidth(120);
    layoutThreshold->addWidget(spinThreshold_);

    QSlider *sliderThreshold = new QSlider(Qt::Horizontal, this);
    sliderThreshold->setRange(0, 255);
    layoutThreshold->addWidget(sliderThreshold);

    // open-close anchor width

    QHBoxLayout *layoutOpenWidth = new QHBoxLayout();
    layoutField_->addRow(tr("Open-Close Width:"), layoutOpenWidth);

    spinAnchorOpenWidth_ = new QSpinBox(this);
    spinAnchorOpenWidth_->setRange(1, 255);
    spinAnchorOpenWidth_->setFixedWidth(120);
    layoutOpenWidth->addWidget(spinAnchorOpenWidth_);

    QSlider *sliderAnchorOpenWidth = new QSlider(Qt::Horizontal, this);
    sliderAnchorOpenWidth->setRange(1, 255);
    layoutOpenWidth->addWidget(sliderAnchorOpenWidth);

    // open-close anchor height

    QHBoxLayout *layoutOpenHeight = new QHBoxLayout();
    layoutField_->addRow(tr("Open-Close Height:"), layoutOpenHeight);

    spinAnchorOpenHeight_ = new QSpinBox(this);
    spinAnchorOpenHeight_->setRange(1, 255);
    spinAnchorOpenHeight_->setFixedWidth(120);
    layoutOpenHeight->addWidget(spinAnchorOpenHeight_);

    QSlider *sliderAnchorOpenHeight = new QSlider(Qt::Horizontal, this);
    sliderAnchorOpenHeight->setRange(1, 255);
    layoutOpenHeight->addWidget(sliderAnchorOpenHeight);

    // erode anchor width

    QHBoxLayout *layoutAnchorErodeWidth = new QHBoxLayout();
    layoutField_->addRow(tr("Erode Width:"), layoutAnchorErodeWidth);

    spinAnchorErodeWidth_ = new QSpinBox(this);
    spinAnchorErodeWidth_->setRange(1, 255);
    spinAnchorErodeWidth_->setFixedWidth(120);
    layoutAnchorErodeWidth->addWidget(spinAnchorErodeWidth_);

    QSlider *sliderAnchorErodeWidth = new QSlider(Qt::Horizontal, this);
    sliderAnchorErodeWidth->setRange(1, 255);
    layoutAnchorErodeWidth->addWidget(sliderAnchorErodeWidth);

    // erode anchor height

    QHBoxLayout *layoutAnchorErodeHeigh = new QHBoxLayout();
    layoutField_->addRow(tr("Erode Height:"), layoutAnchorErodeHeigh);

    spinAnchorErodeHeight_ = new QSpinBox(this);
    spinAnchorErodeHeight_->setRange(1, 255);
    spinAnchorErodeHeight_->setFixedWidth(120);
    layoutAnchorErodeHeigh->addWidget(spinAnchorErodeHeight_);

    QSlider *sliderAnchorErodeHeight = new QSlider(Qt::Horizontal, this);
    sliderAnchorErodeHeight->setRange(1, 255);
    layoutAnchorErodeHeigh->addWidget(sliderAnchorErodeHeight);

    // reognition area width
    connect(spinReogAreaWidth_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [=](int value){
        Q_EMIT ReogAreaChanged(QSize(value, spinReogAreaHeight_->value()));
    });
    connect(spinReogAreaWidth_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            sliderReogAreaWidth_, &QSlider::setValue);
    connect(sliderReogAreaWidth_, &QSlider::valueChanged, spinReogAreaWidth_, &QSpinBox::setValue);
    // reognition area height
    connect(spinReogAreaHeight_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [=](int value){
        Q_EMIT ReogAreaChanged(QSize(spinReogAreaWidth_->value(), value));
    });
    connect(spinReogAreaHeight_, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            sliderReogAreaHeight_, &QSlider::setValue);
    connect(sliderReogAreaHeight_, &QSlider::valueChanged, spinReogAreaHeight_, &QSpinBox::setValue);
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

    //
    setReogArea(defaultReogArea_);
    setThreshold(defaultThreshold_);
    setAnchorOpenClose(defaultAnchorErode_);
    setAnchorErode(defaultAnchorErode_);
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

QSize SettingsView::reogArea() const
{
    return QSize(spinReogAreaWidth_->value(), spinReogAreaHeight_->value());
}

int SettingsView::threshold() const
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

QSize SettingsView::defaultReogArea() const
{
    return defaultReogArea_;
}

int SettingsView::defaultThreshold() const
{
    return defaultThreshold_;
}

QSize SettingsView::defaultAnchorOpenClose() const
{
    return defaultAnchorOpenClose_;
}

QSize SettingsView::defaultAnchorErode() const
{
    return defaultAnchorErode_;
}

void SettingsView::setReogArea(const QSize &size)
{
    spinReogAreaWidth_->setValue(size.width());
    spinReogAreaHeight_->setValue(size.height());
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

void SettingsView::reset()
{
    setReogArea(defaultReogArea());
    setThreshold(defaultThreshold());
    setAnchorOpenClose(defaultAnchorOpenClose());
    setAnchorErode(defaultAnchorErode());
}

void SettingsView::setReogAreaVisible(bool visible)
{
    layoutField_->labelForField(layoutReogAreaWidth_)->setVisible(visible);
    layoutField_->labelForField(layoutReogAreaHeight_)->setVisible(visible);
    spinReogAreaWidth_->setVisible(visible);
    spinReogAreaHeight_->setVisible(visible);
    sliderReogAreaWidth_->setVisible(visible);
    sliderReogAreaHeight_->setVisible(visible);
}
