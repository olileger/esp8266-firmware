#ifndef _CONTROLLERAPP_H_
#define _CONTROLLERAPP_H_

/**
 * Includes. 
 */
#include "ConfigApp.h"
#include "ControllerAzureIoTHubClient.h"
#include "ControllerWifiClient.h"
#include "DatabaseTokens.h"
#include "DeviceDiode.h"
#include "DeviceDhtSensor.h"
#include "DeviceSSD1306.h"
#include <WString.h>


/**
 * Main Arduino app handler.
 */
class ControllerApp
{
private:
    String                          cfgFilename;
    ConfigApp*                      pCfg;
    unsigned long                   nextLoop;
    DatabaseTokens                  tokens;
    ControllerAzureIoTHubClient*    pAzIoTHubClient;
    ControllerWifiClient*           pWifiClient;
    DeviceDiode*                    pDiode;
    DeviceDhtSensor*                pDhtSensor;
    DeviceSSD1306*                  pOled;

    bool    IsTimeToRun() const;
    void    SetNextLoop();
    bool    SetDiode(AzureIoTHubMessage& msg);
    bool    SetText(AzureIoTHubMessage& msg);

public:
    ControllerApp(String configFilename = "/config.ini");
    ~ControllerApp();
    void Setup();
    void Loop();
};

#endif