
#ifndef JPROTOCOL_PRECITIMER_H
#define JPROTOCOL_PRECITIMER_H

#include "../global.h"

#ifdef _MSC_VER
#include <Windows.h>
#include <assert.h>
#endif

namespace J {

#ifdef _MSC_VER

class PROTOCORE_EXPORT PreciTimer
{
public:
    PreciTimer();
    ~PreciTimer();

    //
    void reset();

    // 返回CPU计数器值(us)
    inline LONGLONG uscount() const
    {
        LARGE_INTEGER lcount;
        QueryPerformanceCounter(&lcount);
        return lcount.QuadPart * 1000000UL / q_freq;
    }

    // 返回CPU计数器值(ms)
    inline LONGLONG mscount() const
    {
        LARGE_INTEGER lcount;
        QueryPerformanceCounter(&lcount);
        return lcount.QuadPart * 1000UL / q_freq;
    }

    // 返回从初始化到现在的时间间隔(us)
    inline LONGLONG ustick() const
    {
        LARGE_INTEGER lcount;
        QueryPerformanceCounter(&lcount);
        return (lcount.QuadPart - q_count) * 1000000UL / q_freq;
    }

    // 返回从初始化到现在的时间间隔(ms)
    inline LONGLONG mstick() const
    {
        LARGE_INTEGER lcount;
        QueryPerformanceCounter(&lcount);
        return (lcount.QuadPart - q_count) * 1000UL / q_freq;
    }

private:
    J_DISABLE_COPY(PreciTimer)
    LONGLONG q_freq;    // CPU频率
    LONGLONG q_count;   // 对象初始化时的时间
};
#else

class PROTOCORE_EXPORT PreciTimer
{
public:
    explicit PreciTimer(void);
    ~PreciTimer(void);

    //
    void reset() {}

    // 返回CPU计数器值(us)
    inline long long uscount() const
    {
        return 0;
    }

    // 返回CPU计数器值(ms)
    inline long long mscount() const
    {
        return 0;
    }

    // 返回从初始化到现在的时间间隔(us)
    inline long long ustick() const
    {
        return 0;
    }

    // 返回从初始化到现在的时间间隔(ms)
    inline long long mstick() const
    {
        return 0;
    }

private:
    J_DISABLE_COPY(PreciTimer)
};
#endif

}   // end of namespace J

#endif  // JPROTOCOL_PRECITIMER_H
