/*
 Nathaniel Collier
 3/24/2007
 Math Calculator System for nsh shell
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


#include "math_h/stack_type.h"

#include "stack.h"
#include "hash_table.h"


/* math_build.cpp */
void build_stack( stack<stack_type>& infix, string input_text);
/* nstring.so */
string reverse_string( string str );
int char_count( string text, char x );
int arg_count( const char * text );
/* math_conv.cpp */
string dec_to_dec( double temp );
string dec_to_oct( double temp );
string dec_to_bin( double temp );
string dec_to_hex( double temp );
/* math_run.cpp */
double run_stack(stack<stack_type>& infix );
/* local functions */
void build_stack( stack<stack_type>& infix, string input_text);
void print_result( double result );
bool isop( char x );
// initializer
void init_ncalc();
double ncalc( string cmd );
double evaluate( string cmd );

/* math_function.cpp */
void setup_mth_func_hashing();



/* global variables */
HashTable< string, int> mth_fun_lookup_table( -1, 0 );


/*
  returns the result as a double
  will eventualy be changed to a string
  once string opps are completed
*/
double ncalc( string cmd )
{
  return evaluate( cmd );
}


double evaluate( string cmd )
{
  stack< stack_type > infix;
  double result = 0;


  cout << "\nEqn:  " << cmd << flush;

  build_stack( infix, cmd );
  result =  run_stack( infix );
  print_result( result );  
  infix.clear();
  return result;
}





void print_result( double result )
{

  string temp;
  temp = dec_to_dec( result );
  cout<< "\nDecimal    :\t" << temp << "\n";
  temp = dec_to_hex( result );
  cout<< "\nHexidecimal:\t" << temp << "\n";
  temp = dec_to_oct( result );
  cout<< "\nOctal      :\t" << temp << "\n";
  temp = dec_to_bin( result );
  cout<< "\nBinary     :\t" << temp << "\n";

}



void init_ncalc()
{
    /* setup command hashing for the math internal command */
   setup_mth_func_hashing();
}





