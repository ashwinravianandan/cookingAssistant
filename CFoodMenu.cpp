#include <vector>
#include <list>
#include <string>
#include "CFoodDatabase.h"
#include "CFoodMenu.h"
#include <fstream>
#include <algorithm>
using namespace std;
using namespace JsonHandling;

std::list<string> CFoodMenu::mIngredients;

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
   bool allowDuplicates = (numberOfItems < foodDB.getNumberOfRecipes ( enBreakfastItem ) ) ? true : false;
   for ( unsigned int i = 0; i < numberOfItems; ++i )
   {
      foodItem item;
      if( true == foodDB.getRandomFoodItem( enBreakfastItem, item ) )
      {
         if ( false == allowDuplicates )
         {
            if( mBreakfastMenu.end() != std::find( begin( mBreakfastMenu ), end( mBreakfastMenu ), item.mDish ) )
            {
               --i;
               continue;
            }
         }
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
   bool allowDuplicates = (numberOfItems < foodDB.getNumberOfRecipes ( enLunchItem ) ) ? true : false;
   for ( unsigned int i = 0; i < numberOfItems; ++i )
   {
      foodItem item;
      if( true == foodDB.getRandomFoodItem( enLunchItem, item ) )
      {
         if ( false == allowDuplicates )
         {
            if( mMealMenu.end() != std::find( begin( mMealMenu ), end( mMealMenu ), item.mDish ) )
            {
               --i;
               continue;
            }
         }
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
void CFoodMenu::generateMenu ( ostream& outFile )
{
   outFile<<"Breakfast Items"<<std::endl;
   outFile<<"==============="<<std::endl;
   for( string item : mBreakfastMenu )
   {
      outFile<<"*   "<<item.c_str()<<std::endl;
   }
   outFile<<std::endl<<std::endl<<"Meals"<<std::endl;
   outFile<<"====="<<std::endl;
   for( string item :  mMealMenu )
   {
      outFile<<"*   "<<item.c_str()<<std::endl;
   }
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
void CFoodMenu::generateGroceryList ( ostream& outFile )
{
   mIngredients.sort();
   mIngredients.unique();
   for( string item : mIngredients )
   {
      outFile<<"*   "<<item.c_str()<<std::endl;
   }
}

