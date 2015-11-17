#include "CMealDB.h"

typedef struct _meal
{
   string mRecipeName;
   vector< string > mIngredients;
}meal;

enum class tenMealCategory
{
   BREAD,
   RICE
};

class CMealGenerator final
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
