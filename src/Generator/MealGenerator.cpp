#include "MealGenerator.h"
#include <algorithm>
#include <random>
#include <vector>
#include <functional>
#include "assert.h"
#include <iostream>

template <typename T>
T getRandIterator( T begin, T end )
{
   if(begin == end){
      return end;
   }
   std::random_device rand;
   std::mt19937_64 gen( rand() );

   std::uniform_int_distribution<> intDist( 0, std::distance(begin, end) -1 );
   std::advance( begin, intDist( gen ) );
   return begin;
}

template <typename T, typename U>
T getWeightedRandIterator( T begin, T end, U weightsBegin, U weightsEnd )
{
   if( std::distance( begin, end ) != std::distance( weightsBegin, weightsEnd ))
   {
      assert( 0 );
   }
   std::random_device rand;
   std::mt19937_64 gen( rand() );

   std::discrete_distribution<> weightedDist{ weightsBegin, weightsEnd };
   std::advance( begin, weightedDist( gen ));
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

   if(sideDish != end(sideDishes)){
      randomMeal.mRecipeName += " with " + sideDish->getName();

      randomMeal.mIngredients.insert(begin( sideDish->getIngredients()), 
                                     end(sideDish->getIngredients()));
   }
   else{
      success = false;
   }

   return success;/*bool*/
}

bool MealGenerator::addAccompaniment ( Meal& randomMeal, const vector<string>& cat )const
{
   bool success = true;

   auto it = getRandIterator( begin( cat ), end( cat ) );

   auto sideDishes = mMealDatabase.sideDishDB().lookup( *it );
   auto sideDish = getRandIterator( begin( sideDishes ), end( sideDishes) );

   if(sideDish != end(sideDishes)){
      randomMeal.mRecipeName += " and " + sideDish->getName();

      randomMeal.mIngredients.insert(begin( sideDish->getIngredients()), 
                                     end(sideDish->getIngredients()));
   }
   else{
      success = false;
   }
   return success;/*bool*/
}

/*..............................................................................
 * @brief getWeights
 *
 * Input Parameters:
 *    @param: vector<MainCourse>::
 *        beginvector<MainCourse>::ite
 * Return Value:
 *    @returns initializer_list<double>
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
vector<double> MealGenerator::getWeights ( vector<MainCourse>::iterator first,
     vector<MainCourse>::iterator last)const
{
   vector<double> weights;
   for( auto it = first; it < last ; ++it )
   {
      double weight = 0;
      if( true == it->needsSide() )
      {
         auto canBeEatenWith = it->canBeEatenWith();
         const auto& tagDB =  mMealDatabase.sideDishDB();
         auto nrOfAccompaniments = 1;
         if(it->hasAccompaniments()){
            nrOfAccompaniments = 0;
            for(auto&& item: it->getAccompaniments()){
               nrOfAccompaniments = tagDB.lookup(item).size();
            }
            nrOfAccompaniments = nrOfAccompaniments == 0? 1: nrOfAccompaniments;
         }
         for_each( begin( canBeEatenWith ), end( canBeEatenWith ),
                   [&tagDB, &weight, nrOfAccompaniments ]( const string& tag ){
                      weight += (tagDB.lookup( tag ).size())*nrOfAccompaniments;
                   });
         weights.push_back( weight );
      }
      else
      {
         weights.push_back( 1 );
      }
   }
   
   return weights;/*initializer_list<double>*/
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

      auto weights = getWeights( begin( mainCourseItems ), it );
      it = getWeightedRandIterator( begin( mainCourseItems), it, 
           begin( weights ), end( weights ) );

      randomMeal.mRecipeName = it->getName();
      randomMeal.mIngredients = it->getIngredients();
      if ( it->needsSide() )
      {
         success = addSideDish( randomMeal, it->canBeEatenWith() );
         if(success && it->hasAccompaniments()){
            success = addAccompaniment(randomMeal, it->getAccompaniments());
         }
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
      int nrOfAccompaniments = 1;
      if(mealItem.hasAccompaniments()){
         nrOfAccompaniments = 0;
         auto accompaniments = mealItem.getAccompaniments();
         for( auto && accompaniment: mealItem.getAccompaniments()){
            auto items = tagDB.lookup(accompaniment);
            nrOfAccompaniments+=items.size();
         }
         nrOfAccompaniments = nrOfAccompaniments == 0? 1: nrOfAccompaniments;
      }
      for(auto&& item: canBeEatenWith){
         auto items = tagDB.lookup(item);
         nrOfDishes += (items.size()*nrOfAccompaniments);
      }
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

