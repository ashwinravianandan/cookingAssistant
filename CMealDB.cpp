#include "CMealDB.h"
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
      recipeGroup grpFromDB;
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
         mealItem itemsFromDB;
         if ( true == checkAndRetriveJsonData( 
                  item, "dishName", Json::stringValue, itemsFromDB.mDishName ) )
         {
            Json::Value sideCategory;
            if( true == checkAndRetriveJsonData( 
                     item, "eatWith", Json::objectValue, sideCategory ) &&
             true == checkAndRetriveJsonData( 
                sideCategory, "category", Json::stringValue, itemsFromDB.mSideCategory ) )
            {
               itemsFromDB.mNeedsSide = true;
            }
            else
            {
               itemsFromDB.mNeedsSide = false;
            }
         }
         Json::Value recipeGrp;
         if ( true == checkAndRetriveJsonData( item, "recipeGroup", Json::arrayValue,  recipeGrp ) )
         {
            for( auto recipeGrpItem: recipeGrp )
            {
               itemsFromDB.mRecipeGroups.push_back( recipeGrpItem.asString() );
            }
         }
         Json::Value ingredients( Json::arrayValue );
         if (true == checkAndRetriveJsonData( 
               item, "ingredients", Json::arrayValue, ingredients ) )
         {
            for( auto ingredient: ingredients )
            {
               itemsFromDB.mIngredients.push_back( ingredient.asString() );
            }
         }
         mMealItems.push_back( itemsFromDB );
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
      sides sideFromDB;
      for( auto side: jsonSides )
      {
         if ( true == checkAndRetriveJsonData( 
                  side, "dishName", Json::stringValue, sideFromDB.mDishName ) )
         {
            Json::Value recipeGrp;
            if ( true == checkAndRetriveJsonData( side, "recipeGroup", Json::arrayValue,  recipeGrp ) )
            {
               for( auto recipeGrpItem: recipeGrp )
               {
                  sideFromDB.mRecipeGroups.push_back( recipeGrpItem.asString() );
               }
            }
            Json::Value categories;
            if ( true == checkAndRetriveJsonData( 
                     side, "category", Json::arrayValue, categories ) )
            {
               for( auto cat : categories )
               {
                  sideFromDB.mCategories.push_back( cat.asString() );
               }
            }
            Json::Value ingredients( Json::arrayValue );
            if (true == checkAndRetriveJsonData( 
                  side, "ingredients", Json::arrayValue, ingredients ) )
            {
               for( auto ingredient: ingredients )
               {
                  sideFromDB.mIngredients.push_back( ingredient.asString() );
               }
            }
            mSideDishes.push_back( sideFromDB );
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

   // populate meal items
   populateMealItems( jsonDB );

   // populate sides
   populateSides( jsonDB );
}

/*..............................................................................
 * @brief getSides
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns vector< sides > 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
vector< sides > CMealDB::getSides (  ) const
{
   return mSideDishes;/*vector< sides > CMealDB*/
}

/*..............................................................................
 * @brief getMealItems
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns vector< mealItem >
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
vector< mealItem > CMealDB::getMealItems (  ) const
{
   return mMealItems;/*vector< mealItem >*/
}

/*..............................................................................
 * @brief getRecipeGroups
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns vector< recipeGroup >
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
vector< recipeGroup > CMealDB::getRecipeGroups (  ) const
{
   return mRecipeGroups;/*vector< recipeGroup >*/
}
