#ifndef PROTOCORE_WORKER_H
#define PROTOCORE_WORKER_H

#include "../global.h"
#include "../core/table.h"
#include "channel.h"
#include <functional>

namespace J {

// class WorkerTrans

class WorkerTrans;
typedef std::shared_ptr<WorkerTrans> WorkerTransPtr;

class PROTOCORE_EXPORT WorkerTrans
{
public:
    enum TimeEvent {
        TimeOneShot,
        TimePeriodic
    };

    inline WorkerTrans() {}
    inline virtual ~WorkerTrans() {}

    virtual ChannelPtr channel() const = 0;
    virtual void setChannel(const ChannelPtr &channel) = 0;

    virtual TablePtr table() const = 0;
    virtual void setTable(const TablePtr &table) = 0;

    virtual int interval() const = 0;
    virtual void setInterval(int value) = 0;

    virtual TimeEvent timeEvent() const = 0;
    virtual void setTimeEvent(TimeEvent value) = 0;

    virtual bool isRunning() const = 0;
    virtual bool start() = 0;
    virtual void stop() = 0;

    inline WorkerTrans(const WorkerTrans &other) { (void)other; }
    inline WorkerTrans &operator =(const WorkerTrans &other)
    { (void)other; return *this; }
};

// class Worker

class WorkerSend;
typedef std::shared_ptr<WorkerSend> WorkerSendPtr;

class WorkerRecv;
typedef std::shared_ptr<WorkerRecv> WorkerRecvPtr;

class Worker;
typedef std::shared_ptr<Worker> WorkerPtr;
typedef std::vector<WorkerPtr> WorkerPtrArray;

class WorkerData;

class PROTOCORE_EXPORT Worker
{
public:
    typedef std::function<void()> OpenedEvent;
    typedef std::function<void()> ClosedEvent;
    typedef std::function<void(bool)> ToggledEvent;
    typedef std::function<void()> ChannelConfigChangedEvent;

    enum WorkerType {
        WorkerTypeSend,
        WorkerTypeRecv
    };
    Worker();
    explicit Worker(const ChannelPtr &channel);
    explicit Worker(const ChannelPtr &channel, const TablePtr &tableSend,
                    const TablePtr &tableRecv);
    virtual ~Worker();

    ChannelPtr channel() const;
    void setChannel(const ChannelPtr &channel);

    TablePtr tableSend() const;
    TablePtr tableRecv() const;

    WorkerPtr relayer() const;
    void setRelayer(const WorkerPtr &relayer);

    std::weak_ptr<WorkerSend> sender() const;
    std::weak_ptr<WorkerRecv> receiver() const;

    bool isOpen() const;
    bool open();
    void close();

    void setOpenedEvent(OpenedEvent event, void *owner);
    void setClosedEvent(ClosedEvent event, void *owner);
    void setToggledEvent(ToggledEvent event, void *owner);
    void setChannelConfigChangedEvent(ChannelConfigChangedEvent event, void *owner);
    void removeEventOwner(void *owner);

    void triggleChannelConfigChanged();

    static WorkerPtr create(const ChannelPtr &channel, const TablePtr &tableSend,
                            const TablePtr &tableRecv);
    static WorkerPtr create(const ChannelPtr &channel, const Json::Value &config);
    static WorkerPtr create(const Json::Value &config, const TablePtr &tableSend,
                            const TablePtr &tableRecv);
    static WorkerPtr create(const Json::Value &config);

private:
    J_DISABLE_COPY(Worker)
    WorkerData *d;
};

} // end of namespace J

#endif // PROTOCORE_WORKER_H
