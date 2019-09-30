#ifndef JSHADOWDIALOG_H
#define JSHADOWDIALOG_H

#include "../global.h"
#include <QDialog>

// class JShadowDialog

class JTitleBar;
class JShadowDialogPrivate;
class QAbstractNativeEventFilter;
class QVBoxLayout;

class JWT_EXPORT JShadowDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(bool resizable READ resizable WRITE setResizable NOTIFY resizableChanged)
    Q_PROPERTY(bool escEnabled READ isEscEnabled WRITE setEscEnabled NOTIFY escEnabledChanged)
    Q_PROPERTY(bool rejectEnabled READ isRejectEnabled WRITE setRejectEnabled NOTIFY rejectEnabledChanged)
public:
    explicit JShadowDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~JShadowDialog() J_OVERRIDE;

    bool resizable() const;
    bool isEscEnabled() const;
    bool isRejectEnabled() const;

    QVBoxLayout *mainLayout() const;

    JTitleBar *titleBar() const;

    QWidget *centralWidget() const;
    void setCentralWidget(QWidget *widget);

    QAbstractNativeEventFilter *filter() const;

Q_SIGNALS:
    void resizableChanged(bool enabled);
    void escEnabledChanged(bool enabled);
    void rejectEnabledChanged(bool enabled);

public Q_SLOTS:
    void setResizable(bool enabled);
    void setEscEnabled(bool enabled);
    void setRejectEnabled(bool enabled);

    virtual int exec() override;

protected:
    virtual void reject() override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    Q_DISABLE_COPY(JShadowDialog)
    J_DECLARE_PRIVATE(JShadowDialog)
};

#endif // JSHADOWDIALOG_H
