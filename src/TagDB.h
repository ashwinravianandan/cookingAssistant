#pragma once
#include <map>
#include <vector>
#include <string>
#include "Meal.h"
using namespace std;

template <typename K, typename V>
class ITagDatabase
{
   protected:
      multimap<K, V> mTagMap;
   public:
      virtual vector<V> lookup( const K& key )const
      {
         vector<V> valueVector = {};

         auto result = mTagMap.equal_range( key );
         for( auto it = result.first; it != result.second; ++ it )
         {
            valueVector.push_back( it->second );
         }
         return valueVector;/*vector<SideDish>*/
      }

      virtual void insert( const K& key, const V& value )
      {
         mTagMap.insert( make_pair(key, value) );
      }
      virtual ~ITagDatabase(){}
};

//class SideDishTagDatabase : public ITagDatabase<string, SideDish>
//{
//   public:
//      virtual vector<SideDish> lookup( const string& key )override;
//      virtual void insert( const string& key, const SideDish& value)override;
//      virtual ~SideDishTagDatabase(){}
//};
