/**
 * Includes. 
 */
#include "ControllerWifiClient.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WString.h>
extern "C"
{
    #include <user_interface.h>
}
#include "HelperLog.h"


/**
 * Constructor.
 */
ControllerWifiClient::ControllerWifiClient(HelperIniFile& file):
cfg(file)
{
    this->cfg.ReadValues();
    char *s = (char*)malloc(this->cfg.GetHostname().length());
    strncpy(s, this->cfg.GetHostname().c_str(), this->cfg.GetHostname().length());
    wifi_station_set_hostname(s);
    free(s);
}

/**
 * Destructor.
 */
ControllerWifiClient::~ControllerWifiClient()
{
}

/**
 * Try to connect to the hotspot.
 */
void ControllerWifiClient::Connect()
{
    if (!this->IsConnected())
    {
        HelperLog::LogInfo("[WIFI] Not connected to wifi hotspot " + this->cfg.GetSsid());
        //if (!this->IsConnecting())
        {
            HelperLog::LogInfo("[WIFI] Trying to connect, last known status : " + String(WiFi.status()));
            WiFi.begin(this->cfg.GetSsid().c_str(), this->cfg.GetKey().c_str());
        }
    }
}

/**
 * Returns the current WiFi client status.
 */
bool ControllerWifiClient::IsConnected() const
{
    return WiFi.status() == WL_CONNECTED;
}

/**
 * Returns the current WiFi client status.
 */
bool ControllerWifiClient::IsConnecting() const
{
    return WiFi.status() == WL_IDLE_STATUS;
}