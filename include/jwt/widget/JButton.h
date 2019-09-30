#ifndef JBUTTON_H
#define JBUTTON_H

#include "../global.h"
#include <QPushButton>

class JButtonPrivate;
class QGraphicsDropShadowEffect;

class JWT_EXPORT JButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool shadowEnabled READ isShadowEnabled WRITE setShadowEnabled NOTIFY shadowEnabledChanged)
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius NOTIFY blurRadiusChanged)
public:
    explicit JButton(QWidget *parent = nullptr);
    explicit JButton(const QString &text, QWidget *parent = nullptr);
    JButton(const QString &icon, const QString &text, QWidget *parent = nullptr);
    JButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    ~JButton() J_OVERRIDE;

    bool isShadowEnabled() const;
    qreal blurRadius() const;
    QGraphicsDropShadowEffect *effect() const;

    virtual QSize sizeHint() const override;

Q_SIGNALS:
    void shadowEnabledChanged(bool enabled);
    void blurRadiusChanged(qreal blurRadius);

public Q_SLOTS:
    void setShadowEnabled(bool enabled);
    void setBlurRadius(qreal radius);

protected:
    virtual void changeEvent(QEvent *event) override;

private:
    Q_DISABLE_COPY(JButton)
    J_DECLARE_PRIVATE(JButton)
};

#endif // JBUTTON_H
