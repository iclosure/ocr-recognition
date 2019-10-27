#include "jwt/style/JTitleBar.h"
#include "global.h"
#include "MainWindow.h"
#include "CentralWidget.h"
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : JMainWindow(parent, QSize(1100, 550))
{
    JTitleBar *titleBar = this->titleBar();
    titleBar->setButtonVisible(JTitleBar::ButtonMenu, false);
    titleBar->setButtonVisible(JTitleBar::ButtonMin, true);
    //titleBar->setButtonVisible(JTitleBar::ButtonMax, false);

    setDockOptions(QMainWindow::AnimatedDocks
                   | QMainWindow::AllowNestedDocks
                   | QMainWindow::AllowTabbedDocks);

    centralWidget_ = new CentralWidget(this);
    setCentralWidget(centralWidget_);
#if 0
    // serialport configuration
    JSystemButton *buttonSerial = titleBar->addRightButton(
                QLatin1String("title.button.serialport"),
                QIcon(":/desktop/image/global/serialport.png"), [=](bool...){
    }, QSize(20, 20));
    buttonSerial->setToolTip(tr("SerialPort configuration"));
#endif
}

MainWindow::~MainWindow()
{
    centralWidget_->clearView();
}

bool MainWindow::init()
{
    bool result = true;

    result = result && centralWidget_->init();

    return result;
}

void MainWindow::dispose()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        break;
    default:
        break;
    }

    JMainWindow::keyPressEvent(event);
}
