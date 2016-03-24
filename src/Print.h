#pragma once
#include <string>
#include <fstream>
#include "MealDB.h"

template <typename T>
class IPrint
{
   public:
      virtual bool print( const T& ) = 0;
      virtual ~IPrint(){}
};

template <typename T>
class FilePrinter: public IPrint<T>
{
   protected:
      string mFileName;
      ofstream mFileHandle;
      FilePrinter() = delete;
   public:
      virtual ~FilePrinter()
      {
         close();
      }

      explicit FilePrinter( string fileName ) : mFileName( fileName ){(void)open();}

      virtual bool open( )
      {
         if ( ! mFileHandle.is_open() )
         {
            mFileHandle.open( mFileName.c_str() );
         }
         return mFileHandle.is_open();/*bool*/
      }
      virtual void close( )
      {
         if( mFileHandle.is_open() )
         {
            mFileHandle.close();
         }
      }
};

