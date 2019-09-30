#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include "jwt/style/JMainWindow.h"

class CentralWidget;

class MainWindow : public JMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() J_OVERRIDE;

    bool init();
    void dispose();

    bool gotoPage(const QString &id, int delayMs = 0, bool sync = true,
                  const QString &msg = QString());
    bool gotoDisconnectPage(int delayMs = 0, bool sync = true,
                            const QString &msg = QString());
    bool gotoConnectPage(int delayMs = 0, bool sync = true,
                         const QString &msg = QString());

signals:

public slots:

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    CentralWidget *centralWidget_;
};

#endif // MAINWINDOW_H
