#ifndef PROTOCORE_DATETIME_H
#define PROTOCORE_DATETIME_H

#include "item.h"
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
typedef struct __timeval_t {
    long tv_sec;        /* seconds */
    long tv_usec;       /* and microseconds */
} timeval_t;
#elif defined(__unix__)
#include <sys/time.h>
#define timeval_t struct timeval
#elif defined(__APPLE__)
#include <sys/time.h>
#define timeval_t struct timeval
#endif

namespace J {

enum DateTimeType {
    DateTimeInvalid = -1,
    DateTime_UTC6Bytes,
    DateTime_MSecsSinceEpoch,
    DateTime_Timeval,
    DateTime_TimeT,
    DateTimeTotal
};

enum DateTimeFormatType {
    DTF_Invalid = -1,
    DTF_Date,
    DTF_DateNoDash,
    DTF_TimeSec,
    DTF_TimeSecColon,
    DTF_TimeSecNoDash,
    DTF_TimeMSec,
    DTF_TimeMSecColon,
    DTF_TimeMSecNoDash,
    DTF_DateTimeSec,
    DTF_DateTimeSecColon,
    DTF_DateTimeSecNoDash,
    DTF_DateTimeMSec,
    DTF_DateTimeMSecColon,
    DTF_DateTimeMSecNoDash,
    DTF_DateTimeSecNoTimeDash,
    DTF_DateTimeMSecNoTimeDash,
    DTF_StrfTime
};

#pragma pack(push)
#pragma pack(1)

//
typedef struct __utc6bytes_t {
    uint16_t mseconds: 10;
    uint16_t second: 6;
    uint16_t minute: 6;
    uint16_t hour: 5;
    uint16_t day: 5;
    uint16_t month: 4;
    uint16_t year: 12;
} utc6bytes_t;

#pragma pack(pop)

class DateTime;
typedef std::shared_ptr<DateTime> DateTimePtr;

class DateTimeData;

class PROTOCORE_EXPORT DateTime : public Item
{
public:
    explicit DateTime(Object *parent = nullptr);
    explicit DateTime(const std::string &id, Object *parent = nullptr);
    DateTime(const DateTime &other);
    ~DateTime() J_OVERRIDE;

    int rtti() const override;

    DateTimeType dateTimeType() const;
    void setDateTimeType(DateTimeType type);
    std::string dateTimeTypeString() const;
    static std::string dateTimeTypeString(DateTimeType type);
    static DateTimeType stringDateTimeType(const std::string &str);

    double data() const override;
    void setData(double data) override;
    std::string dataString() const override;
    double dataFromBuffer(const char *buffer) const override;

    int64_t toSecsSinceEpoch() const;
    int64_t toMSecsSinceEpoch() const;
    timeval_t toTimeval() const;
    time_t toTime_t() const;
    utc6bytes_t toUTC6Bytes(bool locale = false) const;

    void setSecsSinceEpoch(int64_t secs);
    void setMSecsSinceEpoch(int64_t msecs);
    void setTimeval(const timeval_t &tv);
    void setTime_t(const time_t &t);
    void setUTC6Bytes(const utc6bytes_t &t);

    std::string toString(DateTimeFormatType type = DTF_DateTimeMSecColon) const;
    std::string toLocaleString(DateTimeFormatType type = DTF_DateTimeMSecColon) const;

    std::string typeName() const override;
    std::string typeString() const override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    DateTime &operator =(const DateTime &other);

    bool isGlobal() const;
    void setGlobal(bool enabled);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

public:
    // utils

    static int64_t currentSecsSinceEpoch();
    static int64_t currentMSecsSinceEpoch();
    static std::string currentDateTime(DateTimeFormatType type = DTF_DateTimeMSecColon);
    static std::string currentDateTime(const std::string &format, bool locale = true);

    static std::string dateTimeToString(int64_t msecs, DateTimeFormatType type = DTF_DateTimeMSecColon,
                                        bool locale = true);

    static timeval_t msecsSinceEpochToTimeval(int64_t msecs);
    static int64_t timevalToMSecsSinceEpoch(const timeval_t &tv);

    static time_t msecsSinceEpochToTimeT(int64_t msecs);
    static int64_t timeTToMSecsSinceEpoch(const time_t &t);

    static utc6bytes_t msecsSinceEpochToUTC6Bytes(int64_t msecs, bool locale = false);
    static int64_t utc6BytesToMSecsSinceEpoch(const utc6bytes_t &t);

private:
    DateTimeData *d;
};

}   // end of namespace J

#endif // PROTOCORE_DATETIME_H
