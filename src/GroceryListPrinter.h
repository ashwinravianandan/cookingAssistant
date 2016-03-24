#include <iostream>
#include "Print.h"
#include <unordered_set>
using namespace std;


class GroceryListFilePrinter: public FilePrinter<unordered_set<string>>
{
   public:
      GroceryListFilePrinter()=delete;
      explicit GroceryListFilePrinter( string fileName );
      virtual bool print( const unordered_set<string>& ) override;
      virtual ~GroceryListFilePrinter();
};

class GroceryListConsolePrinter: public IPrint<unordered_set<string>>
{
   public:
      virtual bool print( const unordered_set<string>& ) override;
      virtual ~GroceryListConsolePrinter();
};
