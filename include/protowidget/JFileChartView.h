#ifndef PROTOWIDGET_JFILECHARTVIEW_H
#define PROTOWIDGET_JFILECHARTVIEW_H

#include <QWidget>
#include "global.h"

namespace JChart { class View; }

class QStandardItem;

namespace J {

class Table;
typedef std::shared_ptr<Table> TablePtr;

// class FileChartView

class FileChartViewPrivate;

class PROTOWIDGET_EXPORT FileChartView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool xAxisSync READ xAxisSync WRITE setXAxisSync NOTIFY xAxisSyncChanged)
    Q_PROPERTY(bool replaying READ isReplaying NOTIFY replayingChanged)
    Q_PROPERTY(int replayPeriod READ replayPeriod WRITE setReplayPeriod NOTIFY replayPeriodChanged)
public:
    explicit FileChartView(QWidget *parent = nullptr);
    explicit FileChartView(bool styled, QWidget *parent = nullptr);
    virtual ~FileChartView() J_OVERRIDE;

    bool xAxisSync() const;
    bool isReplaying() const;
    int replayPeriod() const;

    QList<QList<QColor> > curveColorPalette() const;

    JChart::View *chartView() const;
    void focusItem(const QString &domain);
    void removeItem(const QString &domain);
    void removeChart(const QString &domain);
    void reset();
    void clearCharts();

    void addTable(const QString &filePath, const TablePtr &table);
    void removeTable(const QString &filePath);
    TablePtr tableByFilePath(const QString &filePath) const;

    void addFreqDomainView(QStandardItem *itemTable, QStandardItem *item);

Q_SIGNALS:
    void xAxisSyncChanged(bool value);
    void replayingChanged(bool replaying);
    void replayPeriodChanged(int value);
    void replayFinished();

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
    void setReplayPeriod(int value);
    void updateData();
    void startReplay();
    void stopReplay();
    void toggleReplay(bool enabled);

    void setColumnWidthSame();

    void setCurveColorPalette(const QList<QList<QColor> > &palette);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Q_DISABLE_COPY(FileChartView)
    J_DECLARE_PRIVATE(FileChartView)
};

}   // end of namespace J

#endif // PROTOWIDGET_JFILECHARTVIEW_H
