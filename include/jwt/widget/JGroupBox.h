#ifndef JGROUPBOX_H
#define JGROUPBOX_H

#include "../global.h"
#include <QGroupBox>

class JGroupBoxPrivate;
class QGraphicsDropShadowEffect;

class JWT_EXPORT JGroupBox : public QGroupBox
{
    Q_OBJECT
    Q_PROPERTY(bool shadowEnabled READ isShadowEnabled WRITE setShadowEnabled NOTIFY shadowEnabledChanged)
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius NOTIFY blurRadiusChanged)
public:
    explicit JGroupBox(QWidget *parent = nullptr);
    explicit JGroupBox(const QString &title, QWidget *parent = nullptr);
    ~JGroupBox() J_OVERRIDE;

    bool isShadowEnabled() const;
    qreal blurRadius() const;
    QGraphicsDropShadowEffect *effect() const;

Q_SIGNALS:
    void shadowEnabledChanged(bool enabled);
    void blurRadiusChanged(qreal blurRadius);

public Q_SLOTS:
    void setShadowEnabled(bool enabled);
    void setBlurRadius(qreal radius);

protected:
    virtual void changeEvent(QEvent *event) override;

private:
    Q_DISABLE_COPY(JGroupBox)
    J_DECLARE_PRIVATE(JGroupBox)
};

#endif // JGROUPBOX_H
