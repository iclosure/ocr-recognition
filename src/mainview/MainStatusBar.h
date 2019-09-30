#ifndef MAIN_STATUSBAR_H
#define MAIN_STATUSBAR_H

#include <QStatusBar>
#include <QLabel>

namespace Main {

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);

signals:

public slots:

private:
};

}

#endif // MAIN_STATUSBAR_H
