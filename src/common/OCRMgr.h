#ifndef OCRMGR_H
#define OCRMGR_H

#include "global.h"

class OCRMgrPrivate;

class OCRMgr : public QObject
{
    Q_OBJECT
public:
    bool init();

    QString test(const QString &filePath);

signals:

public slots:

private:
    explicit OCRMgr(QObject *parent = nullptr);
    ~OCRMgr() J_OVERRIDE;

private:
    Q_DISABLE_COPY(OCRMgr)
    J_DECLARE_PRIVATE(OCRMgr)
    J_DECLARE_SINGLE_INSTANCE(OCRMgr)
};

#endif // LOGGING_H
