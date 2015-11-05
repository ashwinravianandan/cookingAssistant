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
   
   meal randomMeal;
   vector< mealItem >::iterator randomMealItem;
   if ( enBread == cat )
   {
      /**
       * @todo: look for side category Chapathi 
       */
      vector< mealItem > mealItems = mMealDatabase.getMealItems();

      vector< mealItem >::iterator it = std::partition( 
            begin( mealItems ), end( mealItems ), []( mealItem mealFromDB ) 
            { if( mealFromDB.mSideCategory == "withChapathi"  || mealFromDB.mSideCategory == "" ) 
            return true; else return false; } );

      if( it != begin( mealItems ) )
      {
         randomMealItem = getRandIterator( begin( mealItems ), it );
      }
   }
   else if ( enRice == cat )
   {
      /**
       * @todo: look for side category rice
       */
   }
   else
   {
      ;
   }

   return randomMeal;/*meal*/
}

