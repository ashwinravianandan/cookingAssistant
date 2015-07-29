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

   bool generateBabyMenu = false;
   bool generateAdultMenu = false;

   while( ( c = getopt(argc, argv, "m:g:i:ab") ) != -1)
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
         case 'b':
            {
               generateBabyMenu = true;
            }
            break;
         case 'a':
            {
               generateAdultMenu = true;
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

   CFoodMenu weeklyMenu, weeklyMenuAdult;
   if ( true == generateBabyMenu )
   {
      weeklyMenu.generateBreakfastMenu( childRecipies, 5 );
      weeklyMenu.generateMealMenu( childRecipies, 10 );
   }

   if ( true == generateAdultMenu )
   {
      weeklyMenuAdult.generateBreakfastMenu( adultRecipeies, 5 );
      weeklyMenuAdult.generateMealMenu( adultRecipeies, 5 );
   }

   if ( "" == menuFile )
   {
      if ( true == generateBabyMenu )
      {
         cout<<"Baby Menu:\n";
         weeklyMenu.generateMenu(std::cout);
      }
      if ( true == generateAdultMenu )
      {
         cout<<"\n\nAdult Menu:\n";
         weeklyMenuAdult.generateMenu( std::cout );
      }
   }
   else
   {
      ofstream menuObj( menuFile.c_str() );
      if ( true == generateBabyMenu )
      {
         menuObj<<"Baby Menu:\n";
         weeklyMenu.generateMenu( menuObj );
      }
      if ( true == generateAdultMenu )
      {
         menuObj<<"\n\nAdult Menu:\n";
         weeklyMenuAdult.generateMenu( menuObj );
      }
      menuObj.close();
   }

   if( ( true == generateBabyMenu) || ( true == generateAdultMenu ) )
   {
      if ( "" == groceryFile )
      {
         cout<<"\n\nGrocery List:\n=============\n";
         weeklyMenu.generateGroceryList(std::cout);
      }
      else
      {
         ofstream groceryObj( groceryFile.c_str() );
         weeklyMenu.generateGroceryList( groceryObj );
         groceryObj.close();
      }
   }

   return 0;
}

