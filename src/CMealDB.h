#pragma once
#include "CFoodDatabase.h"
#include <string>
#include <vector>
#include <json/json.h>
using namespace std;

typedef struct _recipeGroup
{
   string mGroupName;
   vector< string > mIngredients;
}RecipeGroup;

typedef struct _mealItem
{
   string mDishName;
   bool mNeedsSide;
   string mSideCategory; // this attribute makes sense only if the dish needs a side
   vector< string > mIngredients;
   vector< string > mRecipeGroups; // list of recipe groups
}MealItem;

typedef struct _sides
{
   string mDishName;
   vector< string > mIngredients;
   vector< string > mRecipeGroups; // list of recipe groups
   vector< string > mCategories;
}Sides;

class CMealDB
{
   private:
      vector< RecipeGroup > mRecipeGroups;
      vector< MealItem > mMealItems;
      vector< Sides > mSideDishes;

      void populateRecipeGroups ( const Json::Value& jsonDB );
      void populateMealItems ( const Json::Value& jsonDB );
      void populateSides ( const Json::Value& jsonDB );
      
   protected:

   public:
      CMealDB( );
      CMealDB( const Json::Value& );
      virtual ~CMealDB( );
      vector< Sides > getSides( ) const ;
      vector< MealItem > getMealItems( ) const ;
      vector< RecipeGroup > getRecipeGroups( ) const ;
};
