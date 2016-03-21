#include "CListGenerator.h"
#include <algorithm>
using namespace std;

/*..............................................................................
 * @brief CListGenerator
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 CListGenerator::CListGenerator (  )
{
}

/*..............................................................................
 * @brief ~CListGenerator
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 CListGenerator::~CListGenerator (  )
{
}

/*..............................................................................
 * @brief CListGenerator
 *
 * Input Parameters:
 *    @param: 
 *        set< pair< string,int>>& listOpts
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
CListGenerator::CListGenerator ( const set< pair< string,
      unsigned int >>& listOpts )
{
   mListOptions = listOpts;
}

/*..............................................................................
 * @brief addListCriteria
 *
 * Input Parameters:
 *    @param: 
 *        std::pair< string, 
 *        int>& listOpt
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CListGenerator::addListCriteria ( const std::pair< string,
      unsigned int>& listOpt )
{
   mListOptions.insert( listOpt );
}

/*..............................................................................
 * @brief addListCriteria
 *
 * Input Parameters:
 *    @param: 
 *        set< pair< string, 
 *        int>> listOpts
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CListGenerator::addListCriteria ( const set< pair< string,
      unsigned int>>& listOpts )
{
   mListOptions.insert( begin( listOpts ), end( listOpts ) );
}

/*..............................................................................
 * @brief generateMenu
 *
 * Input Parameters:
 *    @param: 
 *        CMealGenerator& mealGen
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool CListGenerator::generateMenu ( const CMealGenerator& mealGen )
{
   bool success = true;
   for( auto crit: mListOptions )
   {
      if( 0 == crit.second )
      {
         continue;
      }
      unsigned int numberOfDishes = mealGen.getNrOfDishesByCat( crit.first );
      if( 0 == numberOfDishes )
      {
         success = false;
      }
      else
      {
         bool uniqueMenu = ( ( numberOfDishes != 0 ) &&
               ( numberOfDishes >= crit.second ) )? true : false;
         unsigned int count = crit.second;
         do
         {
            Meal randomMeal;
            if( mealGen.generateRandomMeal( randomMeal, crit.first ) )
            {
               if( uniqueMenu )
               {
                  auto it = std::find( begin( mMealMenu ), end( mMealMenu ), 
                        std::make_pair( randomMeal.mRecipeName, randomMeal.mSide ) );
                  if ( end( mMealMenu ) == it )
                  {
                     mMealMenu.push_back( std::make_pair( randomMeal.mRecipeName, randomMeal.mSide ) );
                     mIngredients.insert( begin( randomMeal.mIngredients ), end( randomMeal.mIngredients ) );
                     --count;
                  }
               }
               else
               {
                  mMealMenu.push_back( std::make_pair( randomMeal.mRecipeName, randomMeal.mSide ) );
                  mIngredients.insert( begin( randomMeal.mIngredients ), end( randomMeal.mIngredients ) );
                  --count;
               }
            }
         }while( count > 0 );
      }
   }
   return success;/*bool*/
}

/*..............................................................................
 * @brief exportMenu
 *
 * Input Parameters:
 *    @param: ostream& outFile
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CListGenerator::exportMenu ( ostream& outFile )const
{
   outFile<<"\n-----MENU-----\n";
   for( auto mealItem : mMealMenu )
   {
      outFile<<"\t "<<mealItem.first.c_str();
      if( "" != mealItem.second )
      {
         outFile<<" - "<<mealItem.second.c_str()<<"\n";
      }
      else
      {
         outFile<<endl;
      }
   } 
}

/*..............................................................................
 * @brief exportGroceryList
 *
 * Input Parameters:
 *    @param: ostream& outFile
 * Return Value:
 *    @returns void
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
void CListGenerator::exportGroceryList ( ostream& outFile )const
{
   outFile<<"\n-----GROCERY-LIST-----\n";
   for( auto ingredient : mIngredients )
   {
      outFile<<"\t* "<<ingredient.c_str()<<"\n";
   }
}

