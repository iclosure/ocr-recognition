#ifndef JTEMPGAUGE_H
#define JTEMPGAUGE_H

#include "JGauge.h"

// class JTempGauge

class JTempGaugePrivate;

class JWT_EXPORT JTempGauge : public JGauge
{
    Q_OBJECT
public:
    explicit JTempGauge(QWidget *parent = nullptr);
    explicit JTempGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JTempGauge() J_OVERRIDE;

Q_SIGNALS:

public Q_SLOTS:

protected:
    virtual void drawBackground(QPainter *painter, const PainterContext *context) override;
    virtual void drawScale(QPainter *painter, const PainterContext *context) override;
    virtual void drawNeedle(QPainter *painter, const PainterContext *context) override;
    virtual void drawValue(QPainter *painter, const PainterContext *context) override;

private:
    Q_DISABLE_COPY(JTempGauge)
    J_DECLARE_PRIVATE(JTempGauge)
};

#endif  // JTEMPGAUGE_H
