#ifndef JCPUID_H
#define JCPUID_H

#include "global.h"

namespace jencrypt {

struct JCpuIdData;

class JENCRYPT_EXPORT JCpuId
{
public:
    explicit JCpuId();
    ~JCpuId();

    void reset();
    bool hasNext() const;
    std::string next();

    static std::string cpuId();

private:
	std::string getCpuId();

private:
    JCpuIdData *data;
};

} // end of namespace jencrypt

#endif // JCPUID_H
