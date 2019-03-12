#ifndef _CONFIGBASE_H_
#define _CONFIGBASE_H_

/**
 * Includes. 
 */
#include "HelperIniFile.h"


/**
 * Config : Base class.
 */
class ConfigBase
{
protected:
    HelperIniFile& file;

    ConfigBase(HelperIniFile& file);
    virtual void ReadValues();
    
public:
    virtual ~ConfigBase();
};

#endif