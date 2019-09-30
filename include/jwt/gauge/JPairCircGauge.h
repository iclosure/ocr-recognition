#ifndef JPAIRPairCircGauge_H
#define JPAIRPairCircGauge_H

#include "JCircGauge.h"

// class JPairCircGauge

class JPairCircGaugePrivate;

class JWT_EXPORT JPairCircGauge : public JCircGauge
{
    Q_OBJECT
    Q_PROPERTY(QColor color2 READ color2 WRITE setColor2 NOTIFY color2Changed)
    Q_PROPERTY(qreal value2 READ value2 WRITE setValue2 NOTIFY value2Changed)
public:
    explicit JPairCircGauge(QWidget *parent = nullptr);
    explicit JPairCircGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JPairCircGauge() J_OVERRIDE;

    QColor color2() const;
    qreal value2() const;

signals:
    void color2Changed(const QColor &color);
    void value2Changed(qreal value);

public slots:
    void setColor2(const QColor &color);
    void setValue2(qreal value, bool animation = false);

protected:
    virtual void drawBackground(QPainter *painter, const PainterContext *context) override;
    virtual void drawNeedle(QPainter *painter, const PainterContext *context) override;
    virtual void drawValue(QPainter *painter, const PainterContext *context) override;

private:
    Q_DISABLE_COPY(JPairCircGauge)
    J_DECLARE_PRIVATE(JPairCircGauge)
};

#endif  // JPAIRPairCircGauge_H
