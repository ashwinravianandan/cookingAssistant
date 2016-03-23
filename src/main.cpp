#include "json.h"
#include <iostream>
#include <fstream>
#include "CMealDB.h"
#include "CMealGenerator.h"
#include "COptionsHandler.h"
#include "CListGenerator.h"
#include <algorithm>
#include "Print.h"
#include "MealMenuPrinter.h"
#include "GroceryListPrinter.h"
#include <memory>
#include "Database.h"
using namespace std;
using namespace JsonHandling;


int main(int argc, char* argv[] )
{
   if( !COptionsHandler::getInstance().initialize( argc, argv ) )
   {
      exit( 0 );
   }
   Json::Value Jval;
   unique_ptr<IInputDatabase<Json::Value>> db = ( COptionsHandler::getInstance().getDatabasePath().empty() )?
      unique_ptr<IInputDatabase<Json::Value>>{ new JsonConsoleDatabase{} }: 
      unique_ptr<IInputDatabase<Json::Value>>{ new JsonFileDatabase{COptionsHandler::getInstance().getDatabasePath()}};

   db->readDatabase( Jval );

   CMealDB mealDatabase( Jval );
   CMealGenerator gen( mealDatabase );
   CListGenerator listGen;

   listGen.addListCriteria( COptionsHandler::getInstance().getListCriteria() );
   
   if ( listGen.generateMenu( gen ) )
   {
      cout<< "successfully generated menu";

      string menuFilePath = COptionsHandler::getInstance().getMenuFilePath();
      string groceryFilePath = COptionsHandler::getInstance().getGroceryFilePath();
      
      typedef vector<pair<string,string>> MenuItems;

      unique_ptr<IPrint<MenuItems>> uptr = ( menuFilePath.empty() )?
         unique_ptr<IPrint<MenuItems>>{ new ConsoleMenuPrinter{}}:
         unique_ptr<IPrint<MenuItems>>{ new MenuFilePrinter{menuFilePath}};

      unique_ptr<IPrint<unordered_set<string>>> glPrinter = (groceryFilePath.empty())?
         unique_ptr<IPrint<unordered_set<string>>>{ new GroceryListConsolePrinter{}}:
         unique_ptr<IPrint<unordered_set<string>>>{ new GroceryListFilePrinter{groceryFilePath}};

      uptr->print( listGen.getMealMenu() );
      glPrinter->print( listGen.getGroceryList() );
   }
   return 0;
}

