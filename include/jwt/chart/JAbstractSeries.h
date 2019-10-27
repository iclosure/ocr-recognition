#ifndef JABSTRACTSERIES_H
#define JABSTRACTSERIES_H

#include "../global.h"
#include <QObject>

class QwtPlotCurve;
class JSeriesData;

namespace JChart {

class Chart;
class AbstractSeriesPrivate;

class JWT_EXPORT AbstractSeries
{
public:
    enum CurveStyle {
        NoCurve = -1,
        Line,
        Sticks,
        Steps,
        Dots,
        UserCurve = 100
    };

    enum CurveAttribute {
        Inverted = 0x01,
        Fitted = 0x02
    };
    Q_FLAGS(CurveAttribute)

    enum LegendAttribute {
        NoAttrinute = 0x00,
        ShowLine = 0x01,
        ShowSymbol = 0x02,
        ShowBrush = 0x04
    };
    Q_FLAGS(LegendAttribute)

    enum PaintAttribute {
        ClipPolygons = 0x01,
        FilterPoints = 0x02,
        MinimizeMemory = 0x04,
        ImageBuffer = 0x08
    };

    enum SymbolStyle
    {
        NoSymbol = -1,
        Ellipse,
        Rect,
        Diamond,
        Triangle,
        DTriangle,
        UTriangle,
        LTriangle,
        RTriangle,
        Cross,
        XCross,
        HLine,
        VLine,
        Star1,
        Star2,
        Hexagon,
        Path,
        Pixmap,
        Graphic,
        SvgDocument,
        UserStyle = 1000
    };
    Q_FLAGS(PaintAttribute)

    explicit AbstractSeries(const QString &title = QString());
    virtual ~AbstractSeries();

    QString identity() const;
    void setIdentity(const QString &identity);

    void setCurveStyle(CurveStyle style);
    CurveStyle curveStyle() const;

    void setCurveAttribute(CurveAttribute attr, bool on = true);
    bool testCurveAttribute(CurveAttribute attr) const;

    void setLegendAttribute(LegendAttribute attr, bool on = true);
    bool testLegendAttribute(LegendAttribute attr) const;

    void setPaintAttribute(PaintAttribute attr, bool on = true);
    bool tesPaintAttribute(PaintAttribute attr) const;

    virtual QPen pen() const;
    virtual void setPen(const QPen &pen);
    virtual QBrush brush() const;
    virtual void setBrush(const QBrush &brush);

    virtual QString title() const;
    virtual void setTitle(const QString &text);

    void setSymbol(SymbolStyle style, const QBrush &brush, const QPen &pen, const QSize &size);
    void setSymbolBrush(const QBrush &brush);
    void setSymbolPen(const QPen &pen);
    void setSymbolSize(const QSize &size);

    virtual void attach(Chart *chart);
    virtual void detach();

    Chart *chart() const;
    QwtPlotCurve *curve() const;

    const JSeriesData *seriesData() const;
    void setSeriesData(JSeriesData *seriesData);

    bool isVisible() const;
    void setVisible(bool visible);

    virtual const QVector<QPointF> &samples() const;
    virtual void setSamples(const QVector<QPointF> &data, bool update = true);
    virtual void appendSample(const QPointF &point, bool update = true);
    virtual void shiftSample(const QPointF &point, bool update = true);
    void update();

    QObjectUserData *userData() const;
    void setUserData(QObjectUserData *data);

    int closestPointX(qreal x) const;
    int closestPointY(qreal y) const;
    QPoint closestPoint(const QPointF &point) const;
    QRectF visualBoundingRect(int indexMin = -1, int indexMax = -1) const;

private:
    Q_DISABLE_COPY(AbstractSeries)
    J_DECLARE_PRIVATE(AbstractSeries)
};

} // end of namespace JChart

#endif // JABSTRACTSERIES_H
