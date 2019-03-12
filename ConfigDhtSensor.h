#ifndef _CONFIGDHTSENSOR_H_
#define _CONFIGDHTSENSOR_H_

/**
 * Includes. 
 */
#include "ConfigBase.h"
#include "HelperIniFile.h"
#include <WString.h>


/**
 * Config : DHT Sensor Device.
 */
class ConfigDhtSensor : ConfigBase
{
private:
    int type;
    int pin;

public:
    ConfigDhtSensor(HelperIniFile& file);
    ~ConfigDhtSensor();
    
    void    ReadValues();
    int     GetType() const;
    int     GetPin() const;
};

#endif