#ifndef JCOMBOBOX_H
#define JCOMBOBOX_H

#include "../global.h"
#include <QComboBox>

class JComboBoxPrivate;
class QGraphicsDropShadowEffect;

class JWT_EXPORT JComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(bool shadowEnabled READ isShadowEnabled WRITE setShadowEnabled NOTIFY shadowEnabledChanged)
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius NOTIFY blurRadiusChanged)
public:
    explicit JComboBox(QWidget *parent = nullptr);
    ~JComboBox() J_OVERRIDE;

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
    Q_DISABLE_COPY(JComboBox)
    J_DECLARE_PRIVATE(JComboBox)
};

#endif // JCOMBOBOX_H
