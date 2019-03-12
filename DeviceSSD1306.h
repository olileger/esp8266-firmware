#ifndef DEVICESSD1306_H_
#define DEVICESSD1306_H_

/**
 * Includes.
 */
#include "ConfigSSD1306.h"
#include "HelperIniFile.h"
#include <Adafruit_SSD1306.h>
#include <WString.h>


/**
 * Device : SSD1306 (OLED).
 */
class DeviceSSD1306
{
private:
    ConfigSSD1306       cfg;
    Adafruit_SSD1306    display;

public:
    DeviceSSD1306(HelperIniFile& file);
    ~DeviceSSD1306();

    void Clear();
    void ClearLine(int position);
    void WriteLine(int position, String& text);
};

#endif