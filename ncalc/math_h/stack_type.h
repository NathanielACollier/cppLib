#include <string>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;


#include "number_stack_type.h"
#include "function_stack_type.h"
#include "opp_stack_type.h"

#ifndef STACK_TYPE
#define STACK_TYPE

// this class is used to create objects to store in the stack
class stack_type
{
  private:
   bool is_operator;   // type of datatype stored in this object
   bool is_function;   // ...
   bool is_number;      // ...

  public:
    number_type number;        // number value
    function_type function;   // function value
    op_value op;
    stack_type();
    void set_op(){ is_operator = true; is_function = false; is_number = false; }
    void set_fun(){ is_function = true; is_operator = false; is_number = false;}
    void set_num(){ is_number = true; is_operator = false; is_function = false; }
    bool check_num() const { return is_number; }
    bool check_op() const { return is_operator; }
    bool check_fun() const { return is_function; }
    void clear();
	string get_value_as_string();
    friend ostream& operator << (ostream& , stack_type& );
};

stack_type::stack_type()
{
 // constructor
 is_operator = false;
 is_function = false;
 is_number = false;
}

void stack_type::clear()
{
 number.clear();
 function.clear();
 op.clear();
}

ostream& operator<<(ostream& scr,  stack_type& x)
{
    scr << (( x.check_num() ) ? ( x.number.get_number() ) : "")
        << (( x.check_op() ) ? ( x.op.get_operator() ) : '\a' )
        << (( x.check_fun() ) ? ( x.function.get_function() ) : "");

	return scr;
}

string stack_type::get_value_as_string()
{
  string result="";
    
     if( check_num() == true )
	  result = number.get_number();
	 else
     if( check_op() == true )
      result += op.get_operator();
	 else
	 if( check_fun() == true )
	  result = function.get_function();

  return result;
}

#endif



