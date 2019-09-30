#ifndef PROTOCORE_WORKER_SEND_H
#define PROTOCORE_WORKER_SEND_H

#include "worker.h"

namespace J {

class WorkerSend;
typedef std::shared_ptr<WorkerSend> WorkerSendPtr;

class WorkerSendData;

class PROTOCORE_EXPORT WorkerSend : public WorkerTrans
{
public:
    typedef std::function<void()> ClosedEvent;
    typedef std::function<void()> StartedEvent;
    typedef std::function<void()> StoppedEvent;
    typedef std::function<void(bool)> ToggledEvent;
    typedef std::function<void(TimeEvent)> TimeEventChangedEvent;

    WorkerSend();
    ~WorkerSend() J_OVERRIDE;

    ChannelPtr channel() const override;
    void setChannel(const ChannelPtr &channel) override;

    TablePtr table() const override;
    void setTable(const TablePtr &table) override;

    int interval() const override;
    void setInterval(int value) override;

    TimeEvent timeEvent() const override;
    void setTimeEvent(TimeEvent value) override;

    bool isRunning() const override;
    bool start() override;
    void stop() override;

    bool counterLoop() const;
    void setCounterLoop(bool loop);

    bool frameLoop() const;
    void setFrameLoop(bool loop);

    bool sendOnce(bool counterLoop = false, bool frameLoop = false);
    bool sendOnce(const char *data, int size);

    void setClosedEvent(ClosedEvent event, void *owner);
    void setStartedEvent(StartedEvent event, void *owner);
    void setStoppedEvent(StoppedEvent event, void *owner);
    void setToggledEvent(ToggledEvent event, void *owner);
    void setTimeEventChangedEvent(TimeEventChangedEvent event, void *owner);
    void removeEventOwner(void *owner);

private:
    J_DISABLE_COPY(WorkerSend)
    WorkerSendData *d;
};

} // end of namespace J

#endif // PROTOCORE_WORKER_SEND_H
