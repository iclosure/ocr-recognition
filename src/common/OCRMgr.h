#ifndef OCRMGR_H
#define OCRMGR_H

#include "global.h"

class OCRMgrPrivate;

class OCRMgr : public QObject
{
    Q_OBJECT
public:
    bool init();

    QStringList test(const QString &filePath, const QSize &size,
                     QPixmap *pmSource = nullptr, QPixmap *pmBinary = nullptr);

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
