/**
 * Includes. 
 */
#include "ConfigApp.h"


/**
 * Constructor. 
 */
ConfigApp::ConfigApp(HelperIniFile& file):
ConfigBase(file),
deviceid("Undefined"),
frequency(15000)
{
}

/**
 * Destructor. 
 */
ConfigApp::~ConfigApp()
{
}

/**
 * Read the values.
 */
void ConfigApp::ReadValues()
{
    if (this->file.IsFileOk())
    {
        String token = "[APP-CONTROLLER]";
        this->deviceid = this->file.GetSections()[token]["deviceid"];
        this->frequency = this->file.GetSections()[token]["frequency"].toInt();
    }
}

/**
 * Returns the deviceid field. 
 */
String ConfigApp::GetDeviceId() const
{
    return this->deviceid;
}

/**
 * Returns the frequency field. 
 */
unsigned long ConfigApp::GetFrequency() const
{
    return this->frequency;
}