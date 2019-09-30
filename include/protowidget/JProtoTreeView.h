#ifndef JPROTOTREEVIEW_H
#define JPROTOTREEVIEW_H

#include <QWidget>
#include "global.h"

class QStandardItem;
class JTreeView;

namespace J {

//
enum OptionType {
    // base
    OptionName,
    OptionMark,
    OptionDesc,
    //
};

class Object;
typedef std::shared_ptr<Object> ObjectPtr;
class Root;
typedef std::shared_ptr<Root> RootPtr;
class Table;
typedef std::shared_ptr<Table> TablePtr;

class Parser;
typedef std::shared_ptr<Parser> ParserPtr;

class JSearchEdit;

// class JProtoTreeView

class JProtoTreeViewPrivate;

class PROTOWIDGET_EXPORT JProtoTreeView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged)
public:
    enum BindTableType {
        BindOnlySend = 0x01,
        BindOnlyRecv = 0x02,
        BindAllTable = BindOnlySend | BindOnlyRecv
    };
    Q_DECLARE_FLAGS(BindTableTypes, BindTableType)

    enum TreeMode {
        TreeModeNone = 0x0000,          /**< . */
        TreeModeEdit = 0x0001,          /**< . */
        TreeModeMonitor = 0x0002,       /**< . */
        TreeModeSimulator = 0x0004,     /**< . */
        TreeModeAnalyse = 0x0008,       /**< . */
        TreeModeTableSel = 0x0010,      /**< . */
        TreeModeJustShow = 0x0020       /**< . */
    };
    Q_DECLARE_FLAGS(TreeModes, TreeMode)

    enum ShowAttribute {
        ShowNone = 0x0000,      /**< . */
        ShowOffset = 0x0001,    /**< . */
        ShowType = 0x0002,      /**< . */
        ShowData = 0x0004,      /**< . */
        ShowValue = 0x0008,     /**< . */
        ShowSpec = 0x0010,      /**< . */
        ShowPrivate = 0x0020,   /**< . */
        ShowAll = 0x001f
    };
    Q_DECLARE_FLAGS(ShowAttributes, ShowAttribute)

    explicit JProtoTreeView(QWidget *parent = nullptr);
    virtual ~JProtoTreeView() J_OVERRIDE;

    JSearchEdit *searchEdit() const;

    BindTableTypes bindTableType() const;
    void setBindTableType(BindTableTypes value);

    ShowAttributes showAttributes() const;
    void setShowAttributes(int attrs);
    void setShowAttribute(ShowAttribute attr, bool on = true);
    bool testShowAttribute(ShowAttribute attr) const;

    int dataFormat() const;

    TreeModes treeModes() const;
    void setTreeMode(TreeModes modes);
    void setTreeMode(TreeMode mode, bool on = true);
    bool testTreeMode(TreeMode mode) const;

    ParserPtr parser() const;
    void setParser(const ParserPtr &parser);

    int loadingDeep() const;
    void setLoadingDeep(int deep);

    int intervalUpdate() const;
    void setIntervalUpdate(int interval);

    void toggleUpdate(bool enabled);

    void clearContents();
    bool loadData();
    bool loadData(const TablePtr &table, const QString &domain = QString(), bool binding = false);
    bool loadData(const TablePtr &table, const QString &filePath,
                  bool hasTimeFormat, int headerSize, const QString &domain = QString());

    QStandardItem *rootItem() const;
    QStandardItem *currentItem() const;

    bool isRunning() const;

    void bindingChannels(const QString &filePath);
    void unbindingChannels();

    void exportBindingStatus(const QString &filePath);

    void runAllChannels();
    void stopAllChannels();

    QStandardItem *findItemTable(QStandardItem *item) const;
    void selectItem(const QString &domain, int domainType);

    QString itemDomain(QStandardItem *item, int domainType) const;
    static QString idDomain(QStandardItem *item);
    static QString markDomain(QStandardItem *item);

    static bool loadTable(JTreeView *treeView, QStandardItem *itemParent, const TablePtr &table);

    RootPtr protoRoot() const;
    void setProtoRoot(const RootPtr &root);
    TablePtr newTable() const;

    bool isItemLoaded(QStandardItem *item) const;
    bool hasUnloadedItem() const;
    QStandardItem *unloadedItem() const;

    ObjectPtr findObject(QStandardItem *item, bool ignoreComplex = true) const;
    ObjectPtr findObject(const QString &domain, int domainType, bool ignoreComplex = true) const;

    // for edit module {{{

    void insertRow(int row, const ObjectPtr &target, const QVariant &data = QVariant());
    void updateRow(int sourceRow, int targetRow, const ObjectPtr &target, const QVariant &data = QVariant());
    void removeRow(int row, const ObjectPtr &target, const QVariant &data = QVariant());
    void removeRows(QStandardItem *parentItem, const QList<int> &rows);
    void removeRows(QStandardItem *parentItem, int beginRow, int endRow);
    void clearItem(QStandardItem *parentItem);

    void applyInsert(const ObjectPtr &target);
    void cancelInsert();

    // }}}

Q_SIGNALS:
    void itemPressed(QStandardItem *item);
    void itemClicked(QStandardItem *item);
    void itemDoubleClicked(QStandardItem *item);
    void currentItemChanged(QStandardItem *current, QStandardItem *previous);
    void itemUnloaded(QStandardItem *item, QStandardItem *itemTable);
    void channelBound(QStandardItem *item, const QString &channelId);
    void channelUnbound(QStandardItem *item, const QString &channelId);
    void channelChanged(QStandardItem *item, const QString &channelId);
    void unbindItem(QStandardItem *item, QStandardItem *itemTable);
    void settingAxisTriggled();
    void runningChanged(bool value);
    void exportAnalyseData(QStandardItem *item, const QString &filePath,
                           bool hasTimeFormat, int headerSize);

    // {{ for editor
    void requestAdd(QStandardItem *item, const QVariant &data = QVariant());
    void itemUpdated(QStandardItem *item, bool unloaded, bool removed);
    void canceledInsert(QStandardItem *item);
    // }}

    // {{ for monitor and analyse
    void requestFreqView(QStandardItem *itemTable, QStandardItem *item);
    // }}

public Q_SLOTS:
    void setRunning(bool value);
    void setDataFormat(int format);

private:
    Q_DISABLE_COPY(JProtoTreeView)
    J_DECLARE_PRIVATE(JProtoTreeView)
};

} // end of namespace J

#endif // JPROTOTREEVIEW_H
