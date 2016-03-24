#include "GroceryListPrinter.h"

/*..............................................................................
 * @brief GroceryListFilePrinter
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
GroceryListFilePrinter::GroceryListFilePrinter ( string fileName  ):
   FilePrinter( fileName )
{
   ;
}
/*..............................................................................
 * @brief ~GroceryListFilePrinter
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
GroceryListFilePrinter::~GroceryListFilePrinter (  )
{
   ;
}

/*..............................................................................
 * @brief print
 *
 * Input Parameters:
 *    @param: 
 *        unordered_set<string>& groceryList
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool GroceryListFilePrinter::print ( const unordered_set<string>& groceryList )
{
   bool success = false;
   if ( mFileHandle.is_open() )
   {
      mFileHandle<<"# Grocery List #\n";
      for( auto& item: groceryList )
      {
         mFileHandle<<"\t* "<<item.c_str()<<endl;
      }
   }
   return success;/*bool*/
}

/*..............................................................................
 * @brief ~GroceryListConsolePrinter
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
GroceryListConsolePrinter::~GroceryListConsolePrinter (  )
{
   ;
}

/*..............................................................................
 * @brief print
 *
 * Input Parameters:
 *    @param: 
 *        unordered_set<string>& groceryList
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool GroceryListConsolePrinter::print ( const unordered_set<string>& groceryList )
{
   bool success = true;
   cout<<"# Grocery List #\n";
   for( auto& item: groceryList )
   {
      cout<<"\t* "<<item.c_str()<<endl;
   }
   return success;/*bool*/
}
