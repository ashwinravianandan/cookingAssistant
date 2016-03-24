#include "json.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

template <typename T>
class IInputDatabase
{
   protected:
   public:
      virtual bool readDatabase( T& ) = 0;
      virtual ~IInputDatabase(){}
};

class JsonFileDatabase final: public IInputDatabase<Json::Value>
{
   private:
      string mPathToDB;
      ifstream mDatabaseHandle;

   public:
      JsonFileDatabase( const string& dbPath);

      bool open( const string& databasePath ) ;
      bool readDatabase( Json::Value& jsonDB )override;
      bool close( void ) ;
      
      virtual ~JsonFileDatabase();
};

class JsonConsoleDatabase final: public IInputDatabase<Json::Value>
{
   virtual bool readDatabase( Json::Value& jsonDB )override{ cin>>jsonDB;return true;}
   virtual ~JsonConsoleDatabase(){}
};

