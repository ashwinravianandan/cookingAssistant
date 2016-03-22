#pragma once
#include <fstream>
#include <string>
#include <set>
using namespace std;
class COptionsHandler final
{
   private:
      string mMenuFile;
      string mGroceryFile;
      string mDatabaseFile;
      set< pair<string, unsigned int >> mListCriteria;

      COptionsHandler( );
      bool interpretListCriteria ( string listArgument );
   protected:
   public:
      virtual ~COptionsHandler( );
      COptionsHandler( const COptionsHandler& ) = delete;
      COptionsHandler( const COptionsHandler&& ) = delete;
      COptionsHandler& operator = ( const COptionsHandler& ) = delete;

      static COptionsHandler& getInstance( void );
      bool initialize( int, char* [] );
      string getDatabasePath() const;
      string getMenuFilePath() const;
      string getGroceryFilePath()const;
      set< pair<string, unsigned int >> getListCriteria( )const;
};

