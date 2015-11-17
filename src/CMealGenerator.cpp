#include "CMealGenerator.h"
#include <algorithm>
#include <random>
#include <vector>

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
 * @brief CMealGenerator
 *
 * Input Parameters:
 *    @param: 
 *        CMealDB& mealDB
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
CMealGenerator::CMealGenerator ( const CMealDB& mealDB ): mMealDatabase( mealDB )
{
}

/*..............................................................................
 * @brief ~CMealGenerator
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
CMealGenerator::~CMealGenerator (  )
{
}

/*..............................................................................
 * @brief generateRandomMeal
 *
 * Input Parameters:
 *    @param: cat
 * Return Value:
 *    @returns meal
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
meal CMealGenerator::generateRandomMeal( tenMealCategory cat  )
{
   /**
    * @todo: refactor method to return error and implement 
    * random iterator for rice based items 
    */
   bool success = false;
   meal randomMeal;
   vector< MealItem >::iterator randomMealItem;
   if ( enBread == cat )
   {
      /**
       * @todo: look for side category Chapathi 
       */
      vector< MealItem > mealItems = mMealDatabase.getMealItems();

      vector< MealItem >::iterator it = std::partition( 
            begin( mealItems ), end( mealItems ), []( MealItem mealFromDB ) 
            { if( mealFromDB.mSideCategory == "withChapathi"  || mealFromDB.mSideCategory == "" ) 
            return true; else return false; } );

      if( it != begin( mealItems ) )
      {
         randomMealItem = getRandIterator( begin( mealItems ), it );
         success = true;
      }
   }
   else if ( enRice == cat )
   {
   }
   else
   {
      ;
   }
   if ( true == success )
   {
      randomMeal.mRecipeName = randomMealItem->mDishName;
      randomMeal.mIngredients = randomMealItem->mIngredients;
      std::for_each( randomMealItem->mRecipeGroups.begin(), 
            randomMealItem->mRecipeGroups.end(),
            [ & ]( string recipeGrp )
            {
            auto recipeGrps = mMealDatabase.getRecipeGroups();
            auto it = find_if( begin( recipeGrps ), end( recipeGrps ),
                  [=]( RecipeGroup rg ) { return ( rg.mGroupName == recipeGrp ); } ) ;
            if( it != end( recipeGrps ) )
            {
            randomMeal.mIngredients.reserve( randomMeal.mIngredients.size() + it->mIngredients.size() );
            randomMeal.mIngredients.insert( randomMeal.mIngredients.end(),
                  it->mIngredients.begin(), it->mIngredients.end() );
            }
            }
            );

      if ( true == randomMealItem->mNeedsSide )
      {
         vector< Sides >::iterator randSide;
         string sideCat = randomMealItem->mSideCategory;
         vector< Sides > sidesFromDB = mMealDatabase.getSides();
         vector< Sides >::iterator it = std::partition( begin( sidesFromDB ), end( sidesFromDB ), 
               [ = ] ( Sides fromDB ) -> bool
               { if ( fromDB.mCategories.end() != std::find( fromDB.mIngredients.begin(), 
                        fromDB.mIngredients.end(), randomMealItem->mSideCategory ) )
               return true; else return false;
               }
               );
         if( begin( sidesFromDB ) != it )
         {
            randSide = getRandIterator( begin( sidesFromDB ), it );
         }
      }
   }

   return randomMeal;/*meal*/
}

