#include "HomeWindow.h"
#include "global.h"
#include "jwt/widget/JSplitter.h"
#include "jwt/widget/JGroupBox.h"
#include "common/OCRMgr.h"
#include "ImageLabel.h"
#include "SourceView.h"
#include <QFormLayout>
#include <QPlainTextEdit>
#include <QDebug>

// class HomeWindow

HomeWindow::HomeWindow(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QLatin1String("home"));

    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->setContentsMargins(0, 0, 0, 0);
    layoutMain->setSpacing(0);

    splitter_ = new JSplitter({1, 1, 1}, this);
    splitter_->setObjectName(QLatin1String("home.splitter"));
    splitter_->setOpaqueResize(true);
    splitter_->setChildrenCollapsible(false);
    layoutMain->addWidget(splitter_);

    sourceView_ = new SourceView(this);
    splitter_->addWidget(sourceView_);

    labelBinary_ = new ImageLabel(this);
    labelBinary_->setObjectName(QLatin1String("_image_"));
    labelBinary_->setMinimumWidth(300);
    labelBinary_->setClickable(false);
    splitter_->addWidget(labelBinary_);

    JGroupBox *groupRight = new JGroupBox(tr("Device informations"), this);
    splitter_->addWidget(groupRight);

    QVBoxLayout *layoutRight = new QVBoxLayout(groupRight);
    layoutRight->setAlignment(Qt::AlignVCenter);

    editDevInfo_ = new QPlainTextEdit(groupRight);
    editDevInfo_->setMinimumWidth(300);
    editDevInfo_->setReadOnly(true);
    layoutRight->addWidget(editDevInfo_);

    connect(sourceView_, &SourceView::captured, this, [=](const QImage &image){
        Q_UNUSED(image)
        setCursor(Qt::BusyCursor);
        cv::Mat binaryImage = sourceView_->binaryImage();
        const std::vector<std::vector<cv::Point> > &contours = sourceView_->contours();
        const QStringList sections = OCRMgr::instance()->test(
                    binaryImage, contours, sourceView_->anchorErode());
        const QString text = sections.join(QLatin1String("\n--------------------------\n"));
        editDevInfo_->setPlainText(text);
        unsetCursor();
    });
    connect(sourceView_, &SourceView::filePathChanged, this, [=](const QString &filePath){
        if (filePath.isEmpty()) {
            sourceView_->setSourceImage(QPixmap());
            labelBinary_->setPixmap(QPixmap());
            editDevInfo_->clear();
        } else {
            setCursor(Qt::BusyCursor);

            QPixmap pmSource, pmBinary;

            const QStringList sections = OCRMgr::instance()->test(
                        filePath, sourceView_->threshold(),
                        sourceView_->anchorOpenClose(), sourceView_->anchorErode(),
                        &pmSource, &pmBinary);

            sourceView_->setSourceImage(pmSource);
            labelBinary_->setPixmap(pmBinary);

            const QString text = sections.join(QLatin1String("\n--------------------------\n"));
            editDevInfo_->setPlainText(text);

            unsetCursor();
        }
    });
    connect(sourceView_, &SourceView::binaryImageUpdated, this, [=](){
        const QPixmap pixmap = OCRMgr::cvMatToQPixmap(sourceView_->binaryImage());
        labelBinary_->setPixmap(pixmap);
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

    result = result && sourceView_->init();

    return result;
}
