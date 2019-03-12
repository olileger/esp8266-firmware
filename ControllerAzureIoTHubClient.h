#ifndef _CONTROLLERAZUREIOTHUBCLIENT_H_
#define _CONTROLLERAZUREIOTHUBCLIENT_H_

/**
 * Includes. 
 */
#include "ConfigAzureIoTHubClient.h"
#include "DatabaseTokens.h"
#include "DeviceDiode.h"
#include "HelperIniFile.h"
#include <WString.h>


/**
 * Azure IoT Hub Message.
 */
class AzureIoTHubMessage
{
public:
    String messageId;
    String eTag;
    String message;
};

/**
 * Controller : Azure IoT Hub client.
 */
class ControllerAzureIoTHubClient
{
private:
    ConfigAzureIoTHubClient cfg;
    bool                    bootSent;
    const String            methodDelete = "DELETE";
    const String            methodGet = "GET";
    const String            methodPost = "POST";
    const String            urlSendMessage = "/devices/%DEVICEID%/messages/events?api-version=2016-11-14";
    const String            urlReadMessage = "/devices/%DEVICEID%/messages/deviceBound?api-version=2016-11-14";
    const String            urlAckComplete = "/devices/%DEVICEID%/messages/deviceBound/%ETAG%?api-version=2016-11-14";
    const String            urlAckAbandon = "/devices/%DEVICEID%/messages/deviceBound/%ETAG%/abandon?api-version=2016-11-14";

    int     sendRequest(DatabaseTokens& db, String method, String path, String body, String& response);
    bool    isBootMessageSent();
    
public:
    ControllerAzureIoTHubClient(HelperIniFile& file);
    ~ControllerAzureIoTHubClient();

    String  ExtractToken(String& message, String token, int offset, int len);
    bool    SendBootMessage(DatabaseTokens& db);
    bool    SendMessage(DatabaseTokens& db);
    bool    ReadMessage(DatabaseTokens& db, AzureIoTHubMessage& msg);
    bool    AckComplete(DatabaseTokens& db, String eTag);
    bool    AckAbandon(DatabaseTokens& db, String eTag);
};

#endif