#ifndef JTEMPCHART_H
#define JTEMPCHART_H

#include "../global.h"
#include "JChartBar.h"

// class JTempChart

class JTempChartPrivate;

class JWT_EXPORT JTempChart : public JChartBar
{
    Q_OBJECT
public:
    explicit JTempChart(QWidget *parent = nullptr);
    explicit JTempChart(const QString &title, QWidget *parent = nullptr);
    virtual ~JTempChart() J_OVERRIDE;

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JTempChart)
    J_DECLARE_PRIVATE(JTempChart)
};

#endif  // JTEMPCHART_H
