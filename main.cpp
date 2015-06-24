#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace JsonHandling
{
   class CJsonValue: public Json::Value
   {
      /**
       * @todo: extend to all types 
       */
      
      public:
         CJsonValue( const Json::Value& JVal ):Json::Value( JVal ){}
         operator unsigned int(  )
         {
            return this->asUInt();
         }
         operator std::string() 
         {
            return this->asString();
         }
         operator  int(  )
         {
            return this->asInt();
         }
         operator bool()
         {
            return this->asBool();
         }
   };
   template <typename T>
      bool checkAndRetriveJsonData( Json::Value JVal, const char* key, Json::ValueType valType, T& data )
      {
         CJsonValue Val = JVal;
         bool retVal = false;
         if ( valType == Val[ key ].type() )
         {
            retVal = true;
            data = static_cast<T>( Val[ key ] );
         }
         return retVal;
      }
}

int main()
{
   ifstream jsonDatabase( "menu.json" );
   Json::Value Jval;

   jsonDatabase>>Jval;

   Json::Value babyMenu = Jval[ "babyMenu" ];

   Json::Value babyData;
   
   JsonHandling::checkAndRetriveJsonData( Jval, "babyMenu", Json::arrayValue, babyData );

   Json::FastWriter writer;
   std::string output = writer.write(babyData );
   cout<<output.c_str();
   return 0;
}


