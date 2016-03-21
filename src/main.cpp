#include "json.h"
#include <iostream>
#include <fstream>
#include "CMealDB.h"
#include "CMealGenerator.h"
#include "COptionsHandler.h"
#include "CListGenerator.h"
#include <algorithm>
#include "Print.h"
#include "MenuFilePrinter.h"
#include "ConsoleMenuPrinter.h"
#include <memory>
using namespace std;
using namespace JsonHandling;


int main(int argc, char* argv[] )
{
   if( !COptionsHandler::getInstance().initialize( argc, argv ) )
   {
      exit( 0 );
   }
   Json::Value Jval;
   if ( "" == COptionsHandler::getInstance().getDatabasePath() )
   {
      cin>>Jval;
   }
   else
   {
      ifstream dbFile( COptionsHandler::getInstance().getDatabasePath().c_str() );
      if (true == dbFile.is_open() )
      {
         dbFile>>Jval;
         dbFile.close();
      }
   }

   CMealDB mealDatabase( Jval );
   CMealGenerator gen( mealDatabase );
   CListGenerator listGen;
   listGen.addListCriteria( COptionsHandler::getInstance().getListCriteria() );
   if ( listGen.generateMenu( gen ) )
   {
      cout<< "successfully generated menu";

      string menuFilePath = COptionsHandler::getInstance().getMenuFilePath();
      
      typedef vector<pair<string,string>> MenuItems;

      unique_ptr<IPrint<MenuItems>> uptr = ( menuFilePath.empty() )?
         unique_ptr<IPrint<MenuItems>>{ new ConsoleMenuPrinter{}}:
         unique_ptr<IPrint<MenuItems>>{ new MenuFilePrinter{menuFilePath}};

      uptr->print( listGen.getMealMenu() );

      listGen.exportGroceryList( COptionsHandler::getInstance().groceryFile() );
   }
   return 0;
}

