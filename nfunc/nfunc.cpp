/*
 Nathaniel Collier
 2/10/2007
 Function Library
*/
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;


 int RNUM( int min, int max );
void open_in_file( ifstream & fin,string filename );
void open_out_file( ofstream & fout,string filename );
float calc_sdv( const float array[], int length, float f_avg );



int RNUM( int min, int max )
{
  return (rand() % ( max - min + 1 ) + min );
}


/**
 Opens an output file
 @param fout output file stream passed by reference
 @param filename the filename of the file which will be opened by fout
 @return fout is changed by this function therefore it is passed by reference
*/
void open_out_file( ofstream & fout,string filename )
{
  fout.open( filename.c_str() );
  
  if( !fout )
  {
    cout << "\nOutput File:  \"" << filename << "\" failed to open\nProgram will now exit";
    exit(0);
  }  
  
}

/**
 Opens an input file
 @param fin input file stream passed by reference
 @param filename filename of the file which will be opened by fin
 @return fin is changed so it is passed by reference
*/
void open_in_file( ifstream & fin,string filename )
{
  fin.open( filename.c_str() );
  
  if( !fin )
  {
    cout << "\nInput File:  \"" << filename << "\" failed to open\nProgram will now exit";
    exit(0);
  }
}



/* standard deviation
*/
float calc_sdv( const float array[], int length, float f_avg )
{
  int i = 0;
  float sum = 0;
  float base = 0;
  float radacand = 0;
  
  for( i = 0; i < length; ++i  )
  {
    base = array[i] - f_avg;
    sum += pow( base, 2 );  
  }
  
  radacand = ( 1 / ( (float)length - 1 ) ) * sum; 
  return sqrt( radacand );
  
}


