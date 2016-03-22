#pragma once
#include "CMealDB.h"
#include "CMealGenerator.h"
#include <set>
using namespace std;

class CListGenerator final
{
   private:
      std::set< std::pair< string, unsigned int > > mListOptions;
      std::vector< std::pair< string , string > > mMealMenu;
      std::unordered_set< std::string > mIngredients;
   protected:

   public:
      CListGenerator( );
      CListGenerator( const std::set< std::pair< string, unsigned int > >& );
      virtual ~CListGenerator( );
      void addListCriteria( const std::pair< string, unsigned int >& );
      void addListCriteria( const std::set< std::pair< string, unsigned int > >& );
      bool generateMenu( const CMealGenerator& );
      const std::vector< pair<string, string>>& getMealMenu( void )const;
      const std::unordered_set<string>& getGroceryList( void )const;
};
