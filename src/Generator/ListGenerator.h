#pragma once
#include "MealDB.h"
#include "MealGenerator.h"
#include <set>
using namespace std;

class ListGenerator final
{
   private:
      std::set< std::pair< string, unsigned int > > mListOptions;
      std::vector< std::pair< string , string > > mMealMenu;
      std::unordered_set< std::string > mIngredients;
   protected:

   public:
      ListGenerator( );
      ListGenerator( const std::set< std::pair< string, unsigned int > >& );
      virtual ~ListGenerator( );
      void addListCriteria( const std::pair< string, unsigned int >& );
      void addListCriteria( const std::set< std::pair< string, unsigned int > >& );
      bool generateMenu( const MealGenerator& );
      const std::vector< pair<string, string>>& getMealMenu( void )const;
      const std::unordered_set<string>& getGroceryList( void )const;
};
