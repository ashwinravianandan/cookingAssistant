#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include "CFoodDatabase.h"
#include "CFoodMenu.h"
#include <unistd.h>

using namespace std;
using namespace JsonHandling;


int main()
{
   //ifstream jsonDatabase( "menu.json" );

   Json::Value Jval;
   cin>>Jval;

   Json::Value babyFood, adultMenu;
   ( void )checkAndRetriveJsonData( Jval, "babyMenu", Json::arrayValue, babyFood );
   ( void )checkAndRetriveJsonData( Jval, "adultMenu", Json::arrayValue, adultMenu );
   CFoodDatabase childRecipies( babyFood  );
   CFoodDatabase adultRecipeies( adultMenu  );
   CFoodMenu weeklyMenu;
   weeklyMenu.generateBreakfastMenu( adultRecipeies, 7 );
   weeklyMenu.generateMealMenu( adultRecipeies, 7 );

   std::cout<<"generating menu and list"<<std::endl;
   weeklyMenu.generateMenu();
   weeklyMenu.generateGroceryList();
   std::cout<<"run successful"<<std::endl;

   return 0;
}


