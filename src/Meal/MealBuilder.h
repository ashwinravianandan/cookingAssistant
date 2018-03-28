#pragma once
#include <vector>
#include <unordered_set>
#include "Meal.h"
#include "MealDB.h"

using namespace std;

class MainCourseBuilder
{
   private:
      MainCourse& mMealItem;
      const MealDB & mMealDB;

   protected:

   public:
      explicit MainCourseBuilder( MainCourse& mealItem ,  const MealDB & mealDB);
      MainCourseBuilder& setName( const string& name );
      MainCourseBuilder& addRecipeGrp( const string& grpName );
      MainCourseBuilder& addIngredient( const string& ingredient );
      MainCourseBuilder& addIngredients( const unordered_set<string>& ingredient );
      MainCourseBuilder& eatWith( const string& eatWith );
      MainCourseBuilder& setMealCategory( const string& mealCategory );
      MainCourseBuilder& withSecondarySide();

      operator MainCourse()
      {
         return std::move( mMealItem );
      }
      virtual ~MainCourseBuilder( ){}
};

class SideDishBuilder
{
   private:
      SideDish& mMealItem;
      const MealDB & mMealDB;

   protected:

   public:
      explicit SideDishBuilder( SideDish& mealItem ,  const MealDB & mealDB);
      SideDishBuilder& setName( const string& name );
      SideDishBuilder& addRecipeGrp( const string& grpName );
      SideDishBuilder& addIngredient( const string& ingredient );
      SideDishBuilder& addIngredients( const unordered_set<string>& ingredient );
      SideDishBuilder& eatWith( const string& eatWith );
      SideDishBuilder& setMealCategory( const string& mealCategory );

      operator SideDish()
      {
         return std::move( mMealItem );
      }
      virtual ~SideDishBuilder( ){}
};
