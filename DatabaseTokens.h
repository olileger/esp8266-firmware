#ifndef _DATABASETOKENS_H_
#define _DATABASETOKENS_H_

/**
 * Includes. 
 */
#include <map>
#include <WString.h>


/**
 * Token / value holder.
 */
typedef std::map<String, String>            DbTokenValues;
typedef std::map<String, String>::iterator  DbTokenValuesIterator;
typedef std::pair<String, String>           DbTokenValue;

/**
 * Database : Tokens.
 */
class DatabaseTokens
{
private:
    DbTokenValues db;

public:
    DatabaseTokens();
    ~DatabaseTokens();
    void    Upsert(String k, String v);
    void    ReplaceTokenByValue(String& str);
};

#endif