#pragma once
#include "MealDB.h"
#include <unordered_set>
using namespace std;

typedef struct _meal
{
   string mRecipeName;
   string mSide;
   unordered_set< string > mIngredients;
}Meal;

class MealGenerator final
{
   private:
      MealDB mMealDatabase;
      bool addSideDish ( Meal& randomMeal, const vector<string>& cat )const;
      bool addAccompaniment ( Meal& randomMeal, const vector<string>& cat )const;
      void countMeals ( unsigned int& nrOfDishes , const MainCourse& mealItem )const;
      vector<double> getWeights ( 
            vector<MainCourse>::iterator begin, vector<MainCourse>::iterator end)const;
   protected:

   public:
      MealGenerator( ) = delete ;
      MealGenerator( const MealDB& );
      virtual ~MealGenerator( );
      bool generateRandomMeal( Meal& randomMeal, string cat  ) const;
      unsigned int getNrOfDishesByCat( const string& ) const;
};

