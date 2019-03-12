#ifndef _CONFIGAZUREIOTHUBCLIENT_H_
#define _CONFIGAZUREIOTHUBCLIENT_H_

/**
 * Includes. 
 */
#include "ConfigBase.h"
#include "HelperIniFile.h"
#include <WString.h>


/**
 * Config : Azure IoT Hub.
 */
class ConfigAzureIoTHubClient : public ConfigBase
{
private:
    String iothubName;
    String sasToken;
    String bootMessage;
    String telemetryMessage;

public:
    ConfigAzureIoTHubClient(HelperIniFile& file);
    ~ConfigAzureIoTHubClient();
    
    void    ReadValues();
    String  GetIoTHubName() const;
    String  GetSasToken() const;
    String  GetBootMessage() const;
    String  GetTelemetryMessage() const;
};

#endif