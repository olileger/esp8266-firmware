#ifndef _CONFIGAPP_H_
#define _CONFIGAPP_H_

/**
 * Includes. 
 */
#include "ConfigBase.h"
#include "HelperIniFile.h"
#include <WString.h>


/**
 * Config : Application.
 */
class ConfigApp : public ConfigBase
{
private:
    String          deviceid;
    unsigned long   frequency;

public:
    ConfigApp(HelperIniFile& file);
    ~ConfigApp();
    
    void            ReadValues();
    String          GetDeviceId() const;
    unsigned long   GetFrequency() const;
};

#endif