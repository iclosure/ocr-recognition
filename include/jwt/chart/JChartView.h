#ifndef JCHARTVIEW_H
#define JCHARTVIEW_H

#include "../global.h"
#include "JChart.h"
#include <QWidget>
#include <QResizeEvent>

class JTableView;

namespace JChart {

class ViewPrivate;
class Chart;
class AbstractSeries;

class JWT_EXPORT View : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)
    Q_PROPERTY(bool yLabelVisible READ yLabelVisible WRITE setYLabelVisible NOTIFY yLabelVisibleChanged)
    Q_PROPERTY(bool yAlignEnabled READ yAlignEnabled WRITE setYAlignEnabled NOTIFY yAlignEnabledChanged)
    Q_PROPERTY(int yLabelLength READ yLabelLength WRITE setYLabelLength NOTIFY yLabelLengthChanged)
    Q_PROPERTY(bool asciiVisible READ asciiVisible WRITE setAsciiVisible NOTIFY asciiVisibleChanged)
    Q_PROPERTY(int hexColumnCount READ hexColumnCount WRITE setHexColumnCount NOTIFY hexColumnCountChanged)
    Q_PROPERTY(bool xAxisSync READ xAxisSync WRITE setXAxisSync NOTIFY xAxisSyncChanged)
    Q_PROPERTY(bool zoomSync READ zoomSync WRITE setZoomSync NOTIFY zoomSyncChanged)
    Q_PROPERTY(bool syncTrack READ syncTrack WRITE setSyncTrack NOTIFY syncTrackChanged)
    Q_PROPERTY(JChart::ChartTheme chartTheme READ chartTheme WRITE setChartTheme NOTIFY chartThemeChanged)
public:
    explicit View(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit View(bool styled, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~View() J_OVERRIDE;

    int rowCount() const;
    int columnCount() const;
    bool yLabelVisible() const;
    bool yAlignEnabled() const;
    int yLabelLength() const;
    bool asciiVisible() const;
    int hexColumnCount() const;
    bool xAxisSync() const;
    bool zoomSync() const;
    bool syncTrack() const;
    JChart::ChartTheme chartTheme() const;

    JTableView *view() const;
    bool isStyled() const;

    void appendChart(Chart *chart);
    void insertChart(int index, Chart *chart);
    bool removeChart(Chart *chart);
    bool removeChart(int row, int column);
    void removeSeries(const QString &identity, bool fuzzy = true);
    void removeChart(const QString &identity, bool fuzzy = true);
    void clearChart();
    int chartCount() const;
    Chart *chartAt(int index) const;
    Chart *chartAt(int row, int column) const;
    Chart *chartAt(const QPoint &pos) const;
    JChart::Chart *lastChart(JChart::Chart *except) const;
    int indexOfChart(Chart *chart);
    QList<Chart *> charts() const;
    Chart *chartByIdentity(const QString &identity, bool fuzzy = true) const;
    AbstractSeries *seriesByIdentity(const QString &identity, bool fuzzy = true) const;
    void focusChart(int index);
    void focusChart(int row, int column);
    void focusChart(const QString &identity);
    void focusChart(Chart *chart);
    void focusSeries(const QString &identity);

    bool setTrackerChangedNotify(bool enabled);
    bool setTrackerMarkedNotify(bool enabled);
    bool setTrackerMarkerClearedNotify(bool enabled);
    bool setScaleDivChangedNotify(JChart::Chart *chart, bool enabled);

Q_SIGNALS:
    void rowCountChanged(int count);
    void columnCountChanged(int count);
    void yLabelVisibleChanged(bool visible);
    void yAlignEnabledChanged(bool enabled);
    void yLabelLengthChanged(int length);
    void asciiVisibleChanged(bool visible);
    void hexColumnCountChanged(int count);
    void xAxisSyncChanged(bool enabled);
    void zoomSyncChanged(bool enabled);
    void syncTrackChanged(bool enabled);
    void chartThemeChanged(JChart::ChartTheme theme);

    void itemPressed(JChart::Chart *chart, int row, int column);
    void itemClicked(JChart::Chart *chart, int row, int column);
    void itemDoubleClicked(JChart::Chart *chart, int row, int column);

    void triggledZoomReset(JChart::Chart *chart);
    void triggledClose(JChart::Chart *chart);
    void seriesRemoved(int row, int column);
    void trackerChanged(JChart::Chart *chart, int index, const QPointF &pos);
    void trackerMarked(JChart::Chart *chart, const QPointF &pos);
    void trackerMarkerCleared(JChart::Chart *chart);

public Q_SLOTS:
    void setColumnCount(int count);
    void setYLabelVisible(bool visible);
    void setYAlignEnabled(bool enabled);
    void setYLabelLength(int length);
    void setAsciiVisible(bool visible);
    void setHexColumnCount(int count);
    void setXAxisSync(bool enabled);
    void setZoomSync(bool enabled);
    void setSyncTrack(bool enabled, bool clear = false);
    void setChartTheme(JChart::ChartTheme chartTheme);

    void setAllSync(bool enabled);
    void setColumnWidthSame();
    void updateScales();
    void resetZoom();
    void clearMarker();
    void clearSyncTrack();
    void updateSyncScale(JChart::Chart *chart, int axisId, qreal minimum, qreal maximum);

    void selectRow(int row);
    void selectColumn(int column);
    void hideRow(int row);
    void hideColumn(int column);
    void showRow(int row);
    void showColumn(int column);
    void resizeRowToContents(int row);
    void resizeRowsToContents();
    void resizeColumnToContents(int column);
    void resizeColumnsToContents();
    void sortByColumn(int column);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void onTriggledZoomReset(JChart::Chart *chart);
    void onTrackerChanged(JChart::Chart *chart, int index, const QPointF &pos);
    void onTrackerMarked(JChart::Chart *chart, const QPointF &pos);
    void onTrackerMarkerCleared(JChart::Chart *chart);
    void onScaleDivChanged(int axisId, qreal minimum, qreal maximum);

private:
    Q_DISABLE_COPY(View)
    J_DECLARE_PRIVATE(View)
};

} // end of namesoace JChart

#endif // JCHARTVIEW_H
