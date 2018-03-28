#include <algorithm>
#include "MealBuilder.h"

/*..............................................................................
 * @brief MainCourseBuilder
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MainCourseBuilder::MainCourseBuilder ( MainCourse& mealItem, const MealDB& mealDB):
   mMealItem( mealItem ), mMealDB( mealDB )
{
}

/*..............................................................................
 * @brief setName
 *
 * Input Parameters:
 *    @param: 
 *        string& name
 * Return Value:
 *    @returns MainCourseBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MainCourseBuilder& MainCourseBuilder::setName ( const string& name )
{
   mMealItem.mName = name;
   return *this;/*MainCourseBuilder&*/
}

/*..............................................................................
 * @brief addRecipeGrp
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns MainCourseBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MainCourseBuilder& MainCourseBuilder::addRecipeGrp( const string& recipeGrp )
{
   auto recipeGroups = mMealDB.getRecipeGroups();
   auto it = std::find_if( begin( recipeGroups ), end( recipeGroups ),
         [ recipeGrp ]( RecipeGroup grp ) { return ( recipeGrp == grp.mGroupName );});

   if ( end ( recipeGroups ) != it)
   {
      for( auto& ingredient : it->mIngredients )
      {
         mMealItem.mIngredients.insert( ingredient );
      }
   }
   return *this;
}

/*..............................................................................
 * @brief addIngredient
 *
 * Input Parameters:
 *    @param: 
 *        string& ingredient
 * Return Value:
 *    @returns MainCourseBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MainCourseBuilder& MainCourseBuilder::addIngredient ( const string& ingredient )
{
   mMealItem.mIngredients.insert( ingredient );
   return *this;/*MainCourseBuilder&*/
}

/*..............................................................................
 * @brief addIngredients
 *
 * Input Parameters:
 *    @param: 
 *        string& ingredient
 * Return Value:
 *    @returns MainCourseBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MainCourseBuilder& MainCourseBuilder::addIngredients ( const unordered_set<string>& ingredients )
{
   for( auto& ingredient : ingredients )
   {
      mMealItem.mIngredients.insert( ingredient );
   }
   return *this;/*MainCourseBuilder&*/
}

/*..............................................................................
 * @brief eatWith
 *
 * Input Parameters:
 *    @param: 
 *        string& eatWith
 * Return Value:
 *    @returns MainCourseBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MainCourseBuilder& MainCourseBuilder::eatWith ( const string& eatWith )
{
   mMealItem.mEatWith.push_back( eatWith );
   return *this;/*MainCourseBuilder&*/
}

/*..............................................................................
 * @brief add
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns MainCourseBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MainCourseBuilder& MainCourseBuilder::setMealCategory (const string& mealCategory )
{
   mMealItem.mMealCategory = mealCategory;
   return *this;/*MainCourseBuilder&*/
}

MainCourseBuilder& MainCourseBuilder::withSecondarySide()
{
   mMealItem.mSecondarySide = true;
}

//-------------------------------------------------------------------------------------------------------
/*..............................................................................
 * @brief SideDishBuilder
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
SideDishBuilder::SideDishBuilder ( SideDish& mealItem, const MealDB& mealDB):
   mMealItem( mealItem ), mMealDB( mealDB )
{
}

/*..............................................................................
 * @brief setName
 *
 * Input Parameters:
 *    @param: 
 *        string& name
 * Return Value:
 *    @returns SideDishBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
SideDishBuilder& SideDishBuilder::setName ( const string& name )
{
   mMealItem.mName = name;
   return *this;/*SideDishBuilder&*/
}

/*..............................................................................
 * @brief addRecipeGrp
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns SideDishBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
SideDishBuilder& SideDishBuilder::addRecipeGrp( const string& recipeGrp )
{
   auto recipeGroups = mMealDB.getRecipeGroups();
   auto it = std::find_if( begin( recipeGroups ), end( recipeGroups ),
         [ recipeGrp ]( RecipeGroup grp ) { return ( recipeGrp == grp.mGroupName );});

   if ( end ( recipeGroups ) != it)
   {
      for( auto& ingredient : it->mIngredients )
      {
         mMealItem.mIngredients.insert( ingredient );
      }
   }
   return *this;
}

/*..............................................................................
 * @brief addIngredient
 *
 * Input Parameters:
 *    @param: 
 *        string& ingredient
 * Return Value:
 *    @returns SideDishBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
SideDishBuilder& SideDishBuilder::addIngredient ( const string& ingredient )
{
   mMealItem.mIngredients.insert( ingredient );
   return *this;/*SideDishBuilder&*/
}

/*..............................................................................
 * @brief addIngredients
 *
 * Input Parameters:
 *    @param: 
 *        string& ingredient
 * Return Value:
 *    @returns SideDishBuilder&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
SideDishBuilder& SideDishBuilder::addIngredients ( const unordered_set<string>& ingredients )
{
   for( auto& ingredient : ingredients )
   {
      mMealItem.mIngredients.insert( ingredient );
   }
   return *this;/*SideDishBuilder&*/
}

