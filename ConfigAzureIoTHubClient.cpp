/**
 * Includes. 
 */
#include "ConfigAzureIoTHubClient.h"


/**
 * Constructor. 
 */
ConfigAzureIoTHubClient::ConfigAzureIoTHubClient(HelperIniFile& file):
ConfigBase(file),
iothubName("Undefined"),
sasToken("Undefined"),
bootMessage("Undefined"),
telemetryMessage("Undefined")
{
}

/**
 * Destructor. 
 */
ConfigAzureIoTHubClient::~ConfigAzureIoTHubClient()
{
}

/**
 * Read the values.
 */
void ConfigAzureIoTHubClient::ReadValues()
{
    if (this->file.IsFileOk())
    {
        String token = "[AZURE-IOT-HUB-CLIENT-CONTROLLER]";
        this->iothubName = this->file.GetSections()[token]["iothub-name"];
        this->sasToken = this->file.GetSections()[token]["sas-token"];
        this->bootMessage = this->file.GetSections()[token]["boot-message"];
        this->telemetryMessage = this->file.GetSections()[token]["telemetry-message"];
    }
}

/**
 * Returns the IoT Hub name.
 */
String ConfigAzureIoTHubClient::GetIoTHubName() const
{
    return this->iothubName;
}

/**
 * Returns the Sas token.
 */
String ConfigAzureIoTHubClient::GetSasToken() const
{
    return this->sasToken;
}

/**
 * Returns the boot message.
 */
String ConfigAzureIoTHubClient::GetBootMessage() const
{
    return this->bootMessage;
}

/**
 * Returns the telemetry message.
 */
String ConfigAzureIoTHubClient::GetTelemetryMessage() const
{
    return this->telemetryMessage;
}