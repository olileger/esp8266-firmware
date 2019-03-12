#ifndef _HELPERLOG_H_
#define _HELPERLOG_H_

/**
 * Includes. 
 */
#include <WString.h>


/**
 * Log level.
 */
enum HelperLogLevel
{
    HELPERLOG_LEVEL_ERROR,
    HELPERLOG_LEVEL_INFO
};

/**
 * Helper : Logging features.
 */
class HelperLog
{
private:
    HelperLog();
    static void Log(HelperLogLevel level, String s);

public:
    static HelperLogLevel level;
    
    static void Begin();
    static void LogError(String s);
    static void LogError(const char* s);
    static void LogInfo(String s);
    static void LogInfo(const char* s);
};

#endif