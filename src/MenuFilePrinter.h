#include <fstream>
#include "Print.h"

typedef vector<pair<string,string>> MenuItems;
class MenuFilePrinter final : public FilePrinter< MenuItems > 
{
   private:
      MenuFilePrinter() = delete;

   public:
      explicit MenuFilePrinter( string fileName );
      virtual bool print( MenuItems& items ) override;
      virtual ~MenuFilePrinter();
};

