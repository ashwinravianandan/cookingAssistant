#include "Meal.h"


/*..............................................................................
 * @brief MealItem 
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 MealItem::MealItem ( string name, unordered_set<string> ingredients ):
    mName( name ),
    mIngredients( ingredients ),
    mSecondarySide(false)
{
}
/*..............................................................................
 * @brief ~MealItem 
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 MealItem::~MealItem ()
{
}
/*..............................................................................
 * @brief getName
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns string
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
string MealItem::getName ( )const
{
   return mName;/*string*/
}

/*..............................................................................
 * @brief getIngredients
 *
 * Input Parameters:
 *    @param: void
 * Return Value:
 *    @returns const unordered_set<string>
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
const unordered_set<string>& MealItem::getIngredients ( void )const
{
   return mIngredients;/*const unordered_set<string>*/
}


/*..............................................................................
 * @brief ~MainCourse
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
MainCourse::~MainCourse ()
{
   ;
}

/*..............................................................................
 * @brief needsSide
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool MainCourse::needsSide( void )const
{
   return !mEatWith.empty();/*bool*/
}

/*..............................................................................
 * @brief ~SideDish 
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
SideDish::~SideDish ()
{
}

/*..............................................................................
 * @brief needsSide
 *
 * Input Parameters:
 *    @param: void
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool SideDish::needsSide ( void )const
{
   /*
    * side dish should not need a side dish
    */
   return false;/*bool*/
}
/*..............................................................................
 * @brief getCategory
 *
 * Input Parameters:
 *    @param: void
 * Return Value:
 *    @returns string
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
string MainCourse::getCategory ( void )const
{
   return mMealCategory;/*string*/
}

/*..............................................................................
 * @brief canBeEatenWith
 *
 * Input Parameters:
 *    @param: void
 * Return Value:
 *    @returns vector<string>
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
vector<string> MainCourse::canBeEatenWith ( void )const
{
   return mEatWith;/*vector<string>*/
}

