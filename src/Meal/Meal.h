#pragma once

#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

enum class MealType { MainCourse, Side, Desert, Salad };

class MealItem
{
   protected:
   string mName;
   unordered_set<string> mIngredients;
   bool mSecondarySide;

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
      using MealItem::MealItem;
      virtual bool needsSide( void )const override;
      string getCategory( )const;
      vector<string> canBeEatenWith()const;
      virtual ~MainCourse( );
};

class SideDish : public MealItem
{
   friend class SideDishBuilder;
   private:

   protected:

   public:
      using MealItem::MealItem;
      virtual ~SideDish( );
      virtual bool needsSide( void )const override;
};

