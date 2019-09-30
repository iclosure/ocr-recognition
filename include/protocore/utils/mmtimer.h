#ifndef PROTOCORE_MMTIMER_H
#define PROTOCORE_MMTIMER_H

#include "../global.h"
#include <memory>

namespace J {

// class Runnable

#ifndef J_RUNNABLE_INTERFACE
#define J_RUNNABLE_INTERFACE

// class Runnable

class Runnable;
typedef std::shared_ptr<Runnable> RunnablePtr;

class PROTOCORE_EXPORT Runnable
{
public:
    virtual ~Runnable();
    virtual void run() = 0;
};

#endif  // J_RUNNABLE_INTERFACE

// class MMTimer

class MMTimer;
typedef std::shared_ptr<MMTimer> MMTimerPtr;

class MMTimerData;

class PROTOCORE_EXPORT MMTimer
{
public:
    enum TimeEvent {
        TimeOneShot,
        TimePeriodic
    };

    explicit MMTimer();
    explicit MMTimer(int timeEvent, int interval = -1);
    ~MMTimer();

    bool isRunning() const;
    bool start();
    void stop();

    unsigned int accuracy() const;
    void setAccuracy(unsigned int value);

    unsigned int interval() const;
    void setInterval(unsigned int msecs);

    int timeEvent() const;
    void setTimeEvent(int value);

    Runnable *task() const;
    void setTask(Runnable *task);

private:
    MMTimer(const MMTimer &);
    MMTimer &operator=(const MMTimer &);
    MMTimerData *d;
};

} // end of namespace J

#endif // PROTOCORE_MMTIMER_H
