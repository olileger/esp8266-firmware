#ifndef _DEVICEDHTSENSOR_H_
#define _DEVICEDHTSENSOR_H_

/**
 * Includes.
 */
#include "ConfigDhtSensor.h"
#include "HelperIniFile.h"


/**
 * Device : DHT Sensor.
 */
class DeviceDhtSensor
{
private:
    ConfigDhtSensor cfg;

public:
    DeviceDhtSensor(HelperIniFile& file);
    ~DeviceDhtSensor();

    bool ReadValues(float& t, float& h);
};

#endif