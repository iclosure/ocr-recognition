#include "SplashWidget.h"
#include <QApplication>
#include <QDesktopWidget>

SplashWidget::SplashWidget(QWidget *parent)
    : QSplashScreen(parent)
{
    setFont(QFont("Microsoft Yahei", 16));
    QSize screenSize = QApplication::desktop()->screenGeometry().size();
    setPixmap(QPixmap(":/desktop/image/startup.png")
              .scaled(screenSize.width() / 2, screenSize.height() / 2,
                      Qt::KeepAspectRatio, Qt::SmoothTransformation));

    showMessage(tr("Initializing..."), Qt::AlignCenter, QColor("lightgreen"));
}
