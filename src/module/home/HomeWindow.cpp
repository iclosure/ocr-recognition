#include "HomeWindow.h"
#include "global.h"
#include "jwt/widget/JSplitter.h"
#include "jwt/widget/JGroupBox.h"
#include "jwt/widget/JRoundButton.h"
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

    JGroupBox *groupRight = new JGroupBox(tr("Reognition informations"), this);
    splitter_->addWidget(groupRight);

    QVBoxLayout *layoutRight = new QVBoxLayout(groupRight);
    layoutRight->setAlignment(Qt::AlignVCenter);

    editDevInfo_ = new QPlainTextEdit(groupRight);
    editDevInfo_->setMinimumWidth(300);
    editDevInfo_->setReadOnly(true);
    layoutRight->addWidget(editDevInfo_);

    buttonGenReport_ = new JRoundButton(tr("Generate report"), groupRight);
    buttonGenReport_->setMinimumWidth(80);
    layoutRight->addWidget(buttonGenReport_, 0, Qt::AlignHCenter);

    connect(sourceView_, &SourceView::captured, this, [=](const QImage &image){
        Q_UNUSED(image)
        recognite();
    });
    connect(sourceView_, &SourceView::filePathChanged, this, [=](){
        updateImage();
    });
    connect(sourceView_, &SourceView::recognitionClicked, this, [=](){
        recognite();
    });
    connect(sourceView_, &SourceView::binaryImageUpdated, this, [=](){
        const QPixmap pixmap = OCRMgr::cvMatToQPixmap(sourceView_->binaryImage());
        labelBinary_->setPixmap(pixmap);
    });
    connect(sourceView_, &SourceView::thresholdChanged, this, [=](){
        if (sourceView_->currentIndex() != 1) {
            return;
        }
        updateImage();
    });
    connect(sourceView_, &SourceView::anchorOpenCloseChanged, this, [=](){
        if (sourceView_->currentIndex() != 1) {
            return;
        }
        updateImage();
    });
    connect(sourceView_, &SourceView::anchorErodeChanged, this, [=](){
        if (sourceView_->currentIndex() != 1) {
            return;
        }
        updateImage();
    });
    connect(buttonGenReport_, &JRoundButton::clicked, this, [=](){
        //
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

void HomeWindow::updateImage()
{
    editDevInfo_->clear();

    cv::Mat imSource;

    if (!sourceView_->updateImage(imSource)) {
        sourceView_->setSourceImage(QPixmap());
        labelBinary_->setPixmap(QPixmap());
        return;
    }
    //
    QPixmap pmBinary;
    pmBinary = OCRMgr::cvMatToQPixmap(sourceView_->binaryImage());
    labelBinary_->setPixmap(pmBinary);
}

void HomeWindow::recognite()
{
    setCursor(Qt::BusyCursor);
    cv::Mat binaryImage = sourceView_->binaryImage();
    const std::vector<std::vector<cv::Point> > &contours = sourceView_->contours();
    const QStringList sections = OCRMgr::instance()->test(
                binaryImage, contours, sourceView_->anchorErode());
    const QString text = sections.join(QLatin1String("\n--------------------------\n"));
    editDevInfo_->setPlainText(text);
    unsetCursor();
}
