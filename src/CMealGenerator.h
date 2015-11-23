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
   protected:

   public:
      CMealGenerator( ) = delete ;
      CMealGenerator( const CMealDB& );
      virtual ~CMealGenerator( );
      bool generateRandomMeal( Meal& randomMeal, tenMealCategory cat  ) const;
      unsigned int getNrOfDishesByCat( const tenMealCategory& ) const;
};

