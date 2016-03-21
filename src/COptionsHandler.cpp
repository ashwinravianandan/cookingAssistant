#include "COptionsHandler.h"
#include <iostream>
#include <unistd.h>

/*..............................................................................
 * @brief COptionsHandler
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 COptionsHandler::COptionsHandler (  ):mMenuFile( "" ), mGroceryFile( "" ), 
   mDatabaseFile( "" )
{
   ;
}
/*..............................................................................
 * @brief getInstance
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns COptionsHandler&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
COptionsHandler& COptionsHandler::getInstance (  )
{
   static COptionsHandler optHandler;
   return optHandler;/*COptionsHandler&*/
}

/*..............................................................................
 * @brief ~COptionsHandler
 *
 * Input Parameters:
 *    @param: 
 * Return Value:
 *    @returns 
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
 COptionsHandler::~COptionsHandler (  )
{
   if( mGroceryFileHandle.is_open() )
   {
      mGroceryFileHandle.close();
   }
}
/*..............................................................................
 * @brief initialize
 *
 * Input Parameters:
 *    @param: 
 *        argcchar* argv[]
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool COptionsHandler::initialize ( int argc, char* argv[] )
{
   bool success = true;
   int c = 0;
   while( ( c = getopt(argc, argv, "m:g:i:c:abh") ) != -1)
   {
      switch (c )
      {
         case 'm':
            {
               mMenuFile = optarg;
            }
            break;
         case 'g':
            {
               mGroceryFile = optarg;
            }
            break;
         case 'i':
            {
               mDatabaseFile = optarg;
            }
            break;
         case 'c':
            {
               if( true != interpretListCriteria( optarg ))
               {
                  return 0;
               }
            }
            break;
         case 'h':
            {
               cout<<"supported commands are:\n\t-m: output menu-file\n\t-g: output grocery file\n\t-i: input json database\n\t-c comman seperated values of category:number for list generation\n\t-h: shows this help menu"<<std::endl;
               return 0;
            }
            break;
         case '?':
            {
               cerr<<"invalid command line args"<<std::endl;
               return 0;
            }
            break;
      }
   }
   
   return success;/*bool*/
}

/*..............................................................................
 * @brief groceryFile
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns ostream&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
ostream& COptionsHandler::groceryFile (  )
{

   if ( ( "" != mGroceryFile ) && ( !mGroceryFileHandle.is_open() ) )
   {
      mGroceryFileHandle.open( mGroceryFile.c_str() );
   }
   return ( mGroceryFileHandle.is_open() )? mGroceryFileHandle: std::cout ;
}


/*..............................................................................
 * @brief getDatabasePath 
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns string
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
string COptionsHandler::getDatabasePath ( )const
{
   return mDatabaseFile;/*string*/
}

/*..............................................................................
 * @brief interpretListCriteria
 *
 * Input Parameters:
 *    @param: 
 *        listArgument
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool COptionsHandler::interpretListCriteria ( string listArgument )
{
   bool success = false;
   bool finalEntry = false;
   do
   {
      size_t pos = listArgument.find( ',');
      string criteria;
      if ( string::npos == pos )
      {
         if ( listArgument.empty() )
         {
            /// code shouldn't reach here
            break;
         }
         else
         {
            finalEntry = true;
            criteria = listArgument;
         }
      }
      else
      {
         criteria = listArgument.substr( 0, pos );
      }
      size_t colon = 0;
      if ( string::npos != ( colon = criteria.find( ':' ) ) )
      {
         string category = criteria.substr( 0, colon );
         string nrOfItems = criteria.substr( colon+1, criteria.length());
         if( category.empty() || nrOfItems.empty() )
         {
            cerr<<"could not parse "<<criteria<<endl;
         }
         else
         {
            mListCriteria.insert( std::make_pair(category, 
                     atoi( nrOfItems.c_str())));
            success = true;
         }
      }
      else
      {
         cerr<<"could not parse "<<criteria<<endl;
      }
      if( false == finalEntry )
      {
         if( pos < listArgument.length() )
         {
            listArgument = listArgument.substr( pos+1, listArgument.length() );
         }
         else
         {
            break;
         }
      }
   }while( !finalEntry );
   return success;/*bool*/
}

/*..............................................................................
 * @brief getListCriteria 
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns vector< pair< string,int>>
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
set< pair< string,unsigned int>> COptionsHandler::getListCriteria (  )const
{
   return mListCriteria;/*set< pair< string,int>>*/
}

/*..............................................................................
 * @brief getMen
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns string
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
string COptionsHandler::getMenuFilePath ( )const
{
   return mMenuFile;/*string*/
}



