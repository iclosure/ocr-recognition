#ifndef JFREQCHART_H
#define JFREQCHART_H

#include "../global.h"
#include "../chart/JNumericChart.h"

// class JFreqChart

class JFreqChartPrivate;

class JWT_EXPORT JFreqChart : public JChart::NumericChart
{
    Q_OBJECT
public:
    explicit JFreqChart(QWidget *parent = nullptr);
    explicit JFreqChart(const QString &title, QWidget *parent = nullptr);
    virtual ~JFreqChart() J_OVERRIDE;

    void setAxisXTitle(const QString &text);
    void setAxisYTitle(const QString &text);

    void setSample(const QVector<QPointF> data, bool update = true);
    void shiftSample(qreal x, qreal y, bool update = true);
    void shiftSample(const QPointF &point, bool update = true);

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JFreqChart)
    J_DECLARE_PRIVATE(JFreqChart)
};

#endif  // JFREQCHART_H
