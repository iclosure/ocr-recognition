#ifndef JNUMERICSERIES_H
#define JNUMERICSERIES_H

#include "../global.h"
#include "JAbstractSeries.h"

namespace JChart {

class NumericSeriesPrivate;
class JNumericChart;

class JWT_EXPORT NumericSeries : public AbstractSeries
{
public:
    explicit NumericSeries(const QString &title = QString());
    virtual ~NumericSeries() J_OVERRIDE;

    void setBrush(const QBrush &brush) override;
    void setPen(const QPen &pen) override;

private:
    Q_DISABLE_COPY(NumericSeries)
    J_DECLARE_PRIVATE(NumericSeries)
};

} // end of namespace JChart

#endif // JNUMERICSERIES_H
