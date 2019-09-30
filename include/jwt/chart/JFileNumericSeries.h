#ifndef JFILENUMERICSERIES_H
#define JFILENUMERICSERIES_H

#include "../global.h"
#include "JNumericSeries.h"
#include <QFile>

namespace JChart {

class FileNumericSeriesPrivate;

class JWT_EXPORT FileNumericSeries : public NumericSeries
{
public:
    explicit FileNumericSeries(const QString &title = QString());
    virtual ~FileNumericSeries() J_OVERRIDE;

    void setBuffer(const uchar *buffer, size_t bufferSize, int bufferStep, bool update = true);
    void setAttributes(uchar xSize, uchar ySize, int xOffset, int yOffset,
                       qreal valueScale, qreal valueOffset, int numericTypeY,
                       int bitStart = 0, int bitCount = -1, bool update = true);

    qreal xMinimum() const;
    qreal xMaximum() const;
    qreal yMinimum() const;
    qreal yMaximum() const;

private:
    Q_DISABLE_COPY(FileNumericSeries)
    J_DECLARE_PRIVATE(FileNumericSeries)
};

} // end of namespace JChart

#endif // JFILENUMERICSERIES_H
