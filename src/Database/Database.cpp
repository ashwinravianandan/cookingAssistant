#include "Database.h"
/*..............................................................................
 * @brief JsonFileDatabase
 *
 * Input Parameters:
 *    @param: 
 *        string& dbPath
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
JsonFileDatabase::JsonFileDatabase ( const string& dbPath ): mPathToDB( dbPath )
{
   mDatabaseHandle.open( dbPath );
}

/*..............................................................................
 * @brief ~JsonFileDatabase
 *
 * Input Parameters:
 *    @param: 
 *        string& dbPath
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
JsonFileDatabase::~JsonFileDatabase ()
{
   close();
}
/*..............................................................................
 * @brief open
 *
 * Input Parameters:
 *    @param: 
 *        string& databasePath
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool JsonFileDatabase::open ( const string& databasePath )
{
   if ( databasePath != mPathToDB )
   {
      if ( mDatabaseHandle.is_open())
      {
         mDatabaseHandle.close();
         mPathToDB = databasePath;
      }
   }
   if ( ! mDatabaseHandle.is_open() )
   {
      mDatabaseHandle.open( mPathToDB );
   }
   return true;/*bool*/
}

/*..............................................................................
 * @brief readDatabase
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool JsonFileDatabase::readDatabase ( Json::Value& jsonDB)
{
   mDatabaseHandle>>jsonDB;
   return true;
}

/*..............................................................................
 * @brief close
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool JsonFileDatabase::close ( )
{
   if ( mDatabaseHandle.is_open())
   {
      mDatabaseHandle.close();
   }
}

