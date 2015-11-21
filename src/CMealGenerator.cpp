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
 *    @returns Meal
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool CMealGenerator::generateRandomMeal( Meal& randomMeal, tenMealCategory cat  )const
{
   bool success = false;
   vector< MealItem >::iterator randomMealItem;
   vector< MealItem > mealItems = mMealDatabase.getMealItems();

   auto partitionBasedOnCategory = [ cat ]( MealItem mealFromDB ) -> bool
   {
      if ( mealFromDB.mMealCategory == cat )
      {
         return true;
      }
      else
      {
         return false;
      }
   };

   auto it = std::partition( begin( mealItems ), end( mealItems ),partitionBasedOnCategory );

   if( it != begin( mealItems ) )
   {
      randomMealItem = getRandIterator( begin( mealItems ), it );
      success = true;
   }

   if ( true == success )
   {
      randomMeal.mRecipeName = randomMealItem->mDishName;
      randomMeal.mIngredients.insert( begin( randomMealItem->mIngredients ), 
            end( randomMealItem->mIngredients ) );

      std::for_each( randomMealItem->mRecipeGroups.begin(), 
            randomMealItem->mRecipeGroups.end(),
            [ & ]( string recipeGrp )
            {
            auto recipeGrps = mMealDatabase.getRecipeGroups();
            auto it = find_if( begin( recipeGrps ), end( recipeGrps ),
                  [=]( RecipeGroup rg ) { return ( rg.mGroupName == recipeGrp ); } ) ;
            if( it != end( recipeGrps ) )
            {
            randomMeal.mIngredients.insert(it->mIngredients.begin(), it->mIngredients.end() );
            }
            }
            );

      if ( true == randomMealItem->mNeedsSide )
      {
         success = false;
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
            success = true;
            randSide = getRandIterator( begin( sidesFromDB ), it );
            randomMeal.mSide = randSide->mDishName;
            randomMeal.mIngredients.insert( begin( randSide->mIngredients ), end( randSide->mIngredients ) );
            std::for_each( begin( randSide->mRecipeGroups ), 
                  end( randSide->mRecipeGroups ),
                  [ & ]( string recipeGrp )
                  {
                  auto recipeGrps = mMealDatabase.getRecipeGroups();
                  auto it = find_if( begin( recipeGrps ), end( recipeGrps ),
                        [=]( RecipeGroup rg ) { return ( rg.mGroupName == recipeGrp ); } ) ;
                  if( it != end( recipeGrps ) )
                  {
                  randomMeal.mIngredients.insert( it->mIngredients.begin(), it->mIngredients.end() );
                  }
                  }
                  );

         }
      }
   }
   return success;/*Meal*/
}

/*..............................................................................
 * @brief getNrOfDishesByCat
 *
 * Input Parameters:
 *    @param: 
 *        tenMealCategory& cat
 * Return Value:
 *    @returns unsigned int
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
unsigned int CMealGenerator::getNrOfDishesByCat ( const tenMealCategory& cat )const
{
   unsigned int nrOfDishes = 0;
   auto mealItems = mMealDatabase.getMealItems();
   auto sides = mMealDatabase.getSides();

   auto countMeals = [ &nrOfDishes, sides, cat ]( MealItem meal )
   {
      if(  cat == meal.mMealCategory )
      {
         if( false == meal.mNeedsSide )
         {
            ++ nrOfDishes;
         } 
         else
         {
            string sideCat = meal.mSideCategory;
            for_each( begin( sides ), end( sides ), [&nrOfDishes, sideCat]( Sides side)
                  {
                     if( end( side.mCategories ) != find_if( begin( side.mCategories ),
                              end( side.mCategories ), [ &nrOfDishes, sideCat ]( string sideCategory )
                              { return sideCategory == sideCat; }) )
                     {
                        ++nrOfDishes;
                     }
                  } );
         }
      }
   };

   for_each( begin( mealItems ), end( mealItems ), countMeals );

   return nrOfDishes;/*unsigned int*/
}

