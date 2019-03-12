/**
 * Includes. 
 */
#include "DeviceDhtSensor.h"
#include <DHT.h>


/**
 * Constructor.
 */
DeviceDhtSensor::DeviceDhtSensor(HelperIniFile& file):
cfg(file)
{
    this->cfg.ReadValues();
}

/**
 * Destructor.
 */
DeviceDhtSensor::~DeviceDhtSensor()
{
}

/**
 * Read the Temperature & Humidity.
 */
bool DeviceDhtSensor::ReadValues(float& t, float& h)
{
    DHT d(this->cfg.GetPin(), this->cfg.GetType());
    d.begin();
    t = d.readTemperature();
    h = d.readHumidity();
}