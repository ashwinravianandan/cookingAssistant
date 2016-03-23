#pragma once
#include "CMealDB.h"
#include <unordered_set>
using namespace std;

typedef struct _meal
{
   string mRecipeName;
   string mSide;
   unordered_set< string > mIngredients;
}Meal;

class CMealGenerator final
{
   private:
      CMealDB mMealDatabase;
      bool addSideDish ( Meal& randomMeal, const vector<string>& cat )const;
      void countMeals ( unsigned int& nrOfDishes , const MainCourse& mealItem )const;
   protected:

   public:
      CMealGenerator( ) = delete ;
      CMealGenerator( const CMealDB& );
      virtual ~CMealGenerator( );
      bool generateRandomMeal( Meal& randomMeal, string cat  ) const;
      unsigned int getNrOfDishesByCat( const string& ) const;
};

