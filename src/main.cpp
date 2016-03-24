#include "json.h"
#include <iostream>
#include "MealGenerator.h"
#include "OptionsHandler.h"
#include "ListGenerator.h"
#include <memory>
#include "Database.h"
#include "Print.h"
#include "MealMenuPrinter.h"
#include "GroceryListPrinter.h"
using namespace std;
using namespace JsonHandling;


int main(int argc, char* argv[] )
{
   if( !OptionsHandler::getInstance().initialize( argc, argv ) )
   {
      exit( 0 );
   }
   Json::Value Jval;
   unique_ptr<IInputDatabase<Json::Value>> db = ( OptionsHandler::getInstance().getDatabasePath().empty() )?
      unique_ptr<IInputDatabase<Json::Value>>{ new JsonConsoleDatabase{} }: 
      unique_ptr<IInputDatabase<Json::Value>>{ new JsonFileDatabase{OptionsHandler::getInstance().getDatabasePath()}};

   db->readDatabase( Jval );

   MealDB mealDatabase( Jval );
   MealGenerator gen( mealDatabase );
   ListGenerator listGen;

   listGen.addListCriteria( OptionsHandler::getInstance().getListCriteria() );
   
   if ( listGen.generateMenu( gen ) )
   {
      cout<< "successfully generated menu";

      string menuFilePath = OptionsHandler::getInstance().getMenuFilePath();
      string groceryFilePath = OptionsHandler::getInstance().getGroceryFilePath();
      
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

