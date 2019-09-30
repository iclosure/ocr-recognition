#ifndef JBITCHART_H
#define JBITCHART_H

#include "../global.h"
#include "JChart.h"
#include "JBitSeries.h"

namespace JChart {

class BitChartPrivate;

class JWT_EXPORT BitChart : public Chart
{
    Q_OBJECT
public:
    explicit BitChart(QWidget *parent = nullptr);
    virtual ~BitChart() J_OVERRIDE;

    QRectF &boundingRect();
    virtual QVector<QPointF> *data();

    void setXScaleDrawType(ScaleDrawType type) override;
    void setAxisX(Axis axis) override;
    void setAxisAlign(int axisId, bool align) override;
    void setAxisLabelLength(int axisId, int length) override;

    virtual void zoomReset() override;

    quint64 bitsMask() const;
    void setBitsMask(quint64 mask);
    void setBitsRange(int begin, int end);
    void setBitMask(int offset, bool on);
    bool testBitMask(int offset) const;
    void setBitsTitle(const QStringList &texts);

    virtual void updateScale(JChart::Axis axisId) override;
    void updateScaleDraw(JChart::Axis axisId, bool align, int labelLength = -1) override;

    virtual AbstractSeries *addSeries(AbstractSeries *series) override;
    void removeSeries(int index) override;
    void removeSeries(AbstractSeries *series) override;
    void clearSeries() override;

    const QVector<QPointF> &samples() const;
    void setSamples(const QVector<QPointF> &data, bool update = true);
    void appendSample(const QPointF &point, bool update = true);
    void shiftSample(const QPointF &point, bool update = true);

    void setShiftType(ShiftType type, bool update = true) override;
    void setShiftCount(int value, bool update = true) override;
    void setShiftTimeZone(qreal msecs, bool update = true) override;

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(BitChart)
    J_DECLARE_PRIVATE(BitChart)
};

} // end of namespace JChart

#endif // JBITCHART_H
