#ifndef _HELPERINIFILE_H_
#define _HELPERINIFILE_H_

/**
 * Includes
 */
#include <map>
#include <WString.h>


/**
 * Local types.
 */
typedef std::map<String, String>                        HelperIniFileLines;
typedef std::map<String, String>::iterator              HelperIniFileLinesIterator;
typedef std::pair<String, String>                       HelperIniFileLine;
typedef std::map<String, HelperIniFileLines>            HelperIniFileSections;
typedef std::map<String, HelperIniFileLines>::iterator  HelperIniFileSectionsIterator;
typedef std::pair<String, HelperIniFileLines>           HelperIniFileSection;


/**
 * Helper : INI file reader.
 */
class HelperIniFile
{
private:
    HelperIniFileSections   sections;
    bool                    fileOpened;

public:    
    HelperIniFile(String filename);
    ~HelperIniFile();

    HelperIniFileSections&  GetSections();
    bool                    IsFileOk();
};

#endif