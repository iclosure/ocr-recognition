#ifndef JMAINWINDOW_H
#define JMAINWINDOW_H

#include <QMainWindow>
#include "../global.h"

// class JMainWindow

class JTitleBar;
class JMainWindowPrivate;
class QAbstractNativeEventFilter;

class JWT_EXPORT JMainWindow : public QMainWindow
{
	Q_OBJECT
    Q_PROPERTY(bool resizable READ resizable WRITE setResizable NOTIFY resizableChanged)
public:
    explicit JMainWindow(QWidget *parent = nullptr);
    ~JMainWindow() J_OVERRIDE;

    bool resizable() const;

    JTitleBar *titleBar() const;

    QWidget *titleWidget() const;
    void addTitleWidget(QWidget *widget);

    QAbstractNativeEventFilter *filter() const;
    void setFilter(QAbstractNativeEventFilter *filter);

Q_SIGNALS:
    void resizableChanged(bool enabled);
    void menuTrigglered(const QPoint &pos);

public Q_SLOTS:
    void setResizable(bool enabled);
    void setCenter();

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    Q_DISABLE_COPY(JMainWindow)
    J_DECLARE_PRIVATE(JMainWindow)
};

#endif // JMAINWINDOW_H
