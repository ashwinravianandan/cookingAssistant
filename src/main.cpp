#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include "CMealDB.h"
#include "CMealGenerator.h"
#include "CFoodDatabase.h"
#include "COptionsHandler.h"
#include "CFoodMenu.h"
#include <unistd.h>
#include <algorithm>
using namespace std;
using namespace JsonHandling;


int main(int argc, char* argv[] )
{
   //ifstream jsonDatabase( "menu.json" );
   opterr = 0;

   int c = 0;

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
   Json::Value babyFood, adultMenu;

   ( void )checkAndRetriveJsonData( Jval, "babyMenu", Json::arrayValue, babyFood );
   ( void )checkAndRetriveJsonData( Jval, "adultMenu", Json::arrayValue, adultMenu );

   CFoodDatabase childRecipies( babyFood  );
   CFoodDatabase adultRecipeies( adultMenu  );

   CMealDB mealDatabase( Jval );

   CMealGenerator gen( mealDatabase );

   Meal randomMeal;
   if ( gen.generateRandomMeal( randomMeal, tenMealCategory::BREAD ) )
   {
      cout<<"successfully retrieved random meal"<<endl;
      std::cout<<randomMeal.mRecipeName<<"\t"<<randomMeal.mSide<<endl;
      std::for_each( begin( randomMeal.mIngredients ), end( randomMeal.mIngredients ),
            []( string ing ) { cout<< ing.c_str()<<endl; } );
   }

   CFoodMenu weeklyMenu, weeklyMenuAdult;
   if ( true == COptionsHandler::getInstance().generateBabyMenu() )
   {
      weeklyMenu.generateBreakfastMenu( childRecipies, 7 );
      weeklyMenu.generateMealMenu( childRecipies, 14 );
      weeklyMenu.generateSnackMenu( childRecipies, 7 );

      COptionsHandler::getInstance().menuFile()<<"Baby Menu:\n";
      weeklyMenu.generateMenu( COptionsHandler::getInstance().menuFile() );
   }

   if ( true == COptionsHandler::getInstance().generateAdultMenu() )
   {
      weeklyMenuAdult.generateBreakfastMenu( adultRecipeies, 7 );
      weeklyMenuAdult.generateMealMenu( adultRecipeies, 14 );
      weeklyMenuAdult.generateSnackMenu( adultRecipeies, 7 );
      COptionsHandler::getInstance().menuFile()<<"Adult Menu:\n";
      weeklyMenuAdult.generateMenu( COptionsHandler::getInstance().menuFile() );
   }
   if ( ( true == COptionsHandler::getInstance().generateBabyMenu() ) || 
   ( true == COptionsHandler::getInstance().generateAdultMenu() ) )
   {
      COptionsHandler::getInstance().groceryFile()<<"\n\nGrocery List:\n=============\n";
      weeklyMenu.generateGroceryList(COptionsHandler::getInstance().groceryFile());
   }

   return 0;
}

