#ifndef JDELAYBUTTON_H
#define JDELAYBUTTON_H

#include "../global.h"
#include <QPushButton>

class JDelayButtonPrivate;
class QGraphicsDropShadowEffect;

class JWT_EXPORT JDelayButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool shadowEnabled READ isShadowEnabled WRITE setShadowEnabled NOTIFY shadowEnabledChanged)
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius NOTIFY blurRadiusChanged)
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QColor flickerColor READ flickerColor WRITE setFlickerColor NOTIFY flickerColorChanged)
    Q_PROPERTY(bool checkLineVisible READ isCheckLineVisible WRITE setCheckLineVisible NOTIFY checkLineVisibleChanged)
public:
    explicit JDelayButton(QWidget *parent = nullptr);
    explicit JDelayButton(const QString &text, QWidget *parent = nullptr);
    JDelayButton(const QString &icon, const QString &text, QWidget *parent = nullptr);
    ~JDelayButton() J_OVERRIDE;

    bool isShadowEnabled() const;
    qreal blurRadius() const;
    QGraphicsDropShadowEffect *effect() const;

    qreal minimum() const;
    qreal maximum() const;
    qreal value() const;

    QColor flickerColor() const;

    bool isCheckLineVisible() const;

Q_SIGNALS:
    void shadowEnabledChanged(bool enabled);
    void blurRadiusChanged(qreal blurRadius);
    void minimumChanged(qreal value);
    void maximumChanged(qreal value);
    void rangeChanged(qreal minimum, qreal maximum);
    void valueChanged(qreal value);
    void flickerColorChanged(const QColor &color);
    void checkLineVisibleChanged(bool visible);
    void timeout();

public Q_SLOTS:
    void setShadowEnabled(bool enabled);
    void setBlurRadius(qreal radius);
    void setMinimum(qreal value);
    void setMaximum(qreal value);
    void setRange(qreal minimum, qreal maximum);
    void setValue(qreal value, bool animation = false);
    void setFlickerColor(const QColor &color, bool animation = false);
    void setCheckLineVisible(bool visible);

    void start(int timeout = -1);
    void stop();
    void reset();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void timerEvent(QTimerEvent *event) override;
    virtual void changeEvent(QEvent *event) override;

private:
    Q_DISABLE_COPY(JDelayButton)
    J_DECLARE_PRIVATE(JDelayButton)
};

#endif // JDELAYBUTTON_H
