#pragma once
#include <fstream>
#include <string>
using namespace std;
class COptionsHandler final
{
   private:
      string mMenuFile;
      string mGroceryFile;
      string mDatabaseFile;
      ofstream mMenuFileHandle;
      ofstream mGroceryFileHandle;
      bool mGenerateBabyMenu;
      bool mGenerateAdultMenu;

      COptionsHandler( );
   protected:
   public:
      virtual ~COptionsHandler( );
      COptionsHandler( const COptionsHandler& ) = delete;
      COptionsHandler( const COptionsHandler&& ) = delete;
      COptionsHandler& operator = ( const COptionsHandler& ) = delete;

      static COptionsHandler& getInstance( void );
      bool initialize( int, char* [] );
      ostream& groceryFile( );
      ostream& menuFile ( );
      bool generateBabyMenu() const;
      bool generateAdultMenu() const;
      string getDatabasePath() const;
};

