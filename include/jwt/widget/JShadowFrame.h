#ifndef JSHADOWFRAME_H
#define JSHADOWFRAME_H

#include "../global.h"
#include <QFrame>
#include <QGraphicsDropShadowEffect>

class JShadowFramePrivate;

class JWT_EXPORT JShadowFrame : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(bool shadowEnabled READ isShadowEnabled WRITE setShadowEnabled NOTIFY shadowEnabledChanged)
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius NOTIFY blurRadiusChanged)
public:
    explicit JShadowFrame(QWidget *parent = nullptr);
    virtual ~JShadowFrame() J_OVERRIDE;

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
    Q_DISABLE_COPY(JShadowFrame)
    J_DECLARE_PRIVATE(JShadowFrame)
};

#endif // JSHADOWFRAME_H
