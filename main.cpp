#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include "CFoodMenu.h"

using namespace std;
using namespace JsonHandling;


int main()
{
   ifstream jsonDatabase( "menu.json" );

   Json::Value Jval;
   jsonDatabase>>Jval;

   Json::Value babyFood, adultMenu;
   if (true == checkAndRetriveJsonData( Jval, "babyMenu", Json::arrayValue, babyFood ))
   {
      CFoodMenu babyFoodMenu( babyFood  );
      babyFoodMenu.DisplayFoodItems();
   }
   if (true == checkAndRetriveJsonData( Jval, "adultMenu", Json::arrayValue, adultMenu ))
   {
      CFoodMenu adultMealMenu( adultMenu  );
      adultMealMenu.DisplayFoodItems();
   }
   return 0;
}


