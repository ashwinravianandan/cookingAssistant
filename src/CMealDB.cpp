#include "CMealDB.h"
#include "MealBuilder.h"
using namespace JsonHandling;


/*..............................................................................
 * @brief CMealDB
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
CMealDB::CMealDB (  ) 
{
}

/*..............................................................................
 * @brief ~CMealDB
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
CMealDB::~CMealDB (  ) 
{
}

/*..............................................................................
 * @brief populateRecipeGroups
 *
 * Input Parameters:
 *    @param: 
 *        Json::Value& jsonDB
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CMealDB::populateRecipeGroups ( const Json::Value& jsonDB )
{
   Json::Value recipeGroups;

   if ( true == checkAndRetriveJsonData( jsonDB, "recipeGroups", Json::arrayValue, recipeGroups ) )
   {
      RecipeGroup grpFromDB;
      for( auto grp: recipeGroups )
      {
         Json::Value ingredients( Json::arrayValue );
         if ( true == checkAndRetriveJsonData( 
                  grp, "groupName", Json::stringValue, grpFromDB.mGroupName ) && 
               true == checkAndRetriveJsonData( 
                  grp, "ingredients", Json::arrayValue, ingredients ) )
         {
            for( auto ingredient : ingredients )
            {
               grpFromDB.mIngredients.push_back( ingredient.asString() );
            }
            mRecipeGroups.push_back( grpFromDB );
         }
      }
   }
   return ;/*void*/
}

/*..............................................................................
 * @brief populateMealItems
 *
 * Input Parameters:
 *    @param: 
 *        Json::Value& jsonDB
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CMealDB::populateMealItems ( const Json::Value& jsonDB )
{
   Json::Value mealItems;
   if ( true == checkAndRetriveJsonData( jsonDB, "mealItems", Json::arrayValue, mealItems ) )
   {
      for( auto item: mealItems )
      {
         MainCourse mealItem;
         string dishName;
         MainCourseBuilder builder{ mealItem, *this };
         if ( true == checkAndRetriveJsonData( 
                  item, "dishName", Json::stringValue, dishName ) )
         {
            builder.setName( dishName );
            Json::Value sideCategory(Json::arrayValue );
            if( ( true == checkAndRetriveJsonData( 
                        item, "eatWith", Json::arrayValue, sideCategory ) ) &&
                  ( 0 != sideCategory.size() ) )
            {
               for( auto side: sideCategory )
               {
                  builder.eatWith( side.asString() );
               }
            }
            Json::Value recipeGrp;
            if ( true == checkAndRetriveJsonData( item, "recipeGroup", Json::arrayValue,  recipeGrp ) )
            {
               for( auto recipeGrpItem: recipeGrp )
               {
                  builder.addRecipeGrp( recipeGrpItem.asString() );
               }
            }
            Json::Value ingredients( Json::arrayValue );
            if (true == checkAndRetriveJsonData( 
                  item, "ingredients", Json::arrayValue, ingredients ) )
            {
               for( auto ingredient: ingredients )
               {
                  builder.addIngredient( ingredient.asString() );
               }
            }
            string mealCategory;
            (void)checkAndRetriveJsonData( item, "category", 
                     Json::stringValue, mealCategory );
            builder.setMealCategory( mealCategory );
         }
         mMainCourseItems.push_back( builder );
      }
   }
   return ;/*void*/
}

/*..............................................................................
 * @brief populateSides
 *
 * Input Parameters:
 *    @param: 
 *        Json::Val
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CMealDB::populateSides ( const Json::Value& jsonDB )
{
   
   Json::Value jsonSides;
   if ( true == checkAndRetriveJsonData( jsonDB, "sides", Json::arrayValue, jsonSides ) )
   {
      for( auto side: jsonSides )
      {
         SideDish mealItem;
         SideDishBuilder builder{ mealItem, *this };
         string dishName;
         if ( true == checkAndRetriveJsonData( 
                  side, "dishName", Json::stringValue, dishName ) )
         {
            builder.setName( dishName );
            Json::Value recipeGrp;
            if ( true == checkAndRetriveJsonData( side, "recipeGroup", Json::arrayValue,  recipeGrp ) )
            {
               for( auto recipeGrpItem: recipeGrp )
               {
                  builder.addRecipeGrp( recipeGrpItem.asString() );
               }
            }
            Json::Value categories;
            if ( true == checkAndRetriveJsonData( 
                     side, "category", Json::arrayValue, categories ) )
            {
               for( auto cat : categories )
               {
                  /*
                   * @todo : build tag database here
                   */
                  //sideFromDB.mCategories.push_back( cat.asString() );
               }
            }
            Json::Value ingredients( Json::arrayValue );
            if (true == checkAndRetriveJsonData( 
                  side, "ingredients", Json::arrayValue, ingredients ) )
            {
               for( auto ingredient: ingredients )
               {
                  builder.addIngredient( ingredient.asString() );
               }
            }
            mSideDishes.push_back( builder );
         }
      }
   }
   return ;/*void*/
}
/*..............................................................................
 * @brief CMealDB
 *
 * Input Parameters:
 *    @param: 
 *        Json::Value& jsonDB
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
CMealDB::CMealDB ( const Json::Value& jsonDB )
{
   // populate recipe groups
   populateRecipeGroups( jsonDB );

   // populate Meal items
   populateMealItems( jsonDB );

   // populate Sides
   populateSides( jsonDB );
}

/*..............................................................................
 * @brief getRecipeGroups
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns vector< RecipeGroup >
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
vector< RecipeGroup > CMealDB::getRecipeGroups (  ) const
{
   return mRecipeGroups;/*vector< RecipeGroup >*/
}

