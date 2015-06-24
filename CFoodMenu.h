#pragma once
#include <vector>
#include <string>
#include <json/json.h>

typedef struct _FoodItems
{
   std::string mDish;
   std::vector<std::string> mIngredients;
}foodItem;

class CFoodMenu
{
   private:
      /// constant declarations
      const char* scJsonKeyIngredient;
      const char* scJsonKeyBreakfast;
      const char* scJsonKeyMainCourse;
      const char* scJsonKeyDish;

      std::vector<foodItem> mBreakfastItems;
      std::vector<foodItem> mMainCourse;

   public:
      CFoodMenu() = delete;
      virtual ~CFoodMenu() = default;
      explicit CFoodMenu( const Json::Value& babyMenuItems );
      void DisplayFoodItems( void );
};

namespace JsonHandling
{
   class CJsonValue: public Json::Value
   {
      /**
       * @todo: extend to all types 
       */

      public:
         CJsonValue( const Json::Value& JVal ):Json::Value( JVal ){}
         operator unsigned int()
         {
            return this->asUInt();
         }
         operator std::string() 
         {
            return this->asString();
         }
         operator  int()
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
         bool retVal = false;
         if ( valType == JVal[ key ].type() )
         {
            CJsonValue Val = JVal[ key ];
            retVal = true;
            data = static_cast<T>( Val );
         }
         return retVal;
      }
}
