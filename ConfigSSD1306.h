#ifndef _CONFIGSSD1306_H_
#define _CONFIGSSD1306_H_

/**
 * Includes.
 */
#include "ConfigBase.h"
#include "HelperIniFile.h"
#include <WString.h>


 /**
 * Config : SSD 1306 Device.
 */
class ConfigSSD1306 : ConfigBase
{
private:
    float textSize;

public:
    ConfigSSD1306(HelperIniFile& file);
    ~ConfigSSD1306();
    
    void    ReadValues();
    float   GetTextSize() const;
};

#endif