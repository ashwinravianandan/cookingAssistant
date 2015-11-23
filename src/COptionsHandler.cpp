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
   mDatabaseFile( "" ), mGenerateBabyMenu( false ), mGenerateAdultMenu( false )
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
   if( mMenuFileHandle.is_open() )
   {
      mMenuFileHandle.close();
   }
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
   while( ( c = getopt(argc, argv, "m:g:i:abh") ) != -1)
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
         case 'b':
            {
               mGenerateBabyMenu = true;
            }
            break;
         case 'a':
            {
               mGenerateAdultMenu = true;
            }
            break;
         case 'h':
            {
               cout<<"supported commands are:\n\t-m: output menu-file\n\t-g: output grocery file\n\t-i: input json database\n\t-b: generate baby menu\n\t-a: generate adult menu\n\t-h: shows this help menu"<<std::endl;
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
 * @brief menuFile
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns ostream&
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
ostream& COptionsHandler::menuFile (  )
{
   if ( ( "" != mMenuFile ) && (!mMenuFileHandle.is_open() ))
   {
      mMenuFileHandle.open( mMenuFile.c_str() );
   }
   return ( mMenuFileHandle.is_open() )? mMenuFileHandle: std::cout ;
}

/*..............................................................................
 * @brief generateBabyMenu
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool COptionsHandler::generateBabyMenu(  )const
{
   return mGenerateBabyMenu;
}

/*..............................................................................
 * @brief generateAdultMenu
 *
 * Input Parameters:
 *    @param:  parameters
 * Return Value:
 *    @returns bool
 *
 * External methods/variables:
 *    @extern
 *............................................................................*/
bool COptionsHandler::generateAdultMenu(  )const
{
   return mGenerateAdultMenu;
}

/*..............................................................................
 * @brief getDat
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

