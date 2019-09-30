#ifndef JBUFFERCHART_H
#define JBUFFERCHART_H

#include "../global.h"
#include "JChart.h"

class JUtralEdit;

namespace JChart {

class BufferChartPrivate;

class JWT_EXPORT BufferChart : public Chart
{
    Q_OBJECT
    Q_PROPERTY(bool asciiVisible READ isAsciiVisible WRITE setAsciiVisible NOTIFY asciiVisibleChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)
    Q_PROPERTY(int showType READ showType WRITE setShowType NOTIFY showTypeChanged)
public:
    explicit BufferChart(QWidget *parent = nullptr);
    virtual ~BufferChart() J_OVERRIDE;

    bool isAsciiVisible() const;
    int columnCount() const;
    int showType() const;

    QByteArray buffer();
    void setBuffer(const QByteArray &buffer);
    void setBuffer(const uchar *buffer, int size);

    JUtralEdit *bufferView() const;

    void clearMarker() override;
    void setSeriesTitle(int index, const QString &text) override;
    void updateSeries(int index) override;
    void updateScale(JChart::Axis axisId) override;
    void updateScaleDraw(JChart::Axis axisId, bool align, int labelLength) override;
    void setAxisScale(int axisId, double minimum, double maximum, double stepSize = 0) override;

Q_SIGNALS:
    void asciiVisibleChanged(bool checked);
    void columnCountChanged(int count);
    void showTypeChanged(int showType);

public Q_SLOTS:
    void setAsciiVisible(bool visible);
    void setColumnCount(int count);
    void setShowType(int showType);
    void updateBuffer();

private:
    Q_DISABLE_COPY(BufferChart)
    J_DECLARE_PRIVATE(BufferChart)
};

} // end of namespace JChart

#endif // JBUFFER_CHART_H
