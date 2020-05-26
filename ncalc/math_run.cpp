/* 
  Nathaniel Collier
  3/24/2007
  Stack Evaluation Functions
*/
#include <iostream>
#include <cmath>
#include <string>

using namespace std;


#include "math_h/stack_type.h"

#include "stack.h"


/* math_function.cpp */
string math_function_handler( string key, stack<string>& args );
bool function_is_numeric( int function_number );
/* math_conv.cpp */
string dec_to_dec( double temp );
/* local functions */
double evaluate_stack(  stack<stack_type>& output );
double run_stack(  stack<stack_type>& infix );
void reverse_stack( stack<stack_type>& origional );
void infix_to_postfix( stack<stack_type>& infix, stack<stack_type>& output );
void evaluate_operator( stack_type& top, stack<double>& temp );


void evaluate_operator( stack_type& top, stack<double>& temp )
{
  char op;
  double left = 0,
		 right = 0;

  op = top.op.get_operator();

  switch( op )
  { 
	 case '^':
		    // right associative not commutitive
			// a ^ b ^ c = ( a ^ b ) ^ c
			// a ^ b != b ^ a
            right = temp.pop();
			left = temp.pop();
			left = pow( left, right );
			temp.push( left );
			break;
     case '+':
		    // addition is commutitive so we do not have to
			// worry about which one is left and right
			// a + b = b + a
			left = temp.pop() + temp.pop();
			temp.push( left );
		 break;
	 case '-':
		    // subtraction is not commutitive so we have to keep
			// up with which number was on the left and right
			// a - b != b - a
			right = temp.pop();
			left = temp.pop();
			left = left - right;
			temp.push( left  );
		 break;
	 case '*':
			// multiplication is comutitive
			// a * b = b * a
			left = temp.pop() * temp.pop();
			temp.push( left );
		 break;
     case '/':
            // not comutitive
			// a / b != b / a
			right = temp.pop();
			left = temp.pop();
			left = left / right;
			temp.push( left );
		 break;
  }
}



/*
 * Evaluates the stack setup by the run_stack function and returns
 * the result assumes output is a stack with operators in rpn format
 */
double evaluate_stack(  stack<stack_type>& output )
{
	 double result = 0,
			x = 0;
	 stack<double> temp;
     stack_type top;

     cout << "\nEvaluating our postfix stack: ";
	 while( output.size() > 0 )
	 { 
        top = output.pop();
        cout << "\nTOP: " << top << flush;
		
		if( top.check_num() == true ) // check for number
		{
          // its a number we can just push it on
          x = top.number.get_decimal();
		  temp.push( x );
		}
		else 
		if( top.check_op() == true  ) // check for operation
		{
          evaluate_operator( top, temp );
		}
         
	 }




   result = temp.pop();
   return result;
}


void reverse_stack( stack<stack_type>& origional )
{
  stack<stack_type> reverse;
  stack<stack_type> x;

  int size = 0,
	  counter = 0;

  size = origional.size();

  // to reverse we pop into a temp
  // push the temp into another temp
  // then push that temp into the origional
  
  counter = size;
  while( counter > 0 )
  {
    counter--;
	reverse.push( origional.pop() );
  }


  counter = size;
  while( counter > 0 )
  {
    counter--;
	cout << reverse.top() << " "; 
	x.push( reverse.pop() );
  }

  counter = size;
  while( counter > 0 )
  {
   counter--;
   origional.push( x.pop() );
  }

}


/*
 *
 *
 */
void infix_to_postfix( stack<stack_type>& infix, stack<stack_type>& output )
{
   stack<stack_type> stk;
   stack_type top;

   while( infix.size() > 0 )
   {
     top = infix.pop();

	 cout << "\nTOP: " << top;

	 if( top.check_num() == true ) // check for a number
	 {
        // numbers go directly to output in the infix to postfix algorithm
		output.push( top );
	 }
	 else
     if( top.check_op() == true ) // check for a operator
	 {
       if( stk.size() == 0 )
	   {
         // we can just put our operator onto the stack without checking the order
		 stk.push( top );
	   }
	   else // stk stack is not empty
	   {
		 if( top.op.get_operator() == ')' )
		 {
		   cout << "\nPARENTHISIS EQN: "; 
           // pop away the ')' then pop till we get to '(' and pop it away
           while( stk.size() > 0 ) 
		   {
			 top = stk.pop();
			 cout << "\n\tTOP: " << top << flush;
			 if( top.check_op() == true && top.op.get_operator() == '(' ) 
			 {
               // it was already poped we just need to get out of the loop
			   break;
			 }
			 //cout << top << " " << flush;
			 output.push( top );
			 
		   }

		   cout << top << " " << flush;
		 }
		 else
         if( top.op.get_order() <= stk.top().op.get_order() )
		 {
           // top is either less in order or equal so we can also put this onto the stack
		   stk.push( top );
		 }
		 else  // there are lower order operators at the top
		 {
		   // while we have things of lower order pop them off the stack
		   // and the stack is not empty
           while(    top.op.get_order() > stk.top().op.get_order() 
				  && stk.size() > 0 )
		   {
             output.push( top );
			 top = infix.pop();
		   }

		   stk.push( top );
		 }
	   }
	 }
	 else
	 if( top.check_fun() == true ) // function
	 {
         stack<string> arguments;
		 stack_type func = top;
		 string result = 0;
		 // functions are basicly numbers so we need to evaluate the function
		 // and directly push the number onto the stack
		
         
		 // build the argument stack
		 while( infix.size() > 0 )
		 {
           top = infix.pop();
		   if( top.check_op() == true && top.op.get_operator() == ';' )
		   {
             // terminating operator end of function arguments
			 break;
		   }
		   else
		   {
			 result = top.get_value_as_string();
             arguments.push( result );
		   }
		 }
         
		 if( func.function.func_pos != -1 )
	     {
		    // now we need to find out which function this is
		    result = math_function_handler( func.function.get_function(), arguments ); 
            cout << "\nFunction(\"" << func.function.get_function() << "\") = " << result << "\n" << flush;

		    if( function_is_numeric( func.function.func_pos ) == true )
			{
		       top.set_num();
		       top.number.set_dec(  result   );
		       output.push( top );
		    }
		 }
	 }
   }

   // write the operators left in the stack to the output
   while( stk.size() > 0 )
   {
     output.push( stk.pop() );
   }
  

}



/*
 *
 */
double run_stack( stack<stack_type>& infix )
{

     stack<stack_type> output;
	 

	 double result = 0;


     // print out the infix stack which is basicly the output entered by the user
	 cout << "\nInfix: ";
     reverse_stack( infix );

     // now its time to do something with the stack that has been created
	 // we are going to convert the stack to post fix and put it in the post_fix_stack
     
	 infix_to_postfix( infix,output );

      // print out our new postfix stack to the screen
      cout<< "\nPostFix: ";
      reverse_stack( output );

      // now that the stack is converted to rpn format. we can use it
	  result = evaluate_stack( output );

 
   return result;
}// end of run stack

