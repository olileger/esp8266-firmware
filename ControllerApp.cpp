/**
 * Includes. 
 */
#include "ControllerApp.h"
#include <Arduino.h>
#include "HelperIniFile.h"
#include "HelperLog.h"


/**
 * Constructor.
 */
ControllerApp::ControllerApp(String configFilename):
cfgFilename(configFilename),
pCfg(NULL),
nextLoop(0),
tokens(),
pWifiClient(NULL),
pAzIoTHubClient(NULL),
pDiode(NULL),
pDhtSensor(NULL),
pOled(NULL)
{

}

/**
 * Destructor.
 */
ControllerApp::~ControllerApp()
{
    delete this->pAzIoTHubClient;
    delete this->pWifiClient;
    delete this->pDiode;
    delete this->pDhtSensor;
    delete this->pOled;
    delete this->pCfg;
}

/**
 * Setup the manager.
 */
void ControllerApp::Setup()
{
    HelperLog::Begin();
    Serial.println("Running Setup()");
    HelperIniFile file(this->cfgFilename);

    Serial.println("->Fill App Config");
    this->pCfg = new ConfigApp(file);
    this->pCfg->ReadValues();
    this->tokens.Upsert("%DEVICEID%", this->pCfg->GetDeviceId());

    Serial.println("->Create Controllers");
    this->pWifiClient = new ControllerWifiClient(file);
    this->pAzIoTHubClient = new ControllerAzureIoTHubClient(file);

    Serial.println("->Create Devices");
    this->pDiode = new DeviceDiode(file);
    this->pDhtSensor = new DeviceDhtSensor(file);
    this->pOled = new DeviceSSD1306(file);

    Serial.println("End of Setup()");
}

/**
 * Main loop.
 */
void ControllerApp::Loop()
{
    if (!this->IsTimeToRun())
    {
        return;
    }

    // Read the DHT values.
    if (this->pDhtSensor)
    {
        float t;
        float h;
        this->pDhtSensor->ReadValues(t, h);
        this->tokens.Upsert("%TEMPERATURE%", String(t, 2));
        this->tokens.Upsert("%HUMIDITY%", String(h, 2));

        // Write to OLED screen.
        String temp = "T " + String(t, 2) + " C";
        this->pOled->ClearLine(0);
        this->pOled->WriteLine(0, temp);
        
        String hum = "H " + String(h, 2) + " %";
        this->pOled->ClearLine(1);
        this->pOled->WriteLine(1, hum);
    }

    // Interact with endpoint.
    this->pWifiClient->Connect();
    if (this->pWifiClient->IsConnected())
    {
        // Send Boot message
        this->pAzIoTHubClient->SendBootMessage(this->tokens);

        // Send Telemetry
        this->pAzIoTHubClient->SendMessage(this->tokens);

        // Read commands.
        AzureIoTHubMessage msg;
        while (this->pAzIoTHubClient->ReadMessage(this->tokens, msg))
        {
            // Execute command.
            bool ret = false;
            if (msg.message.indexOf("SetDiode") != -1)
            {
                ret = this->SetDiode(msg);
            }
            else if (msg.message.indexOf("SetText") != -1)
            {
                ret = this->SetText(msg);
            }

            // Ack command
            if (ret)
            {
                this->pAzIoTHubClient->AckComplete(this->tokens, msg.eTag);
            }
            else
            {
                this->pAzIoTHubClient->AckAbandon(this->tokens, msg.eTag);
            }
        }
    }

    this->SetNextLoop();
}

/**
 * Check whether it's time to run.
 */
bool ControllerApp::IsTimeToRun() const 
{
    return millis() >= this->nextLoop;
}

/**
 * Set the next timer value for the next loop exec.
 */
void ControllerApp::SetNextLoop()
{
    this->nextLoop = millis() + ((this->pWifiClient->IsConnected()) ? this->pCfg->GetFrequency(): 2000);
}

/**
 * Set the diode state according to the command.
 */
bool ControllerApp::SetDiode(AzureIoTHubMessage& msg)
{
    String state = this->pAzIoTHubClient->ExtractToken(msg.message, "State", 7, 4);
    if (state != "")
    {
        if (state == "true")
        {
            this->pDiode->On();
        }
        else
        {
            this->pDiode->Off();
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Write a text to the OLED screen.
 */
bool ControllerApp::SetText(AzureIoTHubMessage& msg)
{
    int start = msg.message.indexOf("\"Text\":") + 8;
    int end = msg.message.lastIndexOf("\"}}");
    String text = msg.message.substring(start, end);
    //HelperLog::LogError("[CtrlApp] Start : " + start);
    //HelperLog::LogError("[CtrlApp] End : " + end);
    HelperLog::LogError("[CtrlApp] SetText : " + text);
    this->pOled->WriteLine(2, text);
    return true;
}