#ifndef JCHANNELPANE_H
#define JCHANNELPANE_H

#include <QWidget>
#include "global.h"

namespace J {

class Worker;
typedef std::shared_ptr<Worker> WorkerPtr;

// class JChannelPane

class JChannelPanePrivate;

class PROTOWIDGET_EXPORT JChannelPane : public QWidget
{
    Q_OBJECT
public:
    enum OperateAttribute {
        NoOperate = 0x00,
        OperateOpen = 0x01,
        OperateSwitchRecv = 0x02,
        OperateRemove = 0x04,
        OperateIndicator = 0x08,
        OperateMove = 0x10,
        AllOperate = 0x1f
    };
    Q_DECLARE_FLAGS(OperateAttributes, OperateAttribute)

    enum ShowAttribute {
        NoShow = 0x00,
        ShowIdleSender = 0x01,
        ShowIdleReceiver = 0x02,
        ShowAllIdle = ShowIdleSender | ShowIdleReceiver,
        ShowNonIdleChannel = 0x04,
        ShowAllChannel = ShowAllIdle | ShowNonIdleChannel
    };
    Q_DECLARE_FLAGS(ShowAttributes, ShowAttribute)

    explicit JChannelPane(QWidget *parent = nullptr);
    ~JChannelPane() J_OVERRIDE;

    WorkerPtr selectedWorker() const;

    int rowCount() const;
    int currentRow() const;
    void setCurrentRow(int row);

    void addWorker(const WorkerPtr &worker, OperateAttributes attrs);
    void insertWorker(int row, const WorkerPtr &worker, OperateAttributes attrs);
    void removeWorker(const WorkerPtr &worker);
    void removeWorker(const QString &channelId);
    void clearWorker();

    void setTableEnabled(bool enabled);
    void setEditEnabled(bool enabled);

Q_SIGNALS:
    void currentRowChanged(int currentRow, int previousRow);
    void rowDoubleClicked(int row);

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JChannelPane)
    J_DECLARE_PRIVATE(JChannelPane)
};

} // end of namespace J

#endif // JCHANNELPANE_H
