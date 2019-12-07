#ifndef JFILEBITCHART_H
#define JFILEBITCHART_H

#include "../global.h"
#include "JBitChart.h"
#include "JBitSeries.h"

namespace JChart {

class FileBitChartPrivate;

class JWT_EXPORT FileBitChart : public BitChart
{
    Q_OBJECT
public:
    explicit FileBitChart(QWidget *parent = nullptr);
    virtual ~FileBitChart() J_OVERRIDE;

    QVector<QPointF> *data() override;

    void zoomReset() override;

    void updateScale(JChart::Axis axisId) override;

    AbstractSeries *addBitSeries(int index, int yOffset, int maskOffset) override;

    void setBuffer(const uchar *buffer, size_t bufferSize, int bufferStep, bool update = true);
    void setAttributes(uchar xSize, uchar ySize, int xOffset, int yOffset, bool update = true);

    qreal axisMinValue(int axisId) const;
    qreal axisMaxValue(int axisId) const;

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(FileBitChart)
    J_DECLARE_PRIVATE(FileBitChart)
};

} // end of namespace JChart

#endif // JFILEBITCHART_H
