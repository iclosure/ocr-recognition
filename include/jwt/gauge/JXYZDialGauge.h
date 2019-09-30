#ifndef JXYZDIALGAUGE_H
#define JXYZDIALGAUGE_H

#include "../global.h"
#include "JGridDialGauge.h"

// class JXYZDialGauge

class JXYZDialGaugePrivate;

class JWT_EXPORT JXYZDialGauge : public JGridDialGauge
{
    Q_OBJECT
public:
    explicit JXYZDialGauge(QWidget *parent = nullptr);
    explicit JXYZDialGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JXYZDialGauge() J_OVERRIDE;

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JXYZDialGauge)
    J_DECLARE_PRIVATE(JXYZDialGauge)
};

#endif  // JXYZDIALGAUGE_H
