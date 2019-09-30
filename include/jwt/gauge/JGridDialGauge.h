#ifndef JGRIDDIALGAUGE_H
#define JGRIDDIALGAUGE_H

#include "../global.h"
#include "JDialGauge.h"
#include "../widget/JTitleFrame.h"

// class JGridDialGauge

class JGridDialGaugePrivate;
class QGraphicsDropShadowEffect;

class JWT_EXPORT JGridDialGauge : public JTitleFrame
{
    Q_OBJECT
public:
    explicit JGridDialGauge(QWidget *parent = nullptr);
    explicit JGridDialGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JGridDialGauge() J_OVERRIDE;

    qreal minimum() const;
    qreal maximum() const;
    qreal value(int index) const;
    int decimals() const;
    QString suffix() const;
    int count() const;
    int rowCount() const;
    int columnCount() const;

    void addWarningRange(int id, qreal from, qreal to, const QColor &color);
    void removeWarningRange(int id);
    const QMap<int, JDialGauge::WarningContext> &warnRanges() const;

    static qreal fromCoordAngle(qreal angle);
    static qreal toCoordAngle(qreal angle);

    void setPrefixes(const QStringList &prefixes);

    void setHorizontalSpacing(int spacing);
    void setVerticalSpacing(int spacing);

Q_SIGNALS:

public Q_SLOTS:
    void setMinimum(qreal value);
    void setMaximum(qreal value);
    void setRange(qreal minimum, qreal maximum);
    void setValue(int index, qreal value);
    void setDecimals(int value);
    void setSuffix(const QString &text);
    void setColorRange(const QColor &startColor, const QColor &endColor);
    void setCount(int count, int lineCount, Qt::Orientation orientation = Qt::Horizontal);

private:
    Q_DISABLE_COPY(JGridDialGauge)
    J_DECLARE_PRIVATE(JGridDialGauge)
};

#endif  // JGRIDDIALGAUGE_H
