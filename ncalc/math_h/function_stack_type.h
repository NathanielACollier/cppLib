/*
Nathaniel Collier
8/12/2006
Function Stack Type
*/

#ifndef FUNCTION_STACK_TYPE
#define FUNCTION_STACK_TYPE

// functions are not implimented at this time

class function_type
{
 private:
  string function_name;
  int number_arguments;
  
 public:
   function_type();
   int func_pos;
   void set_function( string name );
   void clear();
   string get_function(){ return function_name; }
   

};

function_type::function_type()
{
 // constructor
 function_name = "";
 number_arguments = 0;
}

void function_type::set_function( string name )
{
  function_name = name;
}

void function_type::clear()
{
 function_name = "";
 number_arguments = 0;
}

#endif
