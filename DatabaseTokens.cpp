/**
 * Includes. 
 */
#include "DatabaseTokens.h"


/**
 * Constructor.
 */
DatabaseTokens::DatabaseTokens():
db()
{
}

/**
 * Destructor.
 */
DatabaseTokens::~DatabaseTokens()
{
}

/**e
 * Upsert a record to the DB.
 */
void DatabaseTokens::Upsert(String k, String v)
{
    this->db[k] = v;
}

/**
 * Replace all tokens within str by corresponding values in tokenValues.
 */
void DatabaseTokens::ReplaceTokenByValue(String& str)
{
    for (DbTokenValuesIterator it = (DbTokenValuesIterator)this->db.begin();
         it != this->db.end();
         it++)
    {
        str.replace(it->first, it->second);
    }
}