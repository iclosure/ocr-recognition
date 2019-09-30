#ifndef JGROUPCHANNELPANE_H
#define JGROUPCHANNELPANE_H

#include "global.h"
#include "jwt/style/JShadowDialog.h"
#include "JChannelPane.h"

class QTabWidget;

namespace J {

class Worker;
typedef std::shared_ptr<Worker> WorkerPtr;

// class JGroupChannelPane

class JGroupChannelPanePrivate;

class PROTOWIDGET_EXPORT JGroupChannelPane : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentTab READ currentTab WRITE setCurrentTab NOTIFY currentTabChanged)
    Q_PROPERTY(int currentRow READ currentRow WRITE setCurrentRow NOTIFY currentRowChanged)
public:
    explicit JGroupChannelPane(QWidget *parent = nullptr);
    explicit JGroupChannelPane(JChannelPane::OperateAttribute operateAttrs,
                               JChannelPane::ShowAttributes showAttrs,
                               QWidget *parent = nullptr);
    virtual ~JGroupChannelPane() J_OVERRIDE;

    WorkerPtr selectedWorker() const;
    int currentTab() const;
    int currentRow() const;
    int rowCount() const;
    int rowCount(int tab) const;
    int currentType() const;

    void addWorker(const WorkerPtr &worker);

    QTabWidget *tabWidget() const;

    static QString iconFromType(const QString &type);

Q_SIGNALS:
    void currentTabChanged(int index);
    void currentRowChanged(int index);

    void accepted();
    void rejected();

public Q_SLOTS:
    void setCurrentTab(int index);
    void setCurrentRow(int index);

    void updateAllTab();
    void updateCurrentTab();

private:
    Q_DISABLE_COPY(JGroupChannelPane)
    J_DECLARE_PRIVATE(JGroupChannelPane)
};

// class JGroupChannelDlg

class PROTOWIDGET_EXPORT JGroupChannelDlg : public JShadowDialog
{
    Q_OBJECT
public:
    explicit JGroupChannelDlg(QWidget *parent = nullptr);
    explicit JGroupChannelDlg(JChannelPane::OperateAttribute operateAttrs,
                              JChannelPane::ShowAttributes showAttrs,
                              QWidget *parent = nullptr);

    WorkerPtr selectedWorker() const;

    JGroupChannelPane *pane() const;

Q_SIGNALS:

public Q_SLOTS:

private:
    void init();

private:
    JGroupChannelPane *pane_;
};

} // end of namespace J

#endif // JGROUPCHANNELPANE_H
