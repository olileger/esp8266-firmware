#ifndef _CONTROLLERWIFICLIENT_H_
#define _CONTROLLERWIFICLIENT_H_

/**
 * Includes. 
 */
#include "ConfigWifiClient.h"
#include "HelperIniFile.h"


/**
 * Controller : Wifi as a client.
 */
class ControllerWifiClient
{
private:
    ConfigWifiClient cfg;

public:
    ControllerWifiClient(HelperIniFile& file);
    ~ControllerWifiClient();
    void Connect();
    bool IsConnected() const;
    bool IsConnecting() const;
};

#endif