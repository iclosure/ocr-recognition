#ifndef EXCELMGR_H
#define EXCELMGR_H

#include <QObject>
#include "global.h"

class ExcelMgrPrivate;

class ExcelMgr : public QObject
{
    Q_OBJECT
public:
    bool init();

    static void parseGroups(const QString &text, QMap<QString, QStringList> &groups);
    bool saveGroups(const QMap<QString, QStringList> &groups, int rowOffset = -1);

Q_SIGNALS:

public Q_SLOTS:

private:
    explicit ExcelMgr(QObject *parent = nullptr);
    ~ExcelMgr() J_OVERRIDE;

private:
    Q_DISABLE_COPY(ExcelMgr)
    J_DECLARE_PRIVATE(ExcelMgr)
    J_DECLARE_SINGLE_INSTANCE(ExcelMgr)
};

#endif  // EXCELMGR_H
