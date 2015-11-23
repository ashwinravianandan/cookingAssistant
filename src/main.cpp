#include <json/json.h>
#include <iostream>
#include <fstream>
#include "CMealDB.h"
#include "CMealGenerator.h"
#include "COptionsHandler.h"
#include "CListGenerator.h"
#include <algorithm>
using namespace std;
using namespace JsonHandling;


int main(int argc, char* argv[] )
{
   COptionsHandler::getInstance().initialize( argc, argv );

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
   listGen.addListCriteria( std::make_pair( tenMealCategory::BREAD, 10 ) );
   listGen.addListCriteria( std::make_pair( tenMealCategory::RICE, 4 ) );
   
   if ( listGen.generateMenu( gen ) )
   {
      cout<< "successfully generated menu";
      listGen.exportMenu( COptionsHandler::getInstance().menuFile() );
      listGen.exportGroceryList( COptionsHandler::getInstance().groceryFile() );
   }
   return 0;
}

