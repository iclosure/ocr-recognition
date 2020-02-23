#include "SplashWidget.h"
#include <QApplication>
#include <QScreen>

SplashWidget::SplashWidget(QWidget *parent)
    : QSplashScreen(parent)
{
    setFont(QFont(QLatin1String("Microsoft Yahei"), 24));
    const QScreen *screen = QApplication::screenAt(QCursor::pos());
    if (screen) {
        const QRect screenGeometry = screen->geometry();
        QSize screenSize = screenGeometry.size();
        setPixmap(QPixmap(QLatin1String(":/desktop/image/startup.jpg"))
                  .scaled(screenSize.width() / 2, screenSize.height() / 2,
                          Qt::KeepAspectRatio, Qt::SmoothTransformation));

        showMessage(tr("Initializing..."), Qt::AlignHCenter | Qt::AlignBottom,
                    QColor(QLatin1String("lightgreen")));

        move(screenGeometry.center() - rect().center());
    }
}
