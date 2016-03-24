#pragma once
#include <fstream>
#include <string>
#include <set>
using namespace std;
class OptionsHandler final
{
   private:
      string mMenuFile;
      string mGroceryFile;
      string mDatabaseFile;
      set< pair<string, unsigned int >> mListCriteria;

      OptionsHandler( );
      bool interpretListCriteria ( string listArgument );
   protected:
   public:
      virtual ~OptionsHandler( );
      OptionsHandler( const OptionsHandler& ) = delete;
      OptionsHandler( const OptionsHandler&& ) = delete;
      OptionsHandler& operator = ( const OptionsHandler& ) = delete;

      static OptionsHandler& getInstance( void );
      bool initialize( int, char* [] );
      string getDatabasePath() const;
      string getMenuFilePath() const;
      string getGroceryFilePath()const;
      set< pair<string, unsigned int >> getListCriteria( )const;
};

