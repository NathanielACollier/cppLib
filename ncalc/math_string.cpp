/*
  Nathaniel Collier
  5/5/2007
  String Math Shared Library (Dynamic Linked Library)
*/
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;



/* nstring.so */
string reverse_string( string x );
/* local functions */
string add_string( string a, string b );
string subtract_string( string a, string b );
string divide_string( string a, string b );
string multiply_largeA_by_singleB( string a, int b );
string multiply_string( string a, string b );
string random_number( int size );
/* local conversion functions */
string number_to_string( double number );
string number_to_string( int number );


const unsigned short multiplication_table[10][10]= {
       //0    1		2	3	4	5	6	7	8	9 
	   { 0,   0,	0,	0,	0,	0,	0,	0,	0,	0 },
	   { 0,	  1,	2,	3,	4,	5,	6,	7,	8,	9 },
	   { 0,	  2,	4,	6,	8,	10,	12,	14,	16,	18 },
       { 0,	  3,	6,	9,	12,	15,	18,	21,	24,	27 },
	   { 0,	  4,	8,	12,	16,	20,	24,	28,	32,	36 },
	   { 0,	  5,	10,	15,	20,	25,	30,	35,	40,	45 },
	   { 0,	  6,	12,	18,	24,	30,	36,	42,	48,	54 },
	   { 0,	  7,	14,	21,	28,	35,	42,	49,	56,	63 },
	   { 0,	  8,	16,	24,	32,	40,	48,	56,	64,	72 },
	   { 0,	  9,	18,	27,	36,	45,	54,	63,	72,	81 }

};


const unsigned short addition_table[10][10]= {
	  //   0	1	2	3	4	5	6	7	8	9
	  {	   0,	1,	2,	3,	4,	5,	6,	7,	8,	9 },
	  {	   1,	2,	3,	4,	5,	6,	7,	8,	9,	10 },
	  {	   2,	3,	4,	5,	6,	7,	8,	9,	10,	11 },
	  {    3,	4,	5,	6,	7,	8,	9,	10,	11,	12 },
	  {    4,	5,	6,	7,	8,	9,	10,	11,	12,	13 },
	  {    5,	6,	7,	8,	9,	10,	11,	12,	13,	14 },
	  {    6,	7,	8,	9,	10,	11,	12,	13,	14,	15 },
	  {    7,	8,	9,	10,	11,	12,	13,	14,	15,	16 },
	  {    8,	9,	10,	11,	12,	13,	14,	15,	16,	17 },
	  {    9,	10,	11,	12,	13,	14,	15,	16,	17,	18 }
};


const unsigned short subtraction_table[10][10]={


};





struct carry_type
{
  int pos;
  int num;
};






/*
 * This function does not have what I call writer comments because do to some misplaced
 *   commands on the terminal this function was deleted after 3 hours or so of work so
 *   the function you see below was written very quickly from memory in about 20 minutes
 *   so the writers comments that I usualy make are not there but I am in the process of
 *   adding them back.
 */
string add_string( string a, string b )
{
  string final;
  short cur_a = 0,
        cur_b = 0,
	    result = 0;

  vector< carry_type > carry_list;

  carry_type c;
  
  // we find out the maximum number by testing to see if
  // a is the maximum.
  bool a_max = ( a.size() > b.size() ) ? true : false;

  // here we compute the size of the answer since properties
  // of adition dictate that it can be as large as the largest number
  // pluss one.  Since a carry could occur at the end.
  // sizeof( a + b ) = sizeof( max( a,b) ) + 1
  int size = (( a_max == true ) ? a.size() : b.size() ) + 1;

  // we need to reverse the strings since numbers are written from left to
  // right but in the decimal system place value moves up from right to left
  // so the numbers must be processed by place value.
  a = reverse_string( a );
  b = reverse_string( b );

  for( int i = 0; i < size; ++i )
  {
    if( i >= a.size() ) cur_a = 0;
	else 
	  cur_a =  a[i] - '0' ;
	
	if( i >= b.size() ) cur_b = 0;
	else
	  cur_b = b[i] - '0';

	result = addition_table[cur_a][cur_b];
    cout << "\n" << cur_a << " + " << cur_b << " = " << result;

     //check to see if any carry overs need to be added to the result
	for( int j = 0; j < carry_list.size(); ++j )
	{
      if( carry_list[j].pos == i )
	  {
	    int debug_result = result;
        result += carry_list[j].num;
		cout << "\nAdd carry " << carry_list[j].num << " to " << debug_result << " = " << result;
	  }
	}

    if( (c.num = (int)(result / 10) ) > 0 )
	{
      // there is a carry that needs to occur
	  c.pos = i + 1;
	  carry_list.push_back( c );
	  result -= c.num * 10;
	  cout << "\n" << result << " Carry " << c.num << " to position " << c.pos;
	}
    
	final += '0' + result;
  }

  return reverse_string( final );
}



/*
 *  This function does strait subtraction the other function determines
 *     positive/negative result and sets things up
 */
string subtract_string( string a, string b )
{
   string final;   
   int cur_a,
       cur_b,
	   result,
	   size;
 	// a - b

    // the biggest the end result can be is the size of the largest number
	bool a_max = ( a.size() > b.size() ) ? true : false;
    // this will basicly work the same way addition works
    

	size = ( a_max == true ) ? a.size() : b.size();

	 /* subtraction rules
	     -----------------------------------------------------
		 ***********These checks are performed before strings are reversed*******
		 1.)  Rules to determine if answer will be negative
		    if( A.size() == B.size() )
			{
			 int x = 0;
		     while( A[x] == B[x] ) // skip all equal numbers
			 {
              ++x;
			 }
			 if( A[x] < B[x] ) // first non equal position
			 {
               swap A and B perform the subtraction ( B - A )
			   and the result will be negative
			 }
			}
			else
			if( A.size() < B.size() )
			{
              // the answer is automaticly negative
			  // swap A and B perform the subtraction ( B- A)
			  // and the result will be negative
			}
		  Performance of Subtraction once negation is determined
          -----------------------------------------------------------
		  Reverse the strings A and B
		  if( A[i] < B[i] )
		  {
            A[i] += 10
			A[i+1] -= 1  use the carry structure though
			             in subtraction the carrys will be -1
			perform the subtraction 
			result = A[i] - B[i]
		  }

	  
	  */

    a = reverse_string( a );
	b = reverse_string( b );

	for( int i = 0; i < size; ++i )
	{
      if( i >= a.size() ) cur_a = 0;
	  else 
	  cur_a =  a[i] - '0' ;
	
	  if( i >= b.size() ) cur_b = 0;
	  else
	  cur_b = b[i] - '0';

      result = cur_a - cur_b;
	  cout << "\n" << cur_a << " - " << cur_b << " = " << result;

	 

	}
   
}



string divide_string( string a, string b )
{
  /*
   * Division looks quite hard at the moment
   * since there is no known algorithm that I have found
   * that does not rely on guessing which computers do
   * not do
   */

}


string multiply_largeA_by_singleB( string a, int b )
{
  unsigned short cur_a = 0,
				 result = 0;

  string final;
  vector< carry_type > carry_list;
  /* carry_type
   * int num
   * int pos
   */
  carry_type c;

  a = reverse_string( a );

   for( int i = 0; i < a.size() + 1; ++i )
   {
      if( i >= a.size() ) cur_a = 0;
	  else 
	  cur_a =  a[i] - '0' ;
      result = multiplication_table[cur_a][b]; // max result of 9 * 9 = 81 so max carry of 8
       
	  cout << "\n" << cur_a << " * " << b << " = " << result;

	  // need to add carrys to result
	  for( int j = 0; j < carry_list.size(); ++j )
	  {
         if( carry_list[j].pos == i )
		 {
		   int debug_result = result;
           result += carry_list[j].num;
		   cout << "\nAdd carry " << carry_list[j].num << " to " << debug_result << " = " << result;
		 }
	  }
	  // then determine if a carry needs to be done
	  
	  // first determine if this is the last position as there is no carry in that position
	  if(  /*  ( i != a.size() - 1) && */ (c.num = (int)(result / 10) ) > 0   )
	  {
        // there is a carry that needs to occur
	    c.pos = i + 1;
	    carry_list.push_back( c );
	    result %= 10;
	    cout << "\n" << result << " Carry " << c.num << " to position " << c.pos;
	  }
    
	final += '0' + result;

   }
   return reverse_string( final );
}


string multiply_string( string a, string b )
{
   string shift_postfix,
          current_level,
          final;
   int  cur_b = 0;

   
   // we need to start out with the final string populated with zeros
   // so that our answer will contain the correct number of place values
   for( int i = 0; i < a.size() + b.size(); ++i )
   {
      final += '0';
   }

   // there are b.size() levels so
   for( int level = 0; level < b.size(); ++level )
   {
      for( int i = 0; i != level; ++i )
	  {
        shift_postfix += '0'; 
	  }

	  if( level >= b.size() ) cur_b = 0;
    	else
	  cur_b = b[level] - '0';
 
      current_level =  multiply_largeA_by_singleB( a, cur_b ) + shift_postfix;

	  // and add in this level to the final
	  final = add_string( current_level, final );

      cout << "\n-------------------------------------------"
	       << "\nLEVEL#          " << level
	       << "\nSHIFT PREFIX:   " << shift_postfix
	       << "\nCURRENT_LEVEL:  " << current_level
		   << "\nFINAL_LEVEL:    " << final
		   << "\n-------------------------------------------";

	  shift_postfix.clear(); // clear for the next level
      
   }

   return final;
}


string random_number( int size )
{ 
  // the range of each digit is a min of 0 and a max of 9
  string final;

  for( int i = 0; i < size; ++i )
  {
     final += '0' + (rand() % 10 ); 
  }
  return final;
}



string number_to_string( int number )
{
  stringstream num;

  num << number;

  return num.str();
}


string number_to_string( double number )
{
  stringstream num;
   
  num << number;

  return num.str();
}

