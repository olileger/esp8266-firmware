/**
 * Includes. 
 */
#include "ConfigWifiClient.h"
#include "HelperLog.h"


/**
 * Constructor. 
 */
ConfigWifiClient::ConfigWifiClient(HelperIniFile& file):
ConfigBase(file),
hostname("Undefined"),
ssid("Undefined"),
key("Undefined")
{
}

/**
 * Destructor. 
 */
ConfigWifiClient::~ConfigWifiClient()
{
}

/**
 * Read the values.
 */
void ConfigWifiClient::ReadValues()
{
    if (this->file.IsFileOk())
    {
        String token = "[WIFI-CLIENT-CONTROLLER]";
        this->hostname = this->file.GetSections()[token]["hostname"];
        this->ssid = this->file.GetSections()[token]["ssid"];
        this->key = this->file.GetSections()[token]["key"];
    }
}

/**
 * Returns the hostname field. 
 */
String ConfigWifiClient::GetHostname() const
{
    return this->hostname;
}

/**
 * Returns the ssid field. 
 */
String ConfigWifiClient::GetSsid() const
{
    return this->ssid;
}

/**
 * Returns the key field. 
 */
String ConfigWifiClient::GetKey() const
{
    return this->key;
}