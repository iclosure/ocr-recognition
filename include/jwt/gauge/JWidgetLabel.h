#ifndef JWIDGETLABEL_H
#define JWIDGETLABEL_H

#include "JGauge.h"
#include "../widget/JTitleFrame.h"

// class JWidgetLabel

class JWidgetLabelPrivate;
class QGraphicsDropShadowEffect;
class QVBoxLayout;

class JWT_EXPORT JWidgetLabel : public JTitleFrame
{
    Q_OBJECT
    Q_PROPERTY(QSize contentSize READ contentSize WRITE setContentSize NOTIFY contentSizeChanged)
public:
    explicit JWidgetLabel(QWidget *parent = nullptr);
    explicit JWidgetLabel(const QString &title, QWidget *parent = nullptr);
    virtual ~JWidgetLabel() J_OVERRIDE;

    QSize contentSize() const;

    virtual QSize minimumSizeHint() const override;

Q_SIGNALS:
    void contentSizeChanged(const QSize &size);

public Q_SLOTS:
    void setContentSize(const QSize &size);

protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void drawTitle(QPainter *painter, const JGauge::PainterContext *context);
    virtual void drawBackground(QPainter *painter, const JGauge::PainterContext *context);
    virtual void drawScale(QPainter *painter, const JGauge::PainterContext *context);
    virtual void drawValue(QPainter *painter, const JGauge::PainterContext *context);

private:
    Q_DISABLE_COPY(JWidgetLabel)
    J_DECLARE_PRIVATE(JWidgetLabel)
};

#endif  // JWIDGETLABEL_H
