#ifndef JFORMFRAME_H
#define JFORMFRAME_H

#include "JShadowFrame.h"
#include <QVBoxLayout>

class JFormFramePrivate;
class QLabel;

class JWT_EXPORT JFormFrame : public JShadowFrame
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
public:
    explicit JFormFrame(QWidget *field, QWidget *parent = nullptr);
    JFormFrame(const QString &title, QWidget *field, QWidget *parent = nullptr);
    virtual ~JFormFrame() J_OVERRIDE;

    QString title() const;

    QLabel *label() const;
    virtual QWidget *field() const;

Q_SIGNALS:
    void titleChanged(const QString &text);

public Q_SLOTS:
    void setTitle(const QString &text);

private:
    Q_DISABLE_COPY(JFormFrame)
    J_DECLARE_PRIVATE(JFormFrame)
};

#endif // JFORMFRAME_H
