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

// class LabelImage

LabelImage::LabelImage(QWidget *parent)
    : QLabel(parent)
{

}

LabelImage::~LabelImage()
{

}

void LabelImage::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    const QString filePath = QFileDialog::getOpenFileName(
                this, tr("Select an image"), QString(),
                QLatin1String("Image file (*.png *.jpg)"));
    if (filePath.isEmpty()) {
        return;
    }

    filePath_ = filePath;

    Q_EMIT filePathChanged(filePath_);
}

void LabelImage::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::PointingHandCursor);
}

void LabelImage::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    unsetCursor();
}

void LabelImage::paintEvent(QPaintEvent *)
{
    if (filePath_.isEmpty() || !QFile::exists(filePath_)) {
        return;
    }

    QPixmap pixmap(filePath_);
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

    splitter_ = new JSplitter({1.5, 1}, this);
    splitter_->setObjectName("home.splitter");
    layoutMain->addWidget(splitter_);

    labelImage_ = new LabelImage(this);
    labelImage_->setObjectName(QLatin1String("_image_"));
    splitter_->addWidget(labelImage_);

    JGroupBox *groupRight = new JGroupBox(tr("Device informations"), this);
    splitter_->addWidget(groupRight);

    QVBoxLayout *layoutRight = new QVBoxLayout(groupRight);
    layoutRight->setAlignment(Qt::AlignVCenter);

    editDevInfo_ = new QPlainTextEdit(groupRight);
    editDevInfo_->setReadOnly(true);
    layoutRight->addWidget(editDevInfo_);

    connect(labelImage_, &LabelImage::filePathChanged, this, [=](const QString &filePath){
        const QString text = OCRMgr::instance()->test(filePath);
        editDevInfo_->setPlainText(text);
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
