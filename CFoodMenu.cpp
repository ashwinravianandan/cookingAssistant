#include <vector>
#include <list>
#include <string>
#include "CFoodDatabase.h"
#include "CFoodMenu.h"
#include <fstream>
using namespace std;
using namespace JsonHandling;

/*..............................................................................
 * @brief CFoodMenu 
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 CFoodMenu::CFoodMenu( )
{
   mBreakfastMenu.clear();
   mMealMenu.clear();
   mIngredients.clear();
}

/*..............................................................................
 * @brief generateBreakfastMenu
 *
 * Input Parameters:
 *    @param: foodDB, 
 *        numberOfItems
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool CFoodMenu::generateBreakfastMenu ( const CFoodDatabase& foodDB, 
      const unsigned int& numberOfItems )
{
   bool success = false;
   for ( unsigned int i = 0; i < numberOfItems; ++i )
   {
      foodItem item;
      if( true == foodDB.getRandomFoodItem( enBreakfastItem, item ) )
      {
         mBreakfastMenu.push_back( item.mDish );
         for( string ingredient: item.mIngredients )
         {
            mIngredients.push_back( ingredient );
         }
      }
   }
   return success;/*bool*/
}

/*..............................................................................
 * @brief generateMealMenu
 *
 * Input Parameters:
 *    @param: foodDB, 
 *        intnumberOfItems
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool CFoodMenu::generateMealMenu ( const CFoodDatabase& foodDB, 
      const unsigned int &numberOfItems )
{
   bool success = false;
   for ( unsigned int i = 0; i < numberOfItems; ++i )
   {
      foodItem item;
      if( true == foodDB.getRandomFoodItem( enLunchItem, item ) )
      {
         mMealMenu.push_back( item.mDish );
         for( string ingredient: item.mIngredients )
         {
            mIngredients.push_back( ingredient );
         }
      }
   }
   return success;/*bool*/
}

/*..............................................................................
 * @brief generateMenu
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CFoodMenu::generateMenu ( )
{
   ofstream foodMenu("menu.txt");
   foodMenu<<"Breakfast Items"<<std::endl;
   foodMenu<<"==============="<<std::endl;
   for( string item : mBreakfastMenu )
   {
      foodMenu<<"*   "<<item.c_str()<<std::endl;
   }
   foodMenu<<std::endl<<std::endl<<"Meals"<<std::endl;
   foodMenu<<"====="<<std::endl;
   for( string item :  mMealMenu )
   {
      foodMenu<<"*   "<<item.c_str();
   }
   foodMenu.close();
}

/*..............................................................................
 * @brief generateGroceryList 
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CFoodMenu::generateGroceryList ( )
{
   ofstream groceryList("groceryList.txt");
   mIngredients.sort();
   mIngredients.unique();
   for( string item : mIngredients )
   {
      groceryList<<"*   "<<item.c_str()<<std::endl;
   }
   groceryList.close();
}

