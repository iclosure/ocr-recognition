#ifndef JCOLORBUTTON_H
#define JCOLORBUTTON_H

#include "../global.h"
#include "JShadowFrame.h"

class JColorButtonPrivate;

class JWT_EXPORT JColorButton : public JShadowFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool clickEnabled READ isClickEnabled WRITE setClickEnabled NOTIFY clickEnabledChanged)
public:
    explicit JColorButton(QWidget *parent = nullptr);
    explicit JColorButton(const QColor &color, QWidget *parent = nullptr);
    ~JColorButton() J_OVERRIDE;

    QColor color() const;
    bool isClickEnabled() const;

Q_SIGNALS:
    void colorChanged(const QColor &color);
    void clickEnabledChanged(bool enabled);
    void pressed();
    void clicked();

public Q_SLOTS:
    void setColor(const QColor &color);
    void setClickEnabled(bool enabled);

protected:
    virtual QSize sizeHint() const override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Q_DISABLE_COPY(JColorButton)
    J_DECLARE_PRIVATE(JColorButton)
};

#endif  // JCOLORBUTTON_H
