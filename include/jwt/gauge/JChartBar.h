#ifndef JCHARTBAR_H
#define JCHARTBAR_H

#include "../global.h"
#include "../widget/JTitleFrame.h"

class JChartBarPrivate;

class JWT_EXPORT JChartBar : public JTitleFrame
{
    Q_OBJECT
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)
    Q_PROPERTY(bool colorMapVisible READ colorMapVisible WRITE setColorMapVisible)
    Q_PROPERTY(QColor colorMapFrom READ colorMapFrom)
    Q_PROPERTY(QColor colorMapTo READ colorMapTo)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
public:
    explicit JChartBar(QWidget *parent = nullptr);
    explicit JChartBar(const QString &title, QWidget *parent = nullptr);
    virtual ~JChartBar() J_OVERRIDE;

    int decimals() const;
    bool colorMapVisible() const;
    QColor colorMapFrom() const;
    QColor colorMapTo() const;
    Qt::Orientation orientation() const;

    void exportChart();

    void setSamples(const QVector<double> &data);
    void setRange(qreal minimum, qreal maximum);
    void setStep(qreal step);
    void setMarkerEnabled(bool enabled);
    void setMarkerPos(const QString &format, qreal pos, int decimals = 0);
    void setMarkerPen(const QPen &pen);

Q_SIGNALS:
    void decimalsChanged(int value);

public Q_SLOTS:
    void setDecimals(int value);
    void setColorMapVisible(bool visible);
    void setColorMapRange(const QColor &colorFrom, const QColor &colorTo);
    void setOrientation(Qt::Orientation orientation);

private:
    Q_DISABLE_COPY(JChartBar)
    J_DECLARE_PRIVATE(JChartBar)
};

#endif
