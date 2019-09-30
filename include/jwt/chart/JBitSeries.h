#ifndef JBITSERIES_H
#define JBITSERIES_H

#include "../global.h"
#include "JAbstractSeries.h"

namespace JChart {

class BitSeriesPrivate;
class JBitChart;

class JWT_EXPORT BitSeries : public AbstractSeries
{
public:
    explicit BitSeries(int index, int yOffset, int maskOffset, QRectF &boundingRect,
                       const QString &title = QString(), QVector<QPointF> *data = nullptr);
    virtual ~BitSeries() J_OVERRIDE;

    int index() const;
    int yOffset() const;
    int maskOffset() const;

    void attach(Chart *chart) override;
    void detach() override;

    QString title() const override;
    void setTitle(const QString &text) override;

    void setBuffer(const uchar *buffer, size_t bufferSize, int bufferStep, bool update = true);
    void setAttributes(uchar xSize, uchar ySize, int xOffset, int yOffset, bool update = true);

private:
    Q_DISABLE_COPY(BitSeries)
    J_DECLARE_PRIVATE(BitSeries)
};

} // end of namespace JChart

#endif // JBITSERIES_H
