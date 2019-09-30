#ifndef PROTOCORE_THREAD_H
#define PROTOCORE_THREAD_H

#include "../global.h"
#include <limits.h>

namespace J {

// class Runnable

#ifndef J_RUNNABLE_INTERFACE
#define J_RUNNABLE_INTERFACE

class Runnable;
typedef std::shared_ptr<Runnable> RunnablePtr;

class Runnable
{
public:
    virtual ~Runnable() {}
    virtual void run() = 0;
};

#endif  // J_RUNNABLE_INTERFACE

// class Thread

class ThreadData;

class PROTOCORE_EXPORT Thread
{
public:
    explicit Thread();
    ~Thread();

    bool isRunning() const;
    bool start();
    void stop();

    bool wait(unsigned long msecs = ULONG_MAX);

    Runnable *runnable() const;
    void setRunnable(Runnable *runnable);

    static void sleep(unsigned long secs);
    static void msleep(unsigned long msecs);
    static void usleep(unsigned long usecs);

private:
    J_DISABLE_COPY(Thread)
    friend class ThreadData;
    ThreadData *d;
};

}   // end of namespace J

#endif  // PROTOCORE_THREAD_H
