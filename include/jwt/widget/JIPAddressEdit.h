#ifndef JIPADDRESSEDIT_H
#define JIPADDRESSEDIT_H

#include "../global.h"
#include <QFrame>

// - class JIPAddressEdit -

class JIPAddressEditPrivate;
class QGraphicsDropShadowEffect;

class JWT_EXPORT JIPAddressEdit : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(bool shadowEnabled READ isShadowEnabled WRITE setShadowEnabled NOTIFY shadowEnabledChanged)
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius NOTIFY blurRadiusChanged)
    Q_PROPERTY(bool baseLineVisible READ isBaseLineVisible WRITE setBaseLineVisible NOTIFY baseLineVisibleChanged)
    Q_PROPERTY(QColor dotColor READ dotColor WRITE setDotColor NOTIFY dotColorChanged)
public:
    explicit JIPAddressEdit(QWidget *parent = nullptr);
    explicit JIPAddressEdit(const QString &text, QWidget *parent = nullptr);
    virtual ~JIPAddressEdit();

    bool isShadowEnabled() const;
    qreal blurRadius() const;
    QGraphicsDropShadowEffect *effect() const;

    bool isBaseLineVisible() const;
    QColor dotColor() const;
    QString text() const;

    bool isReadOnly() const;
    void setReadOnly(bool value);

Q_SIGNALS:
    void shadowEnabledChanged(bool enabled);
    void blurRadiusChanged(qreal blurRadius);
    void baseLineVisibleChanged(bool visible);
    void dotColorChanged(const QColor &color);
    void textChanged(const QString &text);

public Q_SLOTS:
    void setShadowEnabled(bool enabled);
    void setBlurRadius(qreal radius);
    void setBaseLineVisible(bool visible);
    void setDotColor(const QColor &color);
    void setText(const QString &text);

private:
    Q_DISABLE_COPY(JIPAddressEdit)
    J_DECLARE_PRIVATE(JIPAddressEdit)
};

#endif // JIPADDRESSEDIT_H
