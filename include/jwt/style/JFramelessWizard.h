#ifndef JFRAMELESSWIZARD_H
#define JFRAMELESSWIZARD_H

#include "../global.h"
#include <QWizard>

// class JFramelessWizard

class JTitleBar;
class JFramelessWizardPrivate;
class QAbstractNativeEventFilter;
class QVBoxLayout;

class JWT_EXPORT JFramelessWizard : public QWizard
{
    Q_OBJECT
    Q_PROPERTY(bool resizable READ resizable WRITE setResizable NOTIFY resizableChanged)
    Q_PROPERTY(bool escEnabled READ isEscEnabled WRITE setEscEnabled NOTIFY escEnabledChanged)
    Q_PROPERTY(bool rejectEnabled READ isRejectEnabled WRITE setRejectEnabled NOTIFY rejectEnabledChanged)
public:
    explicit JFramelessWizard(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~JFramelessWizard() J_OVERRIDE;

    bool resizable() const;
    bool isEscEnabled() const;
    bool isRejectEnabled() const;

    JTitleBar *titleBar() const;

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
    Q_DISABLE_COPY(JFramelessWizard)
    J_DECLARE_PRIVATE(JFramelessWizard)
};

#endif // JFRAMELESSWIZARD_H
