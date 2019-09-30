#ifndef JRAYGAUGE_H
#define JRAYGAUGE_H

#include "JGauge.h"

// class JRayGauge

class JRayGaugePrivate;

class JWT_EXPORT JRayGauge : public JGauge
{
    Q_OBJECT
public:
    explicit JRayGauge(QWidget *parent = nullptr);
    explicit JRayGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JRayGauge() J_OVERRIDE;

Q_SIGNALS:

public Q_SLOTS:

protected:
    virtual void drawBackground(QPainter *painter, const PainterContext *context) override;
    virtual void drawScale(QPainter *painter, const PainterContext *context) override;
    virtual void drawNeedle(QPainter *painter, const PainterContext *context) override;
    virtual void drawValue(QPainter *painter, const PainterContext *context) override;

private:
    Q_DISABLE_COPY(JRayGauge)
    J_DECLARE_PRIVATE(JRayGauge)
};

#endif  // JRAYGAUGE_H
