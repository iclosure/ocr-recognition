#ifndef JMACADDRESS_H
#define JMACADDRESS_H

#include "global.h"

namespace jencrypt {

struct JMacAddressData;

class JENCRYPT_EXPORT JMacAddress
{
public:
    explicit JMacAddress();
    ~JMacAddress();

    void reset();
    bool hasNext() const;
    std::string next();

private:
    JMacAddressData *data;
};

} // end of namespace jencrypt

#endif // JMACADDRESS_H
