/**
 * Includes. 
 */
#include "ControllerAzureIoTHubClient.h"
#include <ESP8266WiFi.h>
#include "HelperLog.h"


/**
 * ControllerAzureIoTHubClient Constructor.
 */
ControllerAzureIoTHubClient::ControllerAzureIoTHubClient(HelperIniFile& file):
cfg(file),
bootSent(false)
{
    this->cfg.ReadValues();
}

/**
 * ControllerAzureIoTHubClient Destructor.
 */
ControllerAzureIoTHubClient::~ControllerAzureIoTHubClient()
{
}

/**
 * Returns the state of the boot message.
 */
bool ControllerAzureIoTHubClient::isBootMessageSent()
{
    return this->bootSent;
}

/**
 * Extract an HTTP Header token from an HTTP message.
 */
String ControllerAzureIoTHubClient::ExtractToken(String& message, String token, int offset, int len)
{
    String ret = "";
    int index = message.indexOf(token);
    if (index < message.length())
    {
        index += offset;
        ret = message.substring(index, index + len);
        HelperLog::LogInfo("[AzIoTHub] " + token + " : " + ret);
    }
    else
    {
        HelperLog::LogError("[AzIoTHub] Bad index to extract " + token + " : " + String(index));
    }

    return ret;
}

/**
 * Send a request to the backend.
 */
int ControllerAzureIoTHubClient::sendRequest(DatabaseTokens& db,
                                             String method,
                                             String path,
                                             String body,
                                             String& response)
{
    int httpCode = -1;

    // Setup the WiFiClientSecure.
    WiFiClientSecure c;
    String host = this->cfg.GetIoTHubName() + ".azure-devices.net";
    if (!c.connect(host.c_str(), 443))
    {
        HelperLog::LogError("[AzIoTHub] Connection to " + host + ":443 failed");
        return httpCode;
    }

    // Setup the headers.
    String payload = method + " " + path + " HTTP/1.1\r\n";
    payload += "Host: " + host + "\r\n";
    payload += "Content-Type: application/json\r\n";
    payload += "Authorization: " + this->cfg.GetSasToken() + "\r\n";

    // Add the body.
    if (body.length() > 0)
    {
        db.ReplaceTokenByValue(body);
        payload += "Content-Length: " + String(body.length()) + "\r\n\r\n";
        payload += body;
    }
    else
    {
        payload += "\r\n";
    }

    // Replace the payload tokens by values.
    db.ReplaceTokenByValue(payload);

    // Send the request.
    int sz = c.print(payload.c_str());
    HelperLog::LogInfo("Payload : " + payload);
    bool readResponse = sz == payload.length();
    if (!readResponse)
    {
        HelperLog::LogError("[AzIoTHub] Sent " + String(sz) + " bytes of " + String(payload.length()));
    }

    // Read the response.
    if (readResponse)
    {
        // Read response.
        String s = c.readString();
        response = s;
        HelperLog::LogInfo("Response = " + response);

        // Extract HTTP Code.
        s = s.substring(0, s.indexOf("\r"));
        int codeIndex = s.indexOf(" ") + 1;
        httpCode = s.substring(codeIndex, codeIndex + 3).toInt();
        HelperLog::LogInfo("Code = " + String(httpCode));
    }

    return httpCode;
}

/**
 * Send the boot message.
 */
bool ControllerAzureIoTHubClient::SendBootMessage(DatabaseTokens& db)
{
    if (this->isBootMessageSent())
    {
        return true;
    }

    String  response;
    int     httpCode;

    // Send HTTP POST.
    if ((httpCode = this->sendRequest(db,
                                      this->methodPost,
                                      this->urlSendMessage,
                                      this->cfg.GetBootMessage(),
                                      response)) < 0)
    {
        HelperLog::LogError("[AzIoTHub] Failed to send boot message");
        return false;
    }

    // Check result.
    if (httpCode != 204)
    {
        HelperLog::LogError("[AzIoTHub] Send boot message received HTTP code " + String(httpCode));
        return false;
    }

    this->bootSent = true;
    return true;
}

/**
 * Send a message to IoT Hub (D2C).
 */
bool ControllerAzureIoTHubClient::SendMessage(DatabaseTokens& db)
{
    String  response;
    int     httpCode;

    // Send HTTP POST.
    if ((httpCode = this->sendRequest(db,
                                      this->methodPost,
                                      this->urlSendMessage,
                                      this->cfg.GetTelemetryMessage(),
                                      response)) < 0)
    {
        return false;
    }

    // Check result.
    if (httpCode != 204)
    {
        HelperLog::LogError("[AzIoTHub] Send message received HTTP code " + String(httpCode));
        return false;
    }

    return true;
}

/**
 * Read a message from IoT Hub (C2D).
 */
bool ControllerAzureIoTHubClient::ReadMessage(DatabaseTokens& db, AzureIoTHubMessage& msg)
{
    int httpCode;

    // Send HTTP GET.
    if ((httpCode = this->sendRequest(db,
                                      this->methodGet,
                                      this->urlReadMessage,
                                      "",
                                      msg.message)) < 0)
    {
        return false;
    }

    // Check result.
    if (httpCode != 200 && httpCode != 204)
    {
        HelperLog::LogError("[AzIoTHub] Read message received HTTP code " + String(httpCode));
        return false;
    }

    // Extract the messageId & the eTag.
    if (httpCode == 200)
    {
        // messageId.
        msg.messageId = this->ExtractToken(msg.message, "iothub-messageid", 18, 36);

        // eTag.
        msg.eTag = this->ExtractToken(msg.message, "ETag", 7, 36);
    }

    return httpCode == 200;
}

/**
 * Acknowledge a D2C as Completed.
 */
bool ControllerAzureIoTHubClient::AckComplete(DatabaseTokens& db, String eTag)
{
    String  response;
    int     httpCode;

    // Send HTTP DELETE.
    String url = this->urlAckComplete;
    url.replace("%ETAG%", eTag);
    if ((httpCode = this->sendRequest(db,
                                      this->methodDelete,
                                      url,
                                      "",
                                      response)) < 0)
    {
        return false;
    }

    // Check result.
    if (httpCode != 204)
    {
        HelperLog::LogError("[AzIoTHub] Ack complete received HTTP code " + String(httpCode));
        return false;
    }

    return true;
}

/**
 * Acknowledge a D2C as Abandoned.
 */
bool ControllerAzureIoTHubClient::AckAbandon(DatabaseTokens& db, String eTag)
{
    String  response;
    int     httpCode;

    // Send HTTP POST.
    String url = this->urlAckAbandon;
    url.replace("%ETAG%", eTag);
    if ((httpCode = this->sendRequest(db,
                                      this->methodPost,
                                      url,
                                      "",
                                      response)) < 0)
    {
        return false;
    }

    // Check result.
    if (httpCode != 204)
    {
        HelperLog::LogError("[AzIoTHub] Ack abandon received HTTP code " + String(httpCode));
        return false;
    }

    return true;
}