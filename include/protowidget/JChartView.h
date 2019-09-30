#ifndef PROTOWIDGET_JCHARTVIEW_H
#define PROTOWIDGET_JCHARTVIEW_H

#include <QWidget>
#include "global.h"

namespace JChart { class View; }

class QStandardItem;

namespace J {

class Worker;
typedef std::shared_ptr<Worker> WorkerPtr;

class ChartViewPrivate;

class PROTOWIDGET_EXPORT ChartView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool xAxisSync READ xAxisSync WRITE setXAxisSync NOTIFY xAxisSyncChanged)
    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged)
public:
    explicit ChartView(QWidget *parent = nullptr);
    explicit ChartView(bool styled, QWidget *parent = nullptr);
    virtual ~ChartView() J_OVERRIDE;

    bool xAxisSync() const;
    bool isRunning() const;

    QList<QList<QColor> > curveColorPalette() const;

    JChart::View *chartView() const;
    void changeWorker(const QString &domain, const WorkerPtr &worker);
    void focusItem(const QString &domain);
    void removeItem(const QString &domain);
    void removeChart(const QString &domain);
    void clearCharts();

    void addFreqDomainView(QStandardItem *itemTable, QStandardItem *item);

Q_SIGNALS:
    void xAxisSyncChanged(bool value);
    void runningChanged(bool value);

public Q_SLOTS:
    void setColumnCount(int count);
    void setYLabelVisible(bool checked);
    void setYAlignEnabled(bool align);
    void setYLabelLength(int length);
    void setXAxisSync(bool value);
    void setSyncTrack(bool enabled);
    void setAsciiVisible(bool visible);
    void setHexColumnCount(int count);
    void setChartTheme(int chartTheme);
    void setRunning(bool value);

    void setColumnWidthSame();

    void setCurveColorPalette(const QList<QList<QColor> > &palette);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Q_DISABLE_COPY(ChartView)
    J_DECLARE_PRIVATE(ChartView)
};

}   // end of namespace J

#endif // PROTOWIDGET_JCHARTVIEW_H
