#ifndef JVALUELABEL_H
#define JVALUELABEL_H

#include "JTextLabel.h"

// class JValueLabel

class JValueLabelPrivate;

class JWT_EXPORT JValueLabel : public JTextLabel
{
    Q_OBJECT
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(qreal value2 READ value2 WRITE setValue2 NOTIFY value2Changed)
public:
    explicit JValueLabel(QWidget *parent = nullptr);
    explicit JValueLabel(const QString &title, QWidget *parent = nullptr);
    virtual ~JValueLabel() J_OVERRIDE;

    qreal minimum() const;
    qreal maximum() const;
    int decimals() const;
    QString suffix() const;
    qreal value() const;
    qreal value2() const;

Q_SIGNALS:
    void minimumChanged(qreal value);
    void maximumChanged(qreal value);
    void rangeChanged(qreal minimum, qreal maximum);
    void decimalsChanged(int value);
    void suffixChanged(const QString &text);
    void valueChanged(qreal value);
    void value2Changed(qreal value);

public Q_SLOTS:
    void setMinimum(qreal value);
    void setMaximum(qreal value);
    void setRange(qreal minimum, qreal maximum);
    void setDecimals(int value);
    void setSuffix(const QString &text);
    void setValue(qreal value, bool animation = false);
    void setValue2(qreal value, bool animation = false);
    void setValue(int index, qreal value);

protected:
    virtual void drawValue(QPainter *painter, const JGauge::PainterContext *context) override;
    virtual void drawNumeric(QPainter *painter, const JGauge::PainterContext *context,
                          qreal value, const QColor &color);

private:
    Q_DISABLE_COPY(JValueLabel)
    J_DECLARE_PRIVATE(JValueLabel)
};

#endif  // JVALUELABEL_H
