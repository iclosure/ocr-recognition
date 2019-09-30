#ifndef JDOCKWIDGET_H
#define JDOCKWIDGET_H

#include "../global.h"
#include <QDockWidget>

class JWT_EXPORT JDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit JDockWidget(QWidget *parent = nullptr);

Q_SIGNALS:

public Q_SLOTS:

private:
};

#endif // JDOCKWIDGET_H
