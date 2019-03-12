#ifndef _CONFIGWIFICLIENT_H_
#define _CONFIGWIFICLIENT_H_

/**
 * Includes. 
 */
#include "ConfigBase.h"
#include "HelperIniFile.h"
#include <WString.h>


/**
 * Config : Wifi Client.
 */
class ConfigWifiClient : ConfigBase
{
private:
    String hostname;
    String ssid;
    String key;

public:
    ConfigWifiClient(HelperIniFile& file);
    ~ConfigWifiClient();
    
    void    ReadValues();
    String  GetHostname() const;
    String  GetSsid() const;
    String  GetKey() const;
};

#endif