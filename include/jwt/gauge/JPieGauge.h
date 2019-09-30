#ifndef JPIEGAUGE_H
#define JPIEGAUGE_H

#include "JGauge.h"

// class JPieGauge

class JPieGaugePrivate;

class JWT_EXPORT JPieGauge : public JGauge
{
    Q_OBJECT
public:
    explicit JPieGauge(QWidget *parent = nullptr);
    explicit JPieGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JPieGauge() J_OVERRIDE;

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
    Q_DISABLE_COPY(JPieGauge)
    J_DECLARE_PRIVATE(JPieGauge)
};

#endif  // JPIEGAUGE_H
