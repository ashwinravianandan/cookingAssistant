#pragma once
#include "Print.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ConsoleMenuPrinter : public IPrint< vector<pair<string,string>>>
{
   public:
      bool print( vector<pair<string,string>>& menu ) override;
      virtual ~ConsoleMenuPrinter();
};

