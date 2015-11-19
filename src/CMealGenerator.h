#include "CMealDB.h"
#include <set>
using namespace std;

typedef struct _meal
{
   string mRecipeName;
   string mSide;
   set< string > mIngredients;
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
      bool generateRandomMeal( Meal& randomMeal, tenMealCategory cat  );
};
