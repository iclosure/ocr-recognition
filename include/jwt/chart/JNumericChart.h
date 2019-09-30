#ifndef JNUMERICCHART_H
#define JNUMERICCHART_H

#include "../global.h"
#include "JChart.h"
#include "JBitSeries.h"

namespace JChart {

class NumericChartPrivate;

class JWT_EXPORT NumericChart : public Chart
{
    Q_OBJECT
public:
    explicit NumericChart(QWidget *parent = nullptr);
    virtual ~NumericChart() J_OVERRIDE;

    void setXScaleDrawType(ScaleDrawType type) override;

    AbstractSeries *addSeries(const QString &id, const QString &title) override;
    AbstractSeries *addSeries(const QString &id, const QPen &pen,
                               const QString &title = QString()) override;

    void updateScale(JChart::Axis axis) override;
    void updateScaleDraw(JChart::Axis axisId, bool align, int labelLength) override;

    void setAxisAlign(int axisId, bool align) override;
    void setAxisLabelLength(int axisId, int length) override;

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(NumericChart)
    J_DECLARE_PRIVATE(NumericChart)
};

} // end of namespace JChart

#endif // JNUMERICCHART_H
