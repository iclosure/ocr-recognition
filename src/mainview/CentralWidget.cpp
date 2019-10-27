#include "CentralWidget.h"
#include "jwt/style/JTitleBar.h"
#include "module/home/HomeWindow.h"
#include "mainview/MainWindow.h"
#include <QLayout>
#include <QStackedWidget>
#include <QCoreApplication>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->setContentsMargins(0, 0, 0, 0);

    stackedWidget_ = new QStackedWidget(this);
    layoutMain->addWidget(stackedWidget_);

    homeWindow_ = new HomeWindow(this);
    stackedWidget_->addWidget(homeWindow_);
}

CentralWidget::~CentralWidget()
{

}

bool CentralWidget::init()
{
    bool result = true;

    //
    result = result && homeWindow_->init();

    return result;
}

void CentralWidget::clearView()
{
    for (int i = stackedWidget_->count() - 1; i >= 0; --i) {
        QWidget *widget = stackedWidget_->widget(i);
        stackedWidget_->removeWidget(widget);
        delete widget;
    }
}
