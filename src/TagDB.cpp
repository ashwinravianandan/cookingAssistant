//#include "TagDB.h"
//
///*..............................................................................
// * @brief lookup
// *
// * Input Parameters:
// *    @param: 
// *        string& key
// * Return Value:
// *    @returns vector<SideDish>
// *
// * External methods/variables:
// *    @extern
// *............................................................................*/
//vector<SideDish> SideDishTagDatabase::lookup ( const string& key )
//{
//   vector<SideDish> valueVector = {};
//
//   auto result = mTagMap.equal_range( key );
//   for( auto it = result.first; it != result.second; ++ it )
//   {
//      valueVector.push_back( it->second );
//   }
//   
//   return valueVector;/*vector<SideDish>*/
//}
//
///*..............................................................................
// * @brief insert
// *
// * Input Parameters:
// *    @param: 
// *        string& key, 
// *        SideDish& value
// * Return Value:
// *    @returns void
// *
// * External methods/variables:
// *    @extern
// *............................................................................*/
//void SideDishTagDatabase::insert ( const string& key, const SideDish& value )
//{
//   mTagMap.insert( make_pair(key, value) );
//}
