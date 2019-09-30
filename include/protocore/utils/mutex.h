#ifndef PROTOCORE_MUTEX_H
#define PROTOCORE_MUTEX_H

#include "../global.h"

namespace J {

// class Mutex

class MutexData;

class PROTOCORE_EXPORT Mutex
{
public:
    explicit Mutex(bool recursive = false);
    ~Mutex();

    void lock();
    void unlock();

private:
    J_DISABLE_COPY(Mutex)
    MutexData *d;
};

// class MutexLocker

class PROTOCORE_EXPORT MutexLocker
{
public:
    explicit MutexLocker(Mutex *mutex);
    ~MutexLocker();

private:
    J_DISABLE_COPY(MutexLocker)
    Mutex *mutex_;
};

// class Critical

class CriticalData;

class PROTOCORE_EXPORT Critical
{
public:
    Critical();
    ~Critical();

    void acquire();
    void release();

private:
    J_DISABLE_COPY(Critical)
    CriticalData *d;
};

// class CriticalLocker

class PROTOCORE_EXPORT CriticalLocker
{
public:
    CriticalLocker(Critical *c);
    ~CriticalLocker();

private:
    J_DISABLE_COPY(CriticalLocker)
    Critical *c_;
};

}   // end of namespace J

#endif  // PROTOCORE_MUTEX_H
