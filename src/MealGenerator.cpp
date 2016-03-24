#include "MealGenerator.h"
#include <algorithm>
#include <random>
#include <vector>
#include <functional>

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
 * @brief MealGenerator
 *
 * Input Parameters:
 *    @param: 
 *        MealDB& mealDB
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MealGenerator::MealGenerator ( const MealDB& mealDB ): mMealDatabase( mealDB )
{
}

/*..............................................................................
 * @brief ~MealGenerator
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MealGenerator::~MealGenerator (  )
{
}

/*..............................................................................
 * @brief addSideDish
 *
 * Input Parameters:
 *    @param: Meal& randomMeal, 
 *        vector<string>& cat
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool MealGenerator::addSideDish ( Meal& randomMeal, const vector<string>& cat )const
{
   bool success = true;

   auto it = getRandIterator( begin( cat ), end( cat ) );

   auto sideDishes = mMealDatabase.sideDishDB().lookup( *it );
   auto sideDish = getRandIterator( begin( sideDishes ), end( sideDishes) );

   randomMeal.mRecipeName += " with " + sideDish->getName();

   randomMeal.mIngredients.insert(begin( sideDish->getIngredients()), 
         end(sideDish->getIngredients()));

   return success;/*bool*/
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
bool MealGenerator::generateRandomMeal( Meal& randomMeal, string cat  )const
{
   bool success = false;
   do
   {
      vector<MainCourse> mainCourseItems;
      mMealDatabase.getMainCourseItems( mainCourseItems );

      auto it = std::partition( begin( mainCourseItems ), end( mainCourseItems ),
            [ cat ]( const MainCourse& mainCourse ){ return mainCourse.getCategory() == cat ;});

      if( begin( mainCourseItems ) == it )
         break;

      it = getRandIterator( begin( mainCourseItems), it );
      randomMeal.mRecipeName = it->getName();
      randomMeal.mIngredients = it->getIngredients();
      if ( it->needsSide() )
      {
         success = addSideDish( randomMeal, it->canBeEatenWith() );
      }
      else
      {
         success = true;
      }
   }
   while( 0 );

   return success;
}

/*..............................................................................
 * @brief countMeals
 *
 * Input Parameters:
 *    @param: 
 *        int& nrOfDishes,
     
 *        stringcategory
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void MealGenerator::countMeals ( unsigned int& nrOfDishes , const MainCourse& mealItem )const
{
   if ( mealItem.needsSide() )
   {
      auto canBeEatenWith = mealItem.canBeEatenWith();
      const SideDishTagDatabase& tagDB = mMealDatabase.sideDishDB();
      for_each( begin( canBeEatenWith ), end( canBeEatenWith ), [&nrOfDishes, &tagDB]( const string& tag )
            {
               auto items = tagDB.lookup( tag );
               nrOfDishes += items.size();
            });
   }
   else
   {
      nrOfDishes++;
   }
}
/*..............................................................................
 * @brief getNrOfDishesByCat
 *
 * Input Parameters:
 *    @param: 
 *        string& cat
 * Return Value:
 *    @returns unsigned int
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
unsigned int MealGenerator::getNrOfDishesByCat ( const string& category )const
{
   unsigned int nrOfDishes = 0;
   using namespace std::placeholders;
   vector<MainCourse> mainCourseItems;
   mMealDatabase.getMainCourseItems( mainCourseItems );

   auto it = std::partition( begin( mainCourseItems) , end( mainCourseItems),
         [ category ](const MainCourse& item ){ return item.getCategory() == category;});

   auto cntMeals = std::bind( &MealGenerator::countMeals, this, std::ref(nrOfDishes), _1 );

   for_each( begin( mainCourseItems ), it , cntMeals );

   return nrOfDishes;/*unsigned int*/
}

