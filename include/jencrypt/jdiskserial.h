#ifndef JDISKSERIAL_H
#define JDISKSERIAL_H

#include "global.h"

namespace jencrypt {

struct JDiskSerialData;

class JENCRYPT_EXPORT JDiskSerial
{
public:
    explicit JDiskSerial();
    ~JDiskSerial();

    void reset();
    bool hasNext() const;
    std::string next();

    static std::string hdId();

private:
	bool readDrivePortsInWin9x();
	bool readPhysicalDriveInNTWithAdminRights();
	bool readIdeDriveAsScsiDriveNT();
	bool readPhysicalDriveNTWithZeroRights();

private:
	JDiskSerialData *data;
};

} // end of namespace jencrypt

#endif // JDISKSERIAL_H
