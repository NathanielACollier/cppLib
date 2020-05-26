/*
  Nathaniel Collier
  3/25/2007
  Stack Building system
    -- basicly it prases the input string a character at a time
	   builds tokens and pushes them onto the stack
*/
#include <iostream>
#include <string>
#include <cmath>

using namespace std;


#include "stack.h"

#include "math_h/stack_type.h"


/* math_function.cpp */
int math_function_lookup( string key );
/* local functions */
bool isop( char x );
void build_stack( stack<stack_type>& infix, string input_text);
void build_operator( string & temp, int & i, stack_type & current, stack<stack_type>& infix );
void build_function( string & temp, int & i, stack_type& current, stack<stack_type>& infix );
void build_number( string & temp, int & i, stack_type & current, stack<stack_type>& infix );


bool isop( char x )
{
  bool result = false;
  switch( x )
  {
    case '+': result = true; break;
    case '-': result = true; break;
    case '*': result = true; break;
    case '/': result = true; break;
    case ')': result = true; break;
    case '(': result = true; break;
    case '^': result = true; break;
    case ';': result = true; break;
  }
  return result;
}


/*
 * builds a function in the build process
 */
void build_function( string & temp, int & i, stack_type& current, stack<stack_type>& infix )
{
  string function;
  int pos = -1;
  while( isalpha( temp[i] ) ) // the function name will end with a space
  {
	function += temp[i];
	 ++i;
  }
  --i; // i was incrimented past the function name so lets decriment it so that
	   // we can use that position on the next run

	   // do something with the function
	 current.function.set_function( function );
	 current.set_fun();

	 // we need to see if the function is in the table
	 // if it is not we will treat this as a string not a function name
     // we do not have a separate type for strings instead we set the pos
	 // of the function to -1 which indicates it is a string
     pos = math_function_lookup( function );
     
	 current.function.func_pos = pos;
 
	 infix.push( current );

}

/*
 * Handles an operator in the build process
 */
void build_operator( string & temp, int & i, stack_type & current, stack<stack_type>& infix )
{
  				 
   bool opp_not_found = false;
   // it is most likely an operator
     switch( temp[i] )
	 {
		case '+': current.op.set_operator( '+' ); break;
		case '-': current.op.set_operator( '-' ); break;
		case '*': current.op.set_operator( '*' ); break;
		case '^': current.op.set_operator( '^' ); break;
		case '/': current.op.set_operator( '/' ); break;
		case '(': current.op.set_operator( '(' ); break;
		case ')': current.op.set_operator( ')' ); break;
		case ';': current.op.set_operator( ';' ); break; // terminating operator
		default: opp_not_found = true; break;
	}

	if( opp_not_found == false )
	{
	  current.set_op();
	  infix.push( current );
	}
}


void build_number( string & temp, int & i, stack_type & current, stack<stack_type>& infix )
{
   string number;
   int pos=0;
				 

   // check for what number system the number uses
   if( temp[i] == '0' && isalpha( temp[i+1] ) )
   {
     pos = i;
     i+= 2; // to get past the 0h 0b 0o etc...
	 
	 while( isalpha( temp[i] ) || isdigit( temp[i] ) )
	 {
	   number += temp[i];
	   ++i;
	 }
	 --i; // because temp[i] is not a digit and it is not alpha and the
		  // for loop will incriment to this position next run so we decriment it now

	 switch( temp[ pos + 1]  )
	 {
	    case 'h' : current.number.set_hex( number );  break; // hexidecimal
	    case 'o' : current.number.set_oct( number );  break; // octal
		case 'b' : current.number.set_bin( number );  break; // binary
		default  : current.number.set_dec( number );  break; // decimal for now figure out 
								                                          //       something else later
	 }

	}
	else // it is a decimal number
	{
	   while( isdigit( temp[i] ) )
	   {
		 number += temp[i];
		 ++i;
	   }
	   --i; // because temp[i] is not a digit and the for loop will incriment
		    // i to that position
	   current.number.set_dec( number );
	}
		
	current.set_num();
    infix.push( current ); // adds the number onto the stack
			
}


void build_stack( stack<stack_type>& infix, string input_text)
{
      string temp =  input_text;
	  stack_type current;
	  
	  cout << "\nBuild: ";
	  // set up the stack
	  for( int i=0; i < (int)temp.length(); ++i )
	  {
             if( !isdigit( temp[i] ) && !isalpha( temp[i] ) && !isop( temp[i] ) )
				 continue;

                 if( isdigit( temp[i] ) ) // number
				 {
				   build_number( temp,i,current,infix );
		         }
				 else 
				 if( isalpha( temp[i] ) ) // function
				 {
				   // if it is a alphabetical character it is most likely a function
				   // non base 10 numbers must start with a 0 to prevent interference with
				   // possible function names
                   build_function( temp,i,current,infix );
				 }
                 else
				 if( !isalpha( temp[i] ) && !isdigit( temp[i] ) ) // operator
				 {
                   build_operator( temp,i,current,infix );
				 }
			  cout << current;
              current.clear();
	  }

}// end of build stack
