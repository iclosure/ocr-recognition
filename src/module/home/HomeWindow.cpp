#include "HomeWindow.h"
#include "global.h"
#include "jwt/widget/JSplitter.h"
#include "jwt/widget/JGroupBox.h"
#include "common/OCRMgr.h"
#include <QFormLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMouseEvent>
#include <QFileDialog>
#include <QPainter>
#include <QDebug>

// class LabelImage

LabelImage::LabelImage(QWidget *parent)
    : QLabel(parent)
    , clickable_(true)
{
    setMinimumWidth(10);
}

LabelImage::~LabelImage()
{

}

bool LabelImage::isClickable() const
{
    return clickable_;
}

void LabelImage::setClickable(bool enabled)
{
    clickable_ = enabled;
}

void LabelImage::mousePressEvent(QMouseEvent *event)
{
    if (!clickable_) {
        QLabel::mousePressEvent(event);
        return;
    }

    const QString filePath = QFileDialog::getOpenFileName(
                this, tr("Select an image"), QString(),
                QLatin1String("Image file (*.png *.jpg)"));
    if (filePath.isEmpty()) {
        return;
    }

    setPixmap(QPixmap(filePath));

    filePath_ = filePath;

    Q_EMIT filePathChanged(filePath_);
}

void LabelImage::enterEvent(QEvent *event)
{
    if (!clickable_) {
        QLabel::enterEvent(event);
        return;
    }

    setCursor(Qt::PointingHandCursor);
}

void LabelImage::leaveEvent(QEvent *event)
{
    if (!clickable_) {
        QLabel::leaveEvent(event);
        return;
    }

    unsetCursor();
}

void LabelImage::paintEvent(QPaintEvent *)
{
    const QPixmap *_pixmap = this->pixmap();
    if (!_pixmap) {
        return;
    }

    QPixmap pixmap = _pixmap->copy();
    QSize size = this->size();
    size = size.boundedTo(pixmap.size());
    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    const QRect rect = this->rect();
    painter.drawPixmap(rect.center() - QPointF(pixmap.width(), pixmap.height()) / 2, pixmap);
}

// class HomeWindow

HomeWindow::HomeWindow(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("home");

    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->setContentsMargins(0, 0, 0, 0);
    layoutMain->setSpacing(0);

    splitter_ = new JSplitter({2, 1}, this);
    splitter_->setObjectName("home.splitter");
    splitter_->setOpaqueResize(true);
    splitter_->setChildrenCollapsible(false);
    layoutMain->addWidget(splitter_);

    QWidget *widgetLeft = new QWidget(this);
    splitter_->addWidget(widgetLeft);

    QHBoxLayout *layoutLeft = new QHBoxLayout(widgetLeft);
    layoutLeft->setContentsMargins(3, 3, 3, 3);
    layoutLeft->setSpacing(3);

    labelImSource_ = new LabelImage(this);
    labelImSource_->setObjectName(QLatin1String("_image_"));
    layoutLeft->addWidget(labelImSource_);

    labelImBinary_ = new LabelImage(this);
    labelImBinary_->setObjectName(QLatin1String("_image_"));
    labelImBinary_->setClickable(false);
    layoutLeft->addWidget(labelImBinary_);

    JGroupBox *groupRight = new JGroupBox(tr("Device informations"), this);
    groupRight->setMinimumWidth(150);
    splitter_->addWidget(groupRight);

    QVBoxLayout *layoutRight = new QVBoxLayout(groupRight);
    layoutRight->setAlignment(Qt::AlignVCenter);

    editDevInfo_ = new QPlainTextEdit(groupRight);
    editDevInfo_->setReadOnly(true);
    layoutRight->addWidget(editDevInfo_);

    connect(labelImSource_, &LabelImage::filePathChanged, this, [=](const QString &filePath){
        setCursor(Qt::BusyCursor);

        QPixmap pmSource, pmBinary;

        const QStringList sections = OCRMgr::instance()->test(filePath, QSize(30, 12), &pmSource, &pmBinary);

        labelImSource_->setPixmap(pmSource);
        labelImBinary_->setPixmap(pmBinary);

        const QString text = sections.join(QLatin1String("\n--------------------------\n"));
        editDevInfo_->setPlainText(text);

        unsetCursor();
    });
}

HomeWindow::~HomeWindow()
{
    Jwt::saveWidgetState(splitter_);
}

bool HomeWindow::init()
{
    bool result = true;

    Jwt::restoreWidgetState(splitter_);

    return result;
}
