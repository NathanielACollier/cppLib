/*
 Nathaniel Collier
 3/24/2007
 Math Functions for the calculator in nsh shell
*/
#include <iostream>
#include <cmath>
#include <string>

using namespace std;



#include "stack.h"
#include "hash_table.h"

/* nfunc.so */
int RNUM( int min, int max );
/* math_string.cpp */
string number_to_string( double number );
string number_to_string( int number );
string add_string( string a, string b );
string subtract_string( string a, string b );
string divide_string( string a, string b );
string multiply_string( string a, string b );


struct math_function_type
{
  string ( * function )  ( stack<string>& args );
  int id;
  string name;
  bool numeric_result;
};




/* math functions */
string std_dev( stack<string>& args );
string avg( stack<string>& args );
string random( stack<string>& args );
string strop( stack<string>& args );

#define NUM_MTH_FUNC 4


const struct math_function_type math_function_list[NUM_MTH_FUNC] = {
               { std_dev, 0, "std_dev", true },
			   { avg, 1, "avg",true },
			   { random, 2, "random",true },
			   { strop, 3, "strop",false }
};


/* global variables */
extern HashTable< string, int> mth_fun_lookup_table;






/* local functions */
void setup_mth_func_hashing();
int math_function_lookup( string key );
double math_function_handler( string key, stack<double>& args );
math_function_type get_function_from_index( int pos );
bool function_is_numeric( int function_number );

math_function_type get_function_from_index( int pos )
{
  return math_function_list[ pos ];
}

void setup_mth_func_hashing()
{
  for( int i = 0; i < NUM_MTH_FUNC; ++i )
  {
    mth_fun_lookup_table.insert( math_function_list[i].name, i );
  }
}

int math_function_lookup( string key )
{
  int pos = -1;
  pos = mth_fun_lookup_table[key];
  return pos;
}


string math_function_handler( string key, stack<string>& args )
{
  string result;
  int pos = 0;

  pos = math_function_lookup( key );
  if( pos == -1 )
  {
    cout << "\nError in function name: \"" << key << "\".";
	return "error";
  }

  result = math_function_list[pos].function( args );

  return result;
}



/*
 * standard deviation
 */
string std_dev( stack<string>& args )
{
  
}

/*
 *
 */
string avg( stack<string>& args )
{
  double sum = 0;
  int n = 0;
  double top = 0;

  while( args.size() > 0 )
  {
    top = atoi( args.pop().c_str() );
	sum += top;
	++n;
  }
  
  return number_to_string( sum / n );
}


/*
 * Generates random number
 */
string random( stack<string>& args )
{
  int max = atoi( args.pop().c_str() ),
      min = atoi( args.pop().c_str() );

  if( max < min )
     return "error"; // a nice number to return if the number were not entered correctly

  return number_to_string( RNUM( min, max ) );
}




/*
 *  String Operations
 */
string strop( stack<string>& args )
{
  string a = args.pop(),
         op = args.pop(),
		 b = args.pop(),
		 result;

   if( op == "add" || op == "+" )
     result = add_string( a, b );
   else
   if( op == "sub" || op == "-" )
     result = subtract_string( a, b );
   else
   if( op == "mul" || op == "*" || op == "x" )
     result = multiply_string( a, b );
   else
   if( op == "div" || op == "/" || op == "%" )
     result = divide_string( a, b );
  
  return result;
}



bool function_is_numeric( int function_number )
{
  return get_function_from_index( function_number ).numeric_result;
}


