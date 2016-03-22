#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Print.h"
using namespace std;

typedef vector<pair<string,string>> MenuItems;
class MenuFilePrinter final : public FilePrinter< MenuItems > 
{

   public:
      MenuFilePrinter() = delete;
      explicit MenuFilePrinter( string fileName );
      virtual bool print( const MenuItems& items ) override;
      virtual ~MenuFilePrinter();
};


class ConsoleMenuPrinter : public IPrint< vector<pair<string,string>>>
{
   public:
      bool print( const vector<pair<string,string>>& menu ) override;
      virtual ~ConsoleMenuPrinter();
};

