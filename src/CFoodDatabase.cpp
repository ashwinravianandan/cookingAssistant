#include <vector>
#include <string>
#include <iostream>
#include <json/json.h>
#include "CFoodDatabase.h"
#include <unistd.h>
#include <algorithm>
#include <random>

using namespace std;
using namespace JsonHandling;

template <typename T>
T getRandIterator( T begin, T end )
{
   std::random_device rand;
   std::mt19937_64 gen( rand() );

   std::uniform_int_distribution<> intDist( 0, std::distance(begin, end) -1 );
   std::advance( begin, intDist( gen ) );
   return begin;
}

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
   scJsonKeyBreakfast("breakfast"), scJsonKeyMainCourse("mainCourse"), scJsonKeyDish("dish"),scJsonKeySnack("snack")
{
   Json::Value breakfastItems, mealItems, snackItems;
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
                        mealItem, scJsonKeyIngredient, Json::arrayValue, dishIngredients ) )
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
      else if ( true ==  checkAndRetriveJsonData( anyDish, scJsonKeySnack, Json::arrayValue, snackItems ) )
      {
         for( Json::Value snackItem: snackItems)
         {
            foodItem mealDish;
            std::string dishName;
            if ( true == checkAndRetriveJsonData( snackItem, scJsonKeyDish, Json::stringValue, dishName ) )
            {
               mealDish.mDish = dishName;
               Json::Value dishIngredients;
               if ( true == checkAndRetriveJsonData( 
                        snackItem, scJsonKeyIngredient, Json::arrayValue, dishIngredients ) )
               {
                  for( Json::Value ingredient: dishIngredients )
                  {
                     mealDish.mIngredients.push_back( ingredient.asString() );
                  }
                  mSnacks.push_back( mealDish );
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
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool CFoodDatabase::getRandomFoodItem ( const enFoodItemType& itemType, foodItem& randomItem ) const
{
   std::random_device randDev;
   bool success = true;
   if ( ( itemType == enBreakfastItem ) && ( mBreakfastItems.size() > 0 ) )
   {
      randomItem = *getRandIterator( mBreakfastItems.begin(), mBreakfastItems.end() );
   }
   else if ( ( itemType == enLunchItem ) && ( mMainCourse.size() > 0 ) )
   {
      randomItem = *getRandIterator( mMainCourse.begin(), mMainCourse.end() );
   }
   else if ( ( itemType == enSnacks ) && ( mSnacks.size() > 0 ) )
   {
      randomItem = *getRandIterator( mSnacks.begin(), mSnacks.end() );
   }
   else
   {
      /**
       * @todo: process other categories   
       */
      success = false;

   }
   return success;/*bool*/
}

/*..............................................................................
 * @brief getNumberOfRecipes
 *
 * Input Parameters:
 *    @param: 
 *        enFoodItemType& itemType
 * Return Value:
 *    @returns unsigned int
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
unsigned int CFoodDatabase::getNumberOfRecipes ( const enFoodItemType& itemType )const
{
   unsigned int numberOfItems = 0;
   if ( itemType == enBreakfastItem )
   {
      numberOfItems = mBreakfastItems.size();
   }
   else if (itemType == enLunchItem )
   {
      numberOfItems = mMainCourse.size();
   }
   else if ( itemType == enSnacks )
   {
      numberOfItems = mSnacks.size();
   }
   else
   {

   }
   return numberOfItems;/*void*/
}


