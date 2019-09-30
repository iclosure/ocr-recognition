#ifndef JTITLEFRAME_H
#define JTITLEFRAME_H

#include "JShadowFrame.h"
#include <QVBoxLayout>

class JTitleFramePrivate;

class JWT_EXPORT JTitleFrame : public JShadowFrame
{
    Q_OBJECT
    Q_PROPERTY(bool titleShadowEnabled READ isTitleShadowEnabled WRITE setTitleShadowEnabled NOTIFY titleShadowEnabledChanged)
    Q_PROPERTY(qreal titleBlurRadius READ titleBlurRadius WRITE setTitleBlurRadius NOTIFY titleBlurRadiusChanged)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
    Q_PROPERTY(int style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool titleVisible READ isTitleVisible WRITE setTitleVisible)
    Q_PROPERTY(bool clickable READ isClickable WRITE setClickable NOTIFY clickableChanged)
public:
    explicit JTitleFrame(QWidget *parent = nullptr);
    explicit JTitleFrame(const QString &title, QWidget *parent = nullptr);
    virtual ~JTitleFrame() J_OVERRIDE;

    bool isTitleShadowEnabled() const;
    qreal titleBlurRadius() const;
    QGraphicsDropShadowEffect *titleEffect() const;

    int borderWidth() const;
    int style() const;
    virtual QString title() const;
    bool isTitleVisible() const;
    bool isClickable() const;

    QVBoxLayout *mainLayout() const;
    QRect titleRect() const;

    QWidget *titleBar() const;
    void setTitleBar(QWidget *widget);

Q_SIGNALS:
    void titleShadowEnabledChanged(bool enabled);
    void titleBlurRadiusChanged(qreal blurRadius);
    void borderWidthChanged(int value);
    void styleChanged(int style);
    void titleChanged(const QString &text);
    void titleVisibleChanged(bool visible);
    void clickableChanged(bool enabled);
    void pressed();
    void clicked();

public Q_SLOTS:
    void setTitleShadowEnabled(bool enabled);
    void setTitleBlurRadius(qreal radius);
    void setBorderWidth(int value);
    void setStyle(int style);
    virtual void setTitle(const QString &text);
    void setTitleVisible(bool visible);
    void setClickable(bool enabled);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Q_DISABLE_COPY(JTitleFrame)
    J_DECLARE_PRIVATE(JTitleFrame)
};

#endif // JTITLEFRAME_H
