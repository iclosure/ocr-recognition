#ifndef JCHART_H
#define JCHART_H

#include "../global.h"
#include "../widget/JShadowFrame.h"

class QwtPlot;

namespace JChart {

/**
 * @brief 图表类型定义
 */
enum ChartType {
    ChartTypeUndefined = 0,     /**< 未定义图表类型 */
    ChartTypeCartesian,         /**< 笛卡尔坐标图表 */
    ChartTypePolar,             /**< 极坐标图表 */
    ChartTypeNumeric,           /**< 数值型数据图表 */
    ChartTypeBuffer,            /**< 缓冲区型数据图表 */
    ChartTypeBitMap             /**< Bit映射数据图表 */
};

/**
 * @brief 图表主题类型定义
 */
enum ChartTheme {
    ChartThemeLight = 0,        /**< */
    ChartThemeBlueCerulean,     /**< */
    ChartThemeDark,             /**< */
    ChartThemeBrownSand,        /**< */
    ChartThemeBlueNcs,          /**< */
    ChartThemeHighContrast,     /**< */
    ChartThemeBlueIcy,          /**< */
    ChartThemeQt                /**< */
};

/**
 * @brief 曲线平移方式
 */
enum ShiftType {
    ShiftInvalid = -1,  /**< Invalid */
    ShiftByCount,       /**< 以数据个数方式平移 */
    ShiftByTime         /**< 以时间带方式平移 */
};

//! \brief Axis index
enum Axis {
    //! Y axis left of the canvas
    yLeft,
    //! Y axis right of the canvas
    yRight,
    //! X axis below the canvas
    xBottom,
    //! X axis above the canvas
    xTop,
    //! Number of axes
    axisCnt
};

/*!
    Position of the legend, relative to the canvas.
    \sa insertLegend()
 */
enum LegendPosition {
    //! The legend will be left from the QwtPlot::yLeft axis.
    LeftLegend,
    //! The legend will be right from the QwtPlot::yRight axis.
    RightLegend,
    //! The legend will be below the footer
    BottomLegend,
    //! The legend will be above the title
    TopLegend
};

/**
 * @brief The ScaleDrawType enum
 */
enum ScaleDrawType
{
    InvalidScaleDraw = -1,
    ScaleDrawDefault,   /**<  */
    ScaleDrawTime       /**<  */
};

enum ScaleComponent
{
    Backbone = 0x01,
    Ticks = 0x02,
    Labels = 0x04
};

/**
 * @brief The NumericType enum
 */
enum NumericType {
    NumericInvalid = -1,
    NumericI8,
    NumericU8,
    NumericI16,
    NumericU16,
    NumericI32,
    NumericU32,
    NumericI64,
    NumericU64,
    NumericF32,
    NumericF64,
    NumericTotal
};

/**
 * @brief The ChartActionFlag enum
 */
enum ChartActionFlag {
    Chart_NoAction = 0x0000,
    Chart_ZoomInAction = 0x0001,
    Chart_ZoomOutAction = 0x0002,
    Chart_ResetZoomAction = 0x0004,
    Chart_SelectAreaAction = 0x0008,
    Chart_FullScreenAction = 0x0010,
    Chart_FloatingAction = 0x0020,
    Chart_ClearMarkerAction = 0x0040,
    Chart_PlayAction = 0x0080,
    Chart_CopyChartAction = 0x0100,
    Chart_ExportAction = 0x0200,
    Chart_RemoveChartAction = 0x0400,
    Chart_SettingsAction = 0x0800,
    Chart_HelpAction = 0x1000,
    Chart_AllActions = 0xffff,

    Chart_Zoom = Chart_ZoomInAction | Chart_ZoomOutAction | Chart_ResetZoomAction,
};
Q_DECLARE_FLAGS(ChartActionFlags, ChartActionFlag)

//

class ChartPrivate;
class AbstractSeries;
class AbstractAxis;
class JPlotZoomer;
class ZoneSlider;

class JWT_EXPORT Chart : public JShadowFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor zoomerColor READ zoomerColor WRITE setZoomerColor NOTIFY zoomerColorChanged)
public:
    explicit Chart(ChartType type, QWidget *parent = nullptr);
    virtual ~Chart() J_OVERRIDE;

    QColor zoomerColor() const;

    ChartType chartType() const;
    void setChartType(ChartType type);

    ChartTheme chartTheme() const;
    void setChartTheme(ChartTheme value, bool useInternal = false);

    ScaleDrawType xScaleDrawType() const;
    virtual void setXScaleDrawType(ScaleDrawType type);

    QString identity() const;
    void setIdentity(const QString &identity);

    QString title() const;
    void setTitle(const QString &value);

    void zoomIn();
    void zoomOut();
    void zoomIn(const QRectF &rect);
    void zoom(qreal factor);
    virtual void zoomReset();
    bool isZoomed();
    void scroll(qreal dx, qreal dy);
    QRectF zoomBase() const;
    void setZoomBase(const QRectF &rect);
    void setZoomBaseY(qreal yMin, qreal yMax);
    void setZoomBase(bool replot = true);
    QRectF zoomRect() const;
    uint zoomRectIndex() const;
    void resetZoomer();

    virtual void clearMarker();

    Axis axisX() const;
    virtual void setAxisX(Axis axis);
    void addAxis(AbstractAxis *axis, Qt::Alignment alignment);
    void removeAxis(AbstractAxis *axis);
    QList<AbstractAxis *> axes(Qt::Orientations orientations = Qt::Horizontal | Qt::Vertical,
                                AbstractSeries *series = nullptr) const;
    void createDefaultAxes();
    void setAxisVisible(int axisId, bool visible);
    void setAxisEnabled(int axisId, bool enabled);
    void enableAxisComponent(int axisId, ScaleComponent component, bool enable = true);
    bool hasAxisComponent(int axisId, ScaleComponent component) const;
    void enableAxis(int axisId, bool enabled = true);
    bool axisEnabled(int axisId) const;
    virtual void setAxisAlign(int axisId, bool align);
    virtual void setAxisLabelLength(int axisId, int length);

    void setGridEnabled(Qt::Orientations orientations, bool enabled);
    void setGridPen(const QPen &pen);

    ShiftType shiftType() const;
    virtual void setShiftType(ShiftType type, bool update = true);
    int defaultShiftCount() const;
    virtual void setDefaultShiftCount(int count, bool update = true);
    int shiftCount() const;
    virtual void setShiftCount(int count, bool update = true);
    qreal defaultShiftTimeZone() const;
    virtual void setDefaultShiftTimeZone(qreal msecs, bool update = true);
    qreal shiftTimeZone() const;
    virtual void setShiftTimeZone(qreal msecs, bool update = true);

    void setTitleVisible(bool visible);

    bool isFloating() const;

    QwtPlot *plot();

    JPlotZoomer *zoomer();

    void resizeSeries(int size);
    virtual AbstractSeries *addSeries(const QString &id, const QString &title);
    virtual AbstractSeries *addSeries(const QString &id, const QPen &pen,
                                       const QString &title = QString());
    virtual AbstractSeries *addSeries(AbstractSeries *series);
    virtual void removeSeries(int index);
    virtual void removeSeries(AbstractSeries *series);
    virtual void clearSeries();
    virtual void setSeries(int index, AbstractSeries *series);
    QVector<AbstractSeries *> series();
    const QVector<AbstractSeries *> &series() const;
    int seriesCount() const;
    AbstractSeries *seriesAt(int index) const;
    AbstractSeries *seriesAt(const QString &identity) const;
    int indexOfSeries(AbstractSeries *series) const;
    void setSeriesPen(int index, const QPen &pen);

    virtual void setSeriesTitle(int index, const QString &text);
    virtual void updateSeries(int index);
    virtual void updateScale(JChart::Axis axisId);
    virtual void updateScaleDraw(JChart::Axis axisId, bool align, int labelLength);
    virtual void setAxisScale(int axisId, double minimum, double maximum, double stepSize = 0);

    QRectF siftArea() const;
    void setSiftArea(const QRectF &area);

    qreal axisStepSize(int axisId) const;

    QPair<qreal, qreal> axisInterval(Axis axisId) const;

    QColor queryColor(int index = -1) const;
    static QColor queryColor(int index, ChartTheme theme);

    bool zoneVisible() const;
    void setZoneVisible(bool visible);
    void setLegendVisible(bool visible);

    ZoneSlider *zoneSlider();
    const ZoneSlider *zoneSlider() const;

    void replot();

    bool isPlay() const;

    QObjectUserData *userData() const;
    void setUserData(QObjectUserData *data);

    void setTrackerPos(int index, const QPointF &pos = QPointF(-1, -1));
    void markTrackerPos(const QPointF &pos);

    QList<QColor> colorPalette();
    const QList<QColor> &colorPalette() const;
    void setColorPalette(const QList<QColor> &colors);
    static QList<QColor> colorPalette(ChartTheme theme = ChartThemeDark);

    QWidget *bufferView() const;

    //
    ChartActionFlags chartActionFlags() const;
    bool testChartActionFlag(ChartActionFlag flag) const;
    void setChartActionFlag(ChartActionFlag flag, bool on = true);
    void setChartActionFlags(ChartActionFlags flags);

    void setAxisLabelAlignment(int axisId, Qt::Alignment alignment);
    void setAxisLabelRotation( int axisId, double rotation);

    void setAxisTitle(int axisId, const QString &text);
    QString axisTitle(int axisId) const;

    void setAxisMaxMinor(int axisId, int maxMinor);
    int axisMaxMinor(int axisId) const;

    void setAxisMaxMajor(int axisId, int maxMajor);
    int axisMaxMajor(int axisId) const;

Q_SIGNALS:
    void zoomerColorChanged(const QColor &color);

    void axisIntervalChanged(int axisId, qreal minimum, qreal maximum);
    void scaleDivChanged(int axisId, qreal minimum, qreal maximum);
    void triggledPlay(bool checked);
    void seriesRemoved(int index);
    void triggledZoomReset();
    void triggledClose();
    void trackerChanged(int index, const QPointF &pos);
    void trackerMarked(const QPointF &pos);
    void trackerMarkerCleared();
    void defShiftCountChanged(int count);
    void defaultShiftTimeZoneChanged(qreal value);
    void colorPaletteChanged();

public Q_SLOTS:
    void setZoomerColor(const QColor &color);
    void togglePlay(bool checked);
    void setTrackIndex(int index);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Q_DISABLE_COPY(Chart)
    J_DECLARE_PRIVATE(Chart)
};

} // end of namespace JChart

#endif // JCHART_H
