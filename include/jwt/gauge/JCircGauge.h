#ifndef JCIRCGAUGE_H
#define JCIRCGAUGE_H

#include "JGauge.h"

// class JCircGauge

class JCircGaugePrivate;

class JWT_EXPORT JCircGauge : public JGauge
{
    Q_OBJECT
public:
    explicit JCircGauge(QWidget *parent = nullptr);
    explicit JCircGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JCircGauge() J_OVERRIDE;

Q_SIGNALS:

public Q_SLOTS:

protected:
    virtual void drawBackground(QPainter *painter, const PainterContext *context) override;
    virtual void drawScale(QPainter *painter, const PainterContext *context) override;
    virtual void drawNeedle(QPainter *painter, const PainterContext *context) override;
    virtual void drawValue(QPainter *painter, const PainterContext *context) override;

    void drawNeedlePolygon(QPainter *painter, const PainterContext *context, qreal valueAngle,
                           const QColor &color);
    void drawNumeric(QPainter *painter, const PainterContext *context, qreal value,
                     const QColor &color, const QString &badgeText = QString());

private:
    Q_DISABLE_COPY(JCircGauge)
    J_DECLARE_PRIVATE(JCircGauge)
};

#endif  // JCIRCGAUGE_H
