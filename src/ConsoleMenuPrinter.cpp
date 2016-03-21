#include "ConsoleMenuPrinter.h"

/*..............................................................................
 * @brief print
 *
 * Input Parameters:
 *    @param: vector<pair<string,string>>& menu
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool ConsoleMenuPrinter::print ( vector<pair<string,string>>& items )
{
   cout<<"\n# Menu #\n"<<endl;
   for( auto& item: items)
   {
      cout<<"\t* "<<item.first.c_str();
      if ( !item.second.empty() )
      {
         cout<<" - "<<item.second.c_str();
      }
      cout<<endl;
   }
   return true;/*bool*/
}

/*..............................................................................
 * @brief Con
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 ConsoleMenuPrinter::~ConsoleMenuPrinter()
{
   ;
}
