/**
 * Includes
 */
#include "HelperIniFile.h"
#include <FS.h>
#include "HelperLog.h"


/**
 * Constructor.
 */
HelperIniFile::HelperIniFile(String filename):
sections(),
fileOpened(false)
{
    // Open the file.
    SPIFFS.begin();
    File f = SPIFFS.open(filename.c_str(), "r");
    if (!f)
    {
        HelperLog::LogError(filename + " doesn't exist");
        return;
    }

    // Read each line
    String s;
    String currentSection;
    while ((s = f.readStringUntil('\n')).length() > 0)
    {
        s.replace("\r", "");
        if (s.length() == 0)
        {
            continue;
        }
        if (s.startsWith("["))
        {
            currentSection = s;
            this->sections.insert(HelperIniFileSection(currentSection, HelperIniFileLines()));
        }
        else if (currentSection.length() > 0)
        {
            String k = s.substring(0, s.indexOf("="));
            String v = s.substring(s.indexOf("=") + 1);
            HelperIniFileLines& lines = this->sections[currentSection];
            lines.insert(HelperIniFileLine(k, v));
        }
    }

    // Close the file.
    f.close();
    this->fileOpened = true;
}

/**
 * Destructor.
 */
HelperIniFile::~HelperIniFile()
{

}

/**
 * Returns the sections of the ini file.
 */
HelperIniFileSections& HelperIniFile::GetSections()
{
    return this->sections;
}

/**
 * Return the state of the current file.
 */
bool HelperIniFile::IsFileOk()
{
    return this->fileOpened;
}