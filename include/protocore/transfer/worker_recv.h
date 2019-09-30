#ifndef PROTOCORE_WORKER_RECV_H
#define PROTOCORE_WORKER_RECV_H

#include "worker.h"
#include <functional>

namespace J {

class Runnable;

class Worker;
typedef std::shared_ptr<Worker> WorkerPtr;

class WorkerRecv;
typedef std::shared_ptr<WorkerRecv> WorkerRecvPtr;

class WorkerRecvData;

class PROTOCORE_EXPORT WorkerRecv : public WorkerTrans
{
public:
    typedef std::function<void()> ClosedEvent;
    typedef std::function<void()> StartedEvent;
    typedef std::function<void()> StoppedEvent;
    typedef std::function<void(bool)> ToggledEvent;

    WorkerRecv();
    ~WorkerRecv() J_OVERRIDE;

    ChannelPtr channel() const override;
    void setChannel(const ChannelPtr &channel) override;

    TablePtr table() const override;
    void setTable(const TablePtr &table) override;

    WorkerPtr relayer() const;
    void setRelayer(const WorkerPtr &relayer);

    int interval() const override;
    void setInterval(int value) override;

    TimeEvent timeEvent() const override;
    void setTimeEvent(TimeEvent value) override;

    bool isRunning() const override;
    bool start() override;
    void stop() override;

    Runnable *runnable();
    void setRunnable(Runnable *runnable);

    int queueCount() const;
    void setQueueCount(int count);

    bool isRecording() const;
    bool startRecord();
    void stopRecord();

    bool isUpdated() const;
    bool takeUpdated();
    void setUpdated(bool updated);

    void setClosedEvent(ClosedEvent event, void *owner);
    void setStartedEvent(StartedEvent event, void *owner);
    void setStoppedEvent(StoppedEvent event, void *owner);
    void setToggledEvent(ToggledEvent event, void *owner);
    void removeEventOwner(void *owner);

private:
    J_DISABLE_COPY(WorkerRecv)
    WorkerRecvData *d;
};

} // end of namespace J

#endif // J::WORKER_RECV_H
