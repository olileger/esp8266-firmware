/**
 * Includes. 
 */
#include "ConfigSSD1306.h"


/**
 * Constructor. 
 */
ConfigSSD1306::ConfigSSD1306(HelperIniFile& file):
ConfigBase(file),
textSize(1.5)
{
}

/**
 * Destructor. 
 */
ConfigSSD1306::~ConfigSSD1306()
{
}

/**
 * Read the values.
 */
void ConfigSSD1306::ReadValues()
{
    if (this->file.IsFileOk())
    {
        String token = "[SSD1306-DEVICE]";
        this->textSize = this->file.GetSections()[token]["text-size"].toFloat();
    }
}

/**
 * Returns the text size.
 */
float ConfigSSD1306::GetTextSize() const
{
    return this->textSize;
}