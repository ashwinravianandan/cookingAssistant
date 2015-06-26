#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include "CFoodDatabase.h"
#include "CFoodMenu.h"
#include <unistd.h>

using namespace std;
using namespace JsonHandling;


int main(int argc, char* argv[] )
{
   //ifstream jsonDatabase( "menu.json" );

   opterr = 0;

   int c = 0;
   std::string menuFile, groceryFile, inputFile;

   while( ( c = getopt(argc, argv, "m:g:i:") ) != -1)
   {
      switch (c )
      {
         case 'm':
            {
               menuFile = optarg;
            }
            break;
         case 'g':
            {
               groceryFile = optarg;
            }
            break;
         case 'i':
            {
               inputFile = optarg;
            }
            break;
         case '?':
            {
               cerr<<"invalid command line args"<<std::endl;
               exit( 0 );
            }
            break;
      }
   }

   Json::Value Jval;
   if ( "" == inputFile )
   {
      cin>>Jval;
   }
   else
   {
      ifstream dbFile( inputFile.c_str() );
      if (true == dbFile.is_open() )
      {
         dbFile>>Jval;
         dbFile.close();
      }
   }
   Json::Value babyFood, adultMenu;

   ( void )checkAndRetriveJsonData( Jval, "babyMenu", Json::arrayValue, babyFood );
   ( void )checkAndRetriveJsonData( Jval, "adultMenu", Json::arrayValue, adultMenu );

   CFoodDatabase childRecipies( babyFood  );
   CFoodDatabase adultRecipeies( adultMenu  );

   CFoodMenu weeklyMenu;
   weeklyMenu.generateBreakfastMenu( adultRecipeies, 7 );
   weeklyMenu.generateMealMenu( adultRecipeies, 7 );

   if ( "" == menuFile )
   {
      weeklyMenu.generateMenu(std::cout);
   }
   else
   {
      ofstream menuObj( menuFile.c_str() );
      weeklyMenu.generateMenu( menuObj );
      menuObj.close();
   }

   if ( "" == groceryFile )
   {
      weeklyMenu.generateGroceryList(std::cout);
   }
   else
   {
      ofstream groceryObj( groceryFile.c_str() );
      weeklyMenu.generateGroceryList( groceryObj );
      groceryObj.close();
   }

   return 0;
}


