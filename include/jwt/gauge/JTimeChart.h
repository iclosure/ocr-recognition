#ifndef JTIMECHART_H
#define JTIMECHART_H

#include "../global.h"
#include "../chart/JNumericChart.h"

// class JTimeChart

class JTimeChartPrivate;

class JWT_EXPORT JTimeChart : public JChart::NumericChart
{
    Q_OBJECT
    Q_PROPERTY(bool valueVisible READ valueVisible WRITE setValueVisible NOTIFY valueVisibleChanged)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(QString highlightText READ highlightText WRITE setHighlightText NOTIFY highlightTextChanged)
    Q_PROPERTY(QColor highlightTextColor READ highlightTextColor WRITE setHighlightTextColor NOTIFY highlightTextColorChanged)
public:
    explicit JTimeChart(QWidget *parent = nullptr);
    explicit JTimeChart(const QString &title, QWidget *parent = nullptr);
    virtual ~JTimeChart() J_OVERRIDE;

    bool valueVisible() const;
    QString suffix() const;
    int decimals() const;

    QString highlightText() const;
    QColor highlightTextColor() const;

    void shiftSample(qreal x, qreal y, bool update = true);
    void shiftSample(const QPointF &point, bool update = true);

    void setSample(const QVector<QPointF> &samples, bool update = true);
    void clearSample();

Q_SIGNALS:
    void valueVisibleChanged(bool visible);

    void highlightTextChanged(const QString &text);
    void highlightTextColorChanged(const QColor &color);

public Q_SLOTS:
    void setValueVisible(bool visible);
    void setSuffix(const QString &text);
    void setDecimals(int value);

    void setHighlightText(const QString &text);
    void setHighlightTextColor(const QColor &color);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(JTimeChart)
    J_DECLARE_PRIVATE(JTimeChart)
};

#endif  // JTIMECHART_H
