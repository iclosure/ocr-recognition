#include "ExcelMgr.h"
#include <QAxObject>
#include <QCoreApplication>
#include <QDebug>

//
typedef struct __GroupInfo {
    QString name;
    int row;
    int count;
} GroupInfo;

// class ExcelMgrPrivate

class ExcelMgrPrivate
{
public:
    ExcelMgrPrivate(ExcelMgr *q)
        : q_ptr_(q)
        , excel(nullptr)
        , workBook(nullptr)
        , workSheet(nullptr)
        , rowCount(0)
        , columnCount(0)
        , startRow(0)
        , startColumn(0)
        , rangeColumn(nullptr)
    {

    }

    ~ExcelMgrPrivate()
    {
        releaseExcel();
    }

    void init();
    bool isExcelInited() const;
    bool initExcel();
    void releaseExcel();

private:
    J_DECLARE_PUBLIC(ExcelMgr)
    QString templateType;
    QString filePath;
    QAxObject *excel;
    QAxObject* workBook;
    QAxObject * workSheet;
    int rowCount;
    int columnCount;
    int startRow;
    int startColumn;
    QAxObject *rangeColumn;
    QList<GroupInfo> groupsInfo;
};

void ExcelMgrPrivate::init()
{
    if (!initExcel()) {
        releaseExcel();
    }
}

bool ExcelMgrPrivate::isExcelInited() const
{
    return (excel != nullptr && workSheet != nullptr && rangeColumn != nullptr);
}

bool ExcelMgrPrivate::initExcel()
{
    Q_Q(ExcelMgr);

    releaseExcel();

    //
    templateType = QString::fromStdString(JMain::instance()->config(
                                              QLatin1String("ocr.template.type")).asString());
    if (templateType != QLatin1String("excel")) {
        return false;
    }
    //
    filePath = QString::fromStdString(JMain::instance()->config(
                                          QLatin1String("ocr.template.filePath")).asString());
    if (filePath.isEmpty()) {
        return false;
    }

    excel = new QAxObject(q);
    if (excel->setControl(QLatin1String("Excel.Application"))) {
        //
    } else if (excel->setControl(QLatin1String("ket.Application"))) {
        //
    } else {
        return false;
    }

    excel->setProperty("Visible", false);
    QAxObject* workBooks = excel->querySubObject("WorkBooks");
    workBook = workBooks->querySubObject("Open(const QString&)", filePath);
    if (!workBook) {
        return false;
    }

    QAxObject * workSheets = workBook->querySubObject("WorkSheets");
    int workSheetCount = workSheets->property("Count").toInt();
    if (workSheetCount < 1) {
        return false;
    }

    workSheet = workSheets->querySubObject("Item(int)", 1);
    if (!workSheet) {
        return false;
    }

    QAxObject * usedRange = workSheet->querySubObject("UsedRange");
    if (!usedRange) {
        return false;
    }

    QAxObject * rows = usedRange->querySubObject("Rows");
    QAxObject * columns = usedRange->querySubObject("Columns");
    rowCount = rows->property("Count").toInt();
    columnCount = columns->property("Count").toInt();
    startRow = rows->property("Row").toInt();
    startColumn = columns->property("Column").toInt();

    const QString rangeText = QStringLiteral("F%1:F%2").arg(startRow + 1).arg(rowCount);
    rangeColumn = workSheet->querySubObject("Range(QString)", rangeText);
    if (!rangeColumn) {
        return false;
    }
#if 0
    const QVariantList rangesValue = rangeColumn->property("Value").toList();
    if (rangesValue.isEmpty()) {
        return false;
    }

    int row = 0, count = 0;
    QString groupName;

    for (int i = 0; i < rangesValue.size(); ++i) {
        const QVariant &varRangeValue = rangesValue[i];
        if (varRangeValue.type() != QVariant::List) {
            return false;
        }
        const QVariantList rangeValue = varRangeValue.toList();
        if (rangeValue.isEmpty()) {
            return false;
        }
        const QVariant &firstValue = rangeValue.at(0);
        if (firstValue.isValid()) {
            const QString name = firstValue.toString().trimmed();
            if (!groupName.isEmpty() && row > 0 && count > 0) {
                groupsInfo.append({groupName, row, count});
                groupName = name;
            } else {
                groupName = name;
                if (groupName.isEmpty()) {
                    row = 0;
                    count = 0;
                    continue;
                }
            }
            row = startRow + 1 + i;
            count = 1;
        } else if (!groupName.isEmpty() && row > 0) {
            ++count;
        }
    }

    if (!groupName.isEmpty() && row > 0 && count > 0) {
        groupsInfo.append({groupName, row, count});
    }
#else
    for (int row = startRow + 1; row < startRow + rowCount; ++row) {
        QAxObject *range = workSheet->querySubObject("Cells(int,int)", row, 6);
        const QString name = range->property("Value").toString();
        if (name.isEmpty()) {
            continue;
        }
        bool bMerger = range->property("MergeCells").toBool();
        if (bMerger) {
            QAxObject *mergeArea =  range->querySubObject("MergeArea");
            int mergeRowStart = mergeArea->property("Row").toInt();
            if (mergeRowStart != row) {
                return false;
            }
            int mergeRowCount = mergeArea->querySubObject("Rows")->property("Count").toInt();
            if (mergeRowCount <= 0) {
                return false;
            }
            //
            groupsInfo.append({name, row, mergeRowCount});
            //
            row = mergeRowStart + mergeRowCount - 1;
        } else {
            groupsInfo.append({name, row, 1});
        }
    }
#endif
    //TEST
#if 0
    for (int i = 0; i < groupsInfo.size(); ++i) {
        qWarning().noquote() << i << groupsInfo[i].name
                             << groupsInfo[i].row << groupsInfo[i].count;
    }
#endif
    return true;
}

void ExcelMgrPrivate::releaseExcel()
{
    templateType.clear();
    filePath.clear();
    groupsInfo.clear();
    rowCount = 0;
    columnCount = 0;
    startRow = 0;
    startColumn = 0;
    rangeColumn = nullptr;
    workSheet = nullptr;

    if (workBook) {
        workBook->dynamicCall("Save()");
        workBook->dynamicCall("Close()");
        workBook = nullptr;
    }

    if (excel) {
        excel->dynamicCall("Quit()");
        delete excel;
        excel = nullptr;
    }
}

// class ExcelMgr

J_IMPLEMENT_SINGLE_INSTANCE(ExcelMgr, JMain)

bool ExcelMgr::init()
{
    Q_D(ExcelMgr);
    if (!d->isExcelInited()) {
        return false;
    }

    return true;
}

void ExcelMgr::parseGroups(const QString &text, QMap<QString, QStringList> &groups)
{
    groups.clear();

    if (text.isEmpty()) {
        return;
    }

    QString key;
    const QStringList sections = text.split(QLatin1String("\n"));
    for (int i = 0; i < sections.size(); ++i) {
        const QString section = sections[i].trimmed();
        if (section.startsWith(QLatin1String("------"))) {
            continue;
        }
        if (key.isEmpty()) {
            if (section.startsWith(QLatin1String("BM"))) {
                key = section;
            } else {
                ++i;
            }
        } else if (section.isEmpty()) {
            key.clear();
            continue;
        } else {
            auto citerGroup = groups.find(key);
            if (citerGroup != groups.cend()) {
                citerGroup.value().append(section);
            } else {
                groups.insert(key, QStringList() << section);
            }
            key.clear();
        }
    }
}

bool ExcelMgr::saveGroups(const QMap<QString, QStringList> &groups, int rowOffset)
{
    if (groups.isEmpty()) {
        return true;
    }

    Q_D(ExcelMgr);
    if (!d->isExcelInited()) {
        return false;
    }

    for (auto citerGroups = groups.cbegin();
         citerGroups != groups.cend(); ++ citerGroups) {
        const QString &groupName = citerGroups.key();
        const QStringList &items = citerGroups.value();
        //
        for (auto citerGroupsInfo = d->groupsInfo.cbegin();
             citerGroupsInfo != d->groupsInfo.cend(); ++citerGroupsInfo) {
            const GroupInfo &groupInfo = *citerGroupsInfo;
            if (groupInfo.name == groupName) {
                if (rowOffset < 0) {
                    rowOffset = 0;
                } else if (groupInfo.count == 1) {
                    rowOffset = 0;
                }
                for (int row = rowOffset; row < groupInfo.count && row < items.count(); ++row) {
                    const int rowIndex = groupInfo.row + row;
                    QAxObject *range = d->workSheet->querySubObject("Cells(int,int)", rowIndex, 7);
                    if (!range) {
                        continue;
                    }
                    range->setProperty("Value", items.at(row));
                }
                break;
            }
        }
    }

    d->workBook->dynamicCall("Save()");

    return true;
}

ExcelMgr::ExcelMgr(QObject *parent)
    : QObject(parent)
    , d_ptr_(new ExcelMgrPrivate(this))
{
    Q_D(ExcelMgr);
    d->init();
}

ExcelMgr::~ExcelMgr()
{
    Q_D(ExcelMgr);
    delete d;
}
