/**
 * Includes. 
 */
#include "ConfigDiode.h"


/**
 * Constructor. 
 */
ConfigDiode::ConfigDiode(HelperIniFile& file):
ConfigBase(file),
pin(0)
{
}

/**
 * Destructor. 
 */
ConfigDiode::~ConfigDiode()
{
}

/**
 * Read the values.
 */
void ConfigDiode::ReadValues()
{
    if (this->file.IsFileOk())
    {
        String token = "[DIODE-DEVICE]";
        this->pin = this->file.GetSections()[token]["pin"].toInt();
    }
}

/**
 * Returns the pin field. 
 */
int ConfigDiode::GetPin() const
{
    return this->pin;
}