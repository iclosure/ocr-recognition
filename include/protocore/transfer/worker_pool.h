#ifndef PROTOCORE_WORKER_POOL_H
#define PROTOCORE_WORKER_POOL_H

#include "worker.h"

namespace J {

class Channel;
typedef std::shared_ptr<Channel> ChannelPtr;

class WorkerPool;
typedef std::shared_ptr<WorkerPool> WorkerPoolPtr;

class WorkerPoolData;

class PROTOCORE_EXPORT WorkerPool : public Json::Serializable
{
public:
    typedef std::function<void(const WorkerPtr &)> WorkerAddedEvent;
    typedef std::function<void(const WorkerPtr &)> WorkerRemovedEvent;
    typedef std::function<void()> WorkerClearedEvent;
    typedef std::function<void()> UpdatedEvent;

    static WorkerPoolPtr instance();
    static void releaseInstance();

    WorkerPtrArray allWorkers();
    const WorkerPtrArray &allWorkers() const;
    void appendWorker(const WorkerPtr &worker);
    void insertWorker(int index, const WorkerPtr &worker);
    void removeWorker(const WorkerPtr &worker);
    void removeWorker(const ChannelPtr &channel);
    void removeWorker(int index);
    void removeWorkerByType(int channelType);
    void clearWorker();
    WorkerPtr workerAt(int index);
    WorkerPtr workerByChannel(const ChannelPtr &channel) const;
    WorkerPtr workerByChannelIdentity(const std::string &identity) const;
    WorkerPtr workerByChannelName(const std::string &name) const;
    void moveWorker(int sourceIndex, int targetIndex, int channelType = ChannelInvalid);

    std::string filePath() const;
    void setFilePath(const std::string &filePath);
    bool loadConfig();
    bool loadConfig(const std::string &filePath);
    bool saveConfig();
    bool saveConfig(const std::string &filePath);

    void stop();

    void setWorkerAddedEvent(WorkerAddedEvent event, void *owner);
    void setWorkerRemovedEvent(WorkerRemovedEvent event, void *owner);
    void setWorkerClearedEvent(WorkerClearedEvent event, void *owner);
    void setUpdatedEvent(UpdatedEvent event, void *owner);
    void removeEventOwner(void *owner);

    // Serializable interface
public:
    Json::Value save() const override;
    bool restore(const Json::Value &json, int /*deep*/ = -1) override;

public:
    WorkerPool();
    ~WorkerPool() J_OVERRIDE;

private:
    J_DISABLE_COPY(WorkerPool)
    WorkerPoolData *d;
};

} // end of namespace J

#endif // PROTOCORE_WORKER_POOL_H
