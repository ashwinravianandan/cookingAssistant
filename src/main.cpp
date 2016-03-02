#include "json.h"
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
      listGen.exportMenu( COptionsHandler::getInstance().menuFile() );
      listGen.exportGroceryList( COptionsHandler::getInstance().groceryFile() );
   }
   return 0;
}

