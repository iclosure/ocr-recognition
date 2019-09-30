#ifndef JFILENUMERICCHART_H
#define JFILENUMERICCHART_H

#include "../global.h"
#include "JNumericChart.h"
#include "JBitSeries.h"

namespace JChart {

class FileNumericChartPrivate;

class JWT_EXPORT FileNumericChart : public NumericChart
{
    Q_OBJECT
public:
    explicit FileNumericChart(QWidget *parent = nullptr);
    virtual ~FileNumericChart() J_OVERRIDE;

    void zoomReset() override;

    AbstractSeries *addSeries(const QString &id, const QPen &pen,
                              const QString &title = QString()) override;

    void updateScale(JChart::Axis axisId) override;

    QPair<qreal, qreal> xRange() const;

    void setBuffer(const uchar *buffer, size_t bufferSize, int bufferStep, bool update = true);

Q_SIGNALS:
    void zoneAreaChanged(const QRectF &range);

public Q_SLOTS:

private:
    Q_DISABLE_COPY(FileNumericChart)
    J_DECLARE_PRIVATE(FileNumericChart)
};

} // end of namespace JChart

#endif // JNUMERICCHART_H
