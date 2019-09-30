#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "global.h"

class QStackedWidget;
class HomeWindow;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget() J_OVERRIDE;

    bool init();

signals:

public slots:
    void clearView();

private:
    void setCurrentPage(const QString &id, const QString &msg = QString());
    void tryRestoreFactory();
    void setMessage(const QString &message, bool gotoDisconnect = false);

private:
    QStackedWidget *stackedWidget_;
    HomeWindow *homeWindow_;
};

#endif // CENTRALWIDGET_H
