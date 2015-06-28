#pragma once
#include <vector>
#include <list>
#include <string>
#include "CFoodDatabase.h"
#include <iostream>
using namespace std;

class CFoodMenu
{
   private:
      std::vector<string> mBreakfastMenu;
      std::vector<string> mMealMenu;
      static std::list<string> mIngredients;

   public:
      CFoodMenu();
      virtual ~CFoodMenu() = default;
       bool generateBreakfastMenu( const CFoodDatabase& foodDB, const unsigned int& numberOfItems );
       bool generateMealMenu( const CFoodDatabase& foodDB, const unsigned int& numberOfItems );
       void generateGroceryList( ostream& );
       void generateMenu( ostream& );
};

