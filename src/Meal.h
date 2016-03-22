#pragma once

#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class MealItem
{
   enum class MealType { MainCourse, Side, Desert, Salad };
   private:
   string mName;
   unordered_set<string> mIngredients;

   public:
   MealItem() = default;
   explicit MealItem( string name, unordered_set<string> ingredients );
   virtual bool needsSide( void )const = 0;
   string getName( void )const;
   const unordered_set<string>& getIngredients(void) const;
   virtual ~MealItem( );
};

class MainCourse: public MealItem
{
   friend class MainCourseBuilder;

   private:
      vector<string> mEatWith;
      string mMealCategory; // Main course items define the main category for list generation

   protected:

   public:
      MainCourse() = default;
      using MealItem::MealItem;
      void setMealCategory( const string& mealCategory );
      void setEatWithCategory( const vector<string>& eatWith );
      virtual bool needsSide( void )const override;
      virtual ~MainCourse( );
};

class SideDish : public MealItem
{
   friend class SideDishBuilder;
   private:

   protected:

   public:
      SideDish() = default;
      using MealItem::MealItem;
      explicit SideDish( string name, unordered_set<string> ingredients, vector<string> categories);
      virtual ~SideDish( );
      virtual bool needsSide( void )const override;
};

