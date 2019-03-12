/**
 * Includes. 
 */
#include "ConfigDhtSensor.h"


/**
 * Constructor. 
 */
ConfigDhtSensor::ConfigDhtSensor(HelperIniFile& file):
ConfigBase(file),
type(11),
pin(0)
{
}

/**
 * Destructor. 
 */
ConfigDhtSensor::~ConfigDhtSensor()
{
}

/**
 * Read the values.
 */
void ConfigDhtSensor::ReadValues()
{
    if (this->file.IsFileOk())
    {
        String token = "[DHT-SENSOR-DEVICE]";
        this->type = this->file.GetSections()[token]["type"].toInt();
        this->pin = this->file.GetSections()[token]["pin"].toInt();
    }
}

/**
 * Returns the type field. 
 */
int ConfigDhtSensor::GetType() const
{
    return this->type;
}

/**
 * Returns the pin field. 
 */
int ConfigDhtSensor::GetPin() const
{
    return this->pin;
}