/*
  Nathaniel Collier
  3/24/2007 is the date these functions where put into this file
  3/05/2006 is the date the calculator functions edited last
  Functions to convert between number systems and other things
*/
#include <string>
#include <cmath>

using namespace std;

/* nstring.cpp */
string reverse_string( string str );
int char_count( string text, char x );
/* local functions */
string dec_to_dec( double temp );
string dec_to_oct( double temp );
string dec_to_bin( double temp );
string dec_to_hex( double temp );



string dec_to_hex( double temp )
{


  string number("");
  int integer = (int)floor( temp );
  int fp      = (int)(temp - integer);

	  int a = integer;
	  int b = 16;
	  div_t division;
	  division.quot = -1;
	  division.rem = -1;

	  while( division.quot != 0 )
	  {
       division = div( a, b );
	   a = division.quot;
	   switch( division.rem )
	   {
		 case 10: number += "A"; break;
	     case 11: number += "B"; break;
	     case 12: number += "C"; break;
	     case 13: number += "D"; break;
	     case 14: number += "E"; break;
	     case 15: number += "F"; break;
	     default:  number += division.rem + 48; break;
	   }

	  }
	  number += "h0"; // write it backwards so it will be reversed properly

	  return reverse_string( number ); // number will be backwards so we need to reverse it !!!!
}

string dec_to_bin( double temp )
{
   int sec_cnt(0);
      string number("");
      int integer = (int)floor( temp );
	  int fp      = (int)(temp - integer);
          int num_space = 0;
	  int a = integer;
	  int b = 2;
	  div_t division;
	  division.quot = -1;
	  division.rem = -1;
	  while( division.quot != 0 )
	  {
             if( sec_cnt == 4 ) { number += " "; sec_cnt = 0; } // groups numbers by 4
             division = div( a, b );
	     a = division.quot;
	     number += division.rem + 48;
	     sec_cnt++;
	  }
          // produce correct display of binary number
          div_t counter;
           counter = div( number.size(), 4 );
             num_space = char_count( number, ' ' );
          do{
              counter = div( number.size() - num_space , 4 );
               if( counter.rem != 0 )
                    number += "0";
                else break;
            }while( counter.rem != 0 );

	  number += "b0";

    return reverse_string( number ); // number will be backwards so we need to reverse it !!!!
}


string dec_to_oct( double temp )
{

      string number("");
      int integer = (int)floor( temp );
	  int fp  = (int)(temp - integer);

	  int a = integer;
	  int b = 8;
	  div_t division;
	  division.quot = -1;
	  division.rem = -1;
	  while( division.quot != 0 )
	  {
           division = div( a, b );
	   a = division.quot;
	   number += division.rem + 48;
	  }

	  number += "o0";

   return reverse_string( number ); // number will be backwards so we need to reverse it !!!!
}

string dec_to_dec( double temp )
{

   string number("");
      int integer = (int)floor( temp );
      int fp      = (int)(temp - integer);

	  int a = integer;
	  int b = 10;
	  div_t division;
	  division.quot = -1;
	  division.rem = -1;
	  while( division.quot != 0 )
	  {
       division = div( a, b );
	   a = division.quot;
	   number += division.rem + 48;
	  }

    return reverse_string( number ); // number will be backwards so we need to reverse it !!!!
}

