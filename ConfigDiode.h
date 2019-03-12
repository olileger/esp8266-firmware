#ifndef _CONFIGDIODE_H_
#define _CONFIGDIODE_H_

/**
 * Includes. 
 */
#include "ConfigBase.h"
#include "HelperIniFile.h"
#include <WString.h>


/**
 * Config : Diode Device.
 */
class ConfigDiode : ConfigBase
{
private:
    int pin;

public:
    ConfigDiode(HelperIniFile& file);
    ~ConfigDiode();
    
    void    ReadValues();
    int     GetPin() const;
};

#endif