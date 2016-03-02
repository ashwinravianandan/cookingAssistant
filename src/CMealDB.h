#pragma once
#include <string>
#include <vector>
#include "json.h"
using namespace std;

typedef struct _recipeGroup
{
   string mGroupName;
   vector< string > mIngredients;
}RecipeGroup;

typedef struct _mealItem
{
   string mDishName;
   string mMealCategory;
   bool mNeedsSide;
   vector< string > mSideCategories; // this attribute makes sense only if the dish needs a side
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

class CMealDB final
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

namespace JsonHandling
{
   class CJsonValue: public Json::Value
   {
      /**
       * @todo: extend to all types 
       */

      public:
         CJsonValue( const Json::Value& JVal ):Json::Value( JVal ){}
         operator unsigned int()
         {
            return this->asUInt();
         }
         operator std::string() 
         {
            return this->asString();
         }
         operator  int()
         {
            return this->asInt();
         }
         operator bool()
         {
            return this->asBool();
         }
   };
   template <typename T>
      bool checkAndRetriveJsonData( Json::Value JVal, const char* key, Json::ValueType valType, T& data )
      {
         bool retVal = false;
         if ( valType == JVal[ key ].type() )
         {
            CJsonValue Val = JVal[ key ];
            retVal = true;
            data = static_cast<T>( Val );
         }
         return retVal;
      }
}

