#pragma once
#include <string>
#include <vector>
#include "json.h"
#include "TagDB.h"
using namespace std;


typedef ITagDatabase<string, SideDish> SideDishTagDatabase;
typedef ITagDatabase<string, MainCourse> MainCourseCategoryDB;

typedef struct _recipeGroup
{
   string mGroupName;
   vector< string > mIngredients;
}RecipeGroup;

class MealDB final
{
   private:
      vector< RecipeGroup > mRecipeGroups;
      vector< MainCourse > mMainCourseItems;
      vector< SideDish > mSideDishes;
      SideDishTagDatabase mSideDishTagDB;

      void populateRecipeGroups ( const Json::Value& jsonDB );
      void populateMealItems ( const Json::Value& jsonDB );
      void populateSides ( const Json::Value& jsonDB );

   protected:

   public:
      MealDB( );
      MealDB( const Json::Value& );
      virtual ~MealDB( );
      vector< RecipeGroup > getRecipeGroups( ) const ;
      const SideDishTagDatabase& sideDishDB( void )const;
      void getMainCourseItems( vector<MainCourse>& meals )const;
      void getSides( vector<SideDish>& sides )const;
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

