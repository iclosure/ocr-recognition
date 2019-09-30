#ifndef JPAIRPairPieGauge_H
#define JPAIRPairPieGauge_H

#include "JPieGauge.h"

// class JPairPieGauge

class JPairPieGaugePrivate;

class JWT_EXPORT JPairPieGauge : public JPieGauge
{
    Q_OBJECT
    Q_PROPERTY(QColor color2 READ color2 WRITE setColor2 NOTIFY color2Changed)
    Q_PROPERTY(qreal value2 READ value2 WRITE setValue2 NOTIFY value2Changed)
public:
    explicit JPairPieGauge(QWidget *parent = nullptr);
    explicit JPairPieGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JPairPieGauge() J_OVERRIDE;

    QColor color2() const;
    qreal value2() const;

Q_SIGNALS:
    void color2Changed(const QColor &color);
    void value2Changed(qreal value);

public Q_SLOTS:
    void setColor2(const QColor &color);
    void setValue2(qreal value, bool animation = false);

protected:
    virtual void drawNeedle(QPainter *painter, const PainterContext *context) override;
    virtual void drawValue(QPainter *painter, const PainterContext *context) override;

private:
    Q_DISABLE_COPY(JPairPieGauge)
    J_DECLARE_PRIVATE(JPairPieGauge)
};

#endif  // JPairPieGauge_H
