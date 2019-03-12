#ifndef _DEVICEDIODE_H_
#define _DEVICEDIODE_H_

/**
 * Includes.
 */
#include "ConfigDiode.h"
#include "HelperIniFile.h"


/**
 * Device : Diode.
 */
class DeviceDiode
{
private:
    ConfigDiode cfg;

    void setState(bool state);
    bool readState();

public:
    DeviceDiode(HelperIniFile& file);
    ~DeviceDiode();

    void On();
    bool IsOn();
    void Off();
    bool IsOff();
};

#endif