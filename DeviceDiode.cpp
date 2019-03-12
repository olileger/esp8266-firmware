/**
 * Includes. 
 */
#include "DeviceDiode.h"
#include <Arduino.h>


/**
 * Constructor.
 */
DeviceDiode::DeviceDiode(HelperIniFile& file):
cfg(file)
{
    this->cfg.ReadValues();
}

/**
 * Destructor.
 */
DeviceDiode::~DeviceDiode()
{
}

/**
 * Set the diode depending of the state.
 */
void DeviceDiode::setState(bool state)
{
    pinMode(this->cfg.GetPin(), OUTPUT);
    if (state)
    {
        digitalWrite(this->cfg.GetPin(), HIGH);
    }
    else
    {
        digitalWrite(this->cfg.GetPin(), LOW);
    }
}

/**
 * Read the diode state.
 */
bool DeviceDiode::readState()
{
    pinMode(this->cfg.GetPin(), INPUT);
    return digitalRead(this->cfg.GetPin());
}

/**
 * Light the diode.
 */
void DeviceDiode::On()
{
    this->setState(true);
}

/**
 * True if diode is lightened.
 */
bool DeviceDiode::IsOn()
{
    return this->readState();
}

/**
 * Unlight the diode.
 */ 
void DeviceDiode::Off()
{
    this->setState(false);
}

/**
 * True if diode is not lightened.
 */
bool DeviceDiode::IsOff()
{
    return !this->readState();
}