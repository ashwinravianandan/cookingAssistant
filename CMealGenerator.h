#include "CMealDB.h"

typedef struct _meal
{
   string mRecipeName;
   vector< string > mIngredients;
}meal;

typedef enum _mealCategory
{
   enBread,
   enRice
} tenMealCategory;

class CMealGenerator
{
   private:
      CMealDB mMealDatabase;
   protected:

   public:
      CMealGenerator( ) = delete ;
      CMealGenerator( const CMealDB& );
      virtual ~CMealGenerator( );
      meal generateRandomMeal( tenMealCategory );
};
