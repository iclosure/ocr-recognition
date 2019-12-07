#include "ImageLabel.h"
#include <QMouseEvent>
#include <QFileDialog>
#include <QPainter>
#include <QSettings>

// class ImageLabel

ImageLabel::ImageLabel(QWidget *parent)
    : QLabel(parent)
    , clickable_(true)
{
    setMinimumWidth(10);
}

ImageLabel::~ImageLabel()
{

}

bool ImageLabel::isClickable() const
{
    return clickable_;
}

QString ImageLabel::filePath() const
{
    return filePath_;
}

void ImageLabel::setClickable(bool enabled)
{
    clickable_ = enabled;
}

void ImageLabel::mousePressEvent(QMouseEvent *event)
{
    if (!clickable_) {
        QLabel::mousePressEvent(event);
        return;
    }

    const QString sourceDirKey(QLatin1String("home/source/sourceDir"));
    const QString sourceDir = Jwt::readStore<QString>(sourceDirKey);

    const QString filePath = QFileDialog::getOpenFileName(
                this, tr("Select an image"), sourceDir,
                QLatin1String("Image file (*.png *.jpg)"));
    if (filePath.isEmpty()) {
        return;
    }

    Jwt::writeStore(sourceDirKey, QFileInfo(filePath).absolutePath());

    setPixmap(QPixmap(filePath));

    filePath_ = filePath;

    Q_EMIT filePathChanged(filePath_);
}

void ImageLabel::enterEvent(QEvent *event)
{
    if (!clickable_) {
        QLabel::enterEvent(event);
        return;
    }

    setCursor(Qt::PointingHandCursor);
}

void ImageLabel::leaveEvent(QEvent *event)
{
    if (!clickable_) {
        QLabel::leaveEvent(event);
        return;
    }

    unsetCursor();
}

void ImageLabel::paintEvent(QPaintEvent *)
{
    const QRect rect = this->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QPixmap *_pixmap = this->pixmap();
    if (_pixmap) {
        if (!_pixmap->isNull()) {
            QPixmap pixmap = _pixmap->copy();
            QSize size = this->size();
            size = size.boundedTo(pixmap.size());
            pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
            painter.drawPixmap(rect.center() - QPointF(pixmap.width(), pixmap.height()) / 2, pixmap);
        }
    } else if (clickable_) {
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        QTextOption textOption(Qt::AlignCenter);
        painter.setPen(QColor(64, 64, 64));
        QFont font = painter.font();
        font.setPointSize(16);
        painter.setFont(font);
        painter.drawText(rect, tr("Click here to select a image to show."), textOption);
    }
}
