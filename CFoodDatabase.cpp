#include <vector>
#include <string>
#include <iostream>
#include <json/json.h>
#include "CFoodDatabase.h"
#include <unistd.h>

using namespace std;
using namespace JsonHandling;

/*..............................................................................
 * @brief CFoodDatabase
 *
 * Input Parameters:
 *    @param: 
 *        Json::Value& FoodItems
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
CFoodDatabase::CFoodDatabase ( const Json::Value& FoodItems ):scJsonKeyIngredient("ingredients"),
   scJsonKeyBreakfast("breakfast"), scJsonKeyMainCourse("mainCourse"), scJsonKeyDish("dish")
{
   Json::Value breakfastItems, mealItems;
   for( Json::Value anyDish: FoodItems )
   {
      if ( true == checkAndRetriveJsonData( anyDish, scJsonKeyBreakfast, Json::arrayValue, breakfastItems ) )
      {
         for( Json::Value breakfastItem: breakfastItems)
         {
            foodItem breakFastDish;
            std::string dishName;
            if ( true == checkAndRetriveJsonData( breakfastItem, scJsonKeyDish, Json::stringValue, dishName ) )
            {
               breakFastDish.mDish = dishName;
               Json::Value dishIngredients;
               if ( true == checkAndRetriveJsonData( 
                        breakfastItem, scJsonKeyIngredient, Json::arrayValue, dishIngredients ) )
               {
                  for( Json::Value ingredient: dishIngredients )
                  {
                     breakFastDish.mIngredients.push_back( ingredient.asString() );
                  }
                  mBreakfastItems.push_back( breakFastDish );
               }
            }
         }
      }
      else if ( true ==  checkAndRetriveJsonData( anyDish, scJsonKeyMainCourse, Json::arrayValue, mealItems ) )
      {
         for( Json::Value mealItem: mealItems)
         {
            foodItem mealDish;
            std::string dishName;
            if ( true == checkAndRetriveJsonData( mealItem, scJsonKeyDish, Json::stringValue, dishName ) )
            {
               mealDish.mDish = dishName;
               Json::Value dishIngredients;
               if ( true == checkAndRetriveJsonData( 
                        mealItem, "ingredients", Json::arrayValue, dishIngredients ) )
               {
                  for( Json::Value ingredient: dishIngredients )
                  {
                     mealDish.mIngredients.push_back( ingredient.asString() );
                  }
                  mMainCourse.push_back( mealDish );
               }
            }
         }
      }
      else
      {
         ;
      }
   }
}

/*..............................................................................
 * @brief getRandomFoodItem
 *
 * Input Parameters:
 *    @param: 
 *        itemType
 *        randomItem
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CFoodDatabase::getRandomFoodItem ( const enFoodItemType& itemType, foodItem& randomItem ) const
{
   if ( ( itemType == enBreakfastItem ) && ( mBreakfastItems.size() > 0 ) )
   {
      unsigned int randomItemIdx = rand() % mBreakfastItems.size();
      randomItem = mBreakfastItems[ randomItemIdx ];
   }
   else if ( ( itemType == enLunchItem ) && ( mMainCourse.size() > 0 ) )
   {
      unsigned int randomItemIdx = rand() % mMainCourse.size();
      randomItem = mMainCourse[ randomItemIdx ];
   }
   else
   {
      /**
       * @todo: process other categories   
       */
   }
   
   return ;/*void*/
}


void CFoodDatabase::DisplayFoodItems(void )
{
   for( foodItem dish: mBreakfastItems)
   {
      cout<<dish.mDish.c_str()<<std::endl;
      for( std::string ingredients: dish.mIngredients)
      {
         cout<<ingredients.c_str()<<"\t";
      }
   }
   cout<<std::endl;
   for( foodItem dish: mMainCourse)
   {
      cout<<dish.mDish.c_str()<<std::endl;
      for( std::string ingredients: dish.mIngredients)
      {
         cout<<ingredients.c_str()<<"\t";
      }
   }
}

