#include "MenuFilePrinter.h"

/*..............................................................................
 * @brief MenuFilePrinter
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 MenuFilePrinter::MenuFilePrinter ( string fileName ): FilePrinter( fileName )
{
}
/*..............................................................................
 * @brief ~MenuFilePrinter 
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 MenuFilePrinter::~MenuFilePrinter ()
{
}
/*..............................................................................
 * @brief print
 *
 * Input Parameters:
 *    @param: vector<MealItem>& mealItems
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool MenuFilePrinter::print ( MenuItems& items )
{
   bool success = false;
   if ( mFileHandle.is_open() )
   {
      success = true;
      mFileHandle<<"# Menu #\n"<<endl;
      for( auto& item: items)
      {
         mFileHandle<<"\t* "<<item.first.c_str();
         if ( !item.second.empty() )
         {
            mFileHandle<<" - "<<item.second.c_str();
         }
         mFileHandle<<endl;
      }
   }
   return success;/*bool*/
}

