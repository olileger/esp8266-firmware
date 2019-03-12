/**
 * Includes. 
 */
#include "DeviceSSD1306.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>


/**
 * Constructor.
 */
DeviceSSD1306::DeviceSSD1306(HelperIniFile& file):
cfg(file),
display(0)
{
    this->cfg.ReadValues();

    this->display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    this->display.clearDisplay();
    this->display.setTextSize(this->cfg.GetTextSize());
    this->display.setTextColor(WHITE, BLACK);
}

/**
 * Destructor.
 */
DeviceSSD1306::~DeviceSSD1306()
{

}

/**
 * Clear the screen.
 */
void DeviceSSD1306::Clear()
{
    this->display.clearDisplay();
}

/**
 * Clear a line on the screen.
 */
void DeviceSSD1306::ClearLine(int position)
{
    String text = "                    ";
    this->WriteLine(position, text);
}

/**
 * Write a line to the screen.
 */
void DeviceSSD1306::WriteLine(int position, String& text)
{
    this->display.setCursor(0, (SSD1306_LCDHEIGHT / 3) * position);
    this->display.println(text.c_str());
    this->display.display();
}