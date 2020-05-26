/*
 Nathaniel Collier
  9/1/2006
 String Functions
*/
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <cmath>
#include <cstring>

using namespace std;



string reverse_string( string str );
string cap_args( string text );
string get_first_arg( string& text );
string strip_whitespace( string & line );
string strip_lead_whitespace( string & line );
string strip_end_whitespace( string & line );
string get_last_arg( string & text, bool strip_trailing_whitespace );
string get_first_quote( string & text );
string get_line_kyb();
char* string_date();
string format_time( double seconds );
char** vector_to_array( vector<string>& arg_list );
bool check_comment( string text );
int char_count( string text, char x );
int arg_count( const char * text );
vector<string> get_arg_array( string line );
char** tokenize( const char * text );

/*
 *
 */
int char_count( string text, char x )
{
  int counter = 0;
  for( int i=0; i < text.size(); ++i )
  {
    if( text[i] == x )
       ++counter;
  }
  return counter;

}

/*
 *
 */
string reverse_string( string x )
{
  string reverse;

  for( int i = x.size() - 1; i >= 0; --i )
  {
    reverse += x[i];
  }
  return reverse;
}

/*

*/
string cap_args( string text )
{
  string temp;

  for( int i=0; i < text.size(); ++i )
  {
    temp += toupper( text.at(i) );
  }
  return temp;
}

/*
Gets a string from the keyboard and returns it
  This function is needed because of a bug
   in the way getline works
*/
string get_line_kyb()
{
 string x;
 getline( cin, x );
 while( x.size() <= 0 )
 {
   // bug fix with getline 
   getline( cin, x );
 }
 return x;
}


/**
 Removes the first argument that is before on of the characters in the delimiters string
 <ul>Ideas
  <li>Maybe send the delimiters to the function so that it can be defined on a case by case<br>
      bases.</li>
 </ul>
 @param text A string which does or does not contain delemeterized sub strings
             passed by reference so the sub string that might be found can be removed
 @return the first delemeterized sub string that is encountered that sub string is
         then removed from the string text
*/
string get_first_arg( string& text )
{
  string temp;
  string new_text;

  string delimiters = " \t\n"; // put argument seperaters in this
  
  int start = 0;
  int end = 0;

  end = text.find_first_of( delimiters ); // find first char wich is in delimiters

    if( end == -1 )
    {
     // no delimters where found so we will return the string
     return text;
    }

  temp = text.substr( start, end - start ); // we now have our argument

  start = end;

  new_text = text.substr( end );
  end = new_text.find_first_not_of( delimiters );
  
  start += end;

  end = text.size() - start;
  new_text = text.substr( start, end );

  text = new_text;
 
 return temp;  
}


/**

*/
string strip_whitespace( string & line )
{
  string new_line;
  char current;
  
  for( int i=0; i < line.size(); ++i )
  {
    current = line[i];

	if( current != ' ' && current != '\n' && current != '\t' )
	{
      new_line += current;
	}
  }

  return new_line;
}

/**

*/
string strip_lead_whitespace( string & line )
{
  string new_line;
  string delimiters = " \t\n"; // whitespace
  int start = 0;
  int end = 0;

  start = line.find_first_not_of( delimiters );

  end = line.size();

  new_line = line.substr( start, end );

  return new_line;
}


/*

*/
string strip_end_whitespace( string & line )
{
  string new_line;
  string delimiters = " \t\n"; // whitespace
  int start = 0;
  int end = 0;
  
  end = line.find_last_not_of( delimiters );
  
  new_line = line.substr( start, end + 1 );

  return new_line;
}





/**

*/
string get_last_arg( string & text, bool strip_trailing_whitespace )
{ 
  string temp;
  string new_text;

  string delimiters = " \t\n"; // put argument seperaters in this

  int start = 0;
  int end = 0;

  // we need to make sure the string ends with a delimiter or this won't work
  end = text.size() - 1;

  if( text[end] != ' ' && text[end] != '\n' && text[end] != '\t' )
  {
    text += ' '; // tac a delimiter onto the end
  }
  
  // also our string can't start with a delimiter
   text = strip_lead_whitespace( text );

   end = text.find_last_of( delimiters ); 

    if( end == -1 )
    {
     // no delimters where found so we will return the string
     return text;
    }

	start = ( text.substr( 0 , end ) ).find_last_of( delimiters );

	temp = text.substr( start + 1 , end - start - 1 );


  end = start;



  new_text = text.substr( 0, end + 1 );
  
  if( strip_trailing_whitespace == true )
  {
    text = strip_end_whitespace( new_text );
  }
  else
  {
    text = new_text;
  }
  
 return temp; 
}


/**

*/
string get_first_quote( string & text )
{
  string quote;
  string new_text;
  int start = 0,
	  end = 0;

  // we need to find the first quote character

   start = text.find_first_of( "\"" );

  // now find the next quote character after the position we just found
  // use quote var as a temp
   quote = text.substr( start + 1 );

   end = quote.find_first_of( "\"" );
   
   // we need to calculate the offset of quotes start from the start of text
   // so that end is at the correct position
   end += ( start + 1 );
   


   // now our start and end positions should be in the right place
   // The commented out line is if you want the quote characters to appear in the string
   //quote = text.substr( start, (end - start) + 1 );
   // we do not so we will get the quote as this
   quote = text.substr( start + 1, (end - start) - 1 );
   // we should now have the quote we want

  // now to remove the quote from our text
   start = end;

  new_text = text.substr( end );
  end = new_text.find_first_not_of( "\"" );
  
  start += end;

  end = text.size() - start;
  new_text = text.substr( start, end );

  text = new_text;

  return quote;
}


char* string_date()
{
 static char buffer[12]; // 00/00/0000
 tm* date;
 time_t curtime;
 curtime = time (0);
 date = localtime( &curtime );
 strftime( buffer, sizeof( buffer ), "%m/%d/%Y", date );
 return buffer;
}

/*
Takes an amount of seconds sent by double seconds
and formats it into ywdhms format
*/
string format_time( double seconds )
{
  int year = 0,
      week = 0,
      day = 0,
      hour = 0,
      min = 0,
      sec = 0;
  double orig_time = seconds; // save this just in case
  ostringstream time;

      year = (int)floor( seconds / 31449600 ); // year = 60 sec * 60 min * 24 hours * 7 days * 52 weeks =  31449600 seconds
      seconds -=  year * 31449600;
      week = (int)floor( seconds / 6048800 ); // week = 60 sec * 60 min * 24 hours * 7 days = 6048800 seconds
      seconds -=  week * 6048800;
      day = (int)floor( seconds / 86400 ); // day = 60 sec * 60 min * 24 hours = 86400
      seconds -= day * 86400;
      hour = (int)floor( seconds / 3600 ); // hour = 60 sec * 60 min = 3600 seconds
      seconds -= hour * 3600;
      min = (int)floor( seconds / 60 ); // min = 60 sec * 1 min = 60 seconds
      seconds -= min * 60;
      sec = (int)floor( seconds );
   
  if( year <= 0 && week <= 0 && day <= 0 && hour <= 0 && min <= 0 && sec <= 0 )
    time << fixed << orig_time << "s"; 
  else {
   if( year > 0 ) time << year << "y";
   if( week > 0 ) time << week << "w";
   if( day > 0 )  time << day << "d";
   if( hour > 0 ) time << hour << "h";
   if( min > 0 )  time << min << "m";
   if( sec > 0 )  time << fixed << sec << "s";
  }
  return time.str();
}

/*
 *  Converts a vector of strings into
 *  a c array of c strings
 *  Written for backwards compatibility with old
 *  c functions and api calls.
 */ 
char** vector_to_array( vector<string>& arg_list )
{
  char** buffer;
    
  buffer = new char* [arg_list.size()];

  for( int i =0; i < arg_list.size(); ++i )
  {
    buffer[i] = new char[arg_list[i].size()];
	sprintf( buffer[i], arg_list[i].c_str() );
  }
  
  return buffer;
}




/**

*/
bool check_comment( string text )
{
  if( text[0] == '#' && text[1] == '#' )
  {
    return true;
  }

  return false;
}

/*
 *  modified form of the argcount function
 *   Still need the tokenize function for c library
 *   calls that expect a char** buffer to be sent to them
 */
vector<string> get_arg_array( string line )
{
 /*
   * we want to find space seperated arguments and we want to be
   * able to treat text starting with " and ending with " as one
   * argument
   */
  int arg_count = 0;
  int start = -1;
  int end = 0;
  char arg_type;
  string text = line;
  string argument;
  vector<string> arg_list;

  for( int i = 0; i < line.size(); ++i )
  {
	  
     if( text[i] == '\"' || text[i] == ' ' ) arg_type = text[i];
	 else arg_type = ' ';

	  while( text[i] == ' ' || text[i] == '\"' ) ++i;
	  start = i; // this should be the start of the argument
	  // ok now we should be able to find the end of the argument
	


	  while(  text[i] != arg_type ) ++i;

	  end = i;

	  // now we need to see if we have a valid argument
      if( end - start > 1 ) ++arg_count;
	  arg_list.push_back( line.substr( start, end - start ) );
      arg_type = ' ';	
  }

  return arg_list;

}

/*
 * This function is written for c compatibility
 *  it should contain no cpp code and should
 *  compile under the c standard
 */
char** tokenize( const char * text )
{
  
  /*
   * we want to find space seperated arguments and we want to be
   * able to treat text starting with " and ending with " as one
   * argument
   */
  int argcount = 0;
  int start = -1;
  int end = 0;
  char arg_type;
  char** buffer = 0;
  
  
  buffer = (char**) malloc( 1 );

  for( int i = 0; i < strlen( text ); ++i )
  {
     buffer = (char**) realloc( buffer, (( argcount > 0) ? argcount : 1 ) );

	 cout << "\ntext[i]=[" << text[i] << "]";
     if( text[i] == '\"' || text[i] == ' ' ) arg_type = text[i];
	 else arg_type = ' ';

	  while( text[i] == ' ' || text[i] == '\"' ) ++i;
	  start = i; // this should be the start of the argument
	  // ok now we should be able to find the end of the argument
	
	  while(  text[i] != arg_type && i < strlen( text ) ) ++i;

	  end = i;

	  // now we need to see if we have a valid argument
     if( end - start > 1 )
	 {
	   buffer[argcount] = (char*) malloc( end - start );
	   cout << "\nArgument Size: " << end - start;
	   // copy the substring of text into our buffer
	   cout << "\n[";
	   for( int i = 0; i < end-start; ++i ) 
	   {
	     buffer[argcount][i] = text[start + i];
		 cout << text[start + i];
	   }
	   cout << "]";
	   // terminate the string we just created
	   buffer[argcount][end-start]='\0';
	   // terminate the buffer array
       buffer[argcount+1] = 0;	  
	   ++argcount;
	 } 
      arg_type = ' ';	

  }


  return buffer;
}



/* 
 * Counts how many arguments are in a line of text
 */
int arg_count( const char * text )
{
  
  /*
   * we want to find space seperated arguments and we want to be
   * able to treat text starting with " and ending with " as one
   * argument
   */
  int arg_count = 0;
  int start = -1;
  int end = 0;
  char arg_type;

  for( int i = 0; i < strlen( text ); ++i )
  {
	  
     if( text[i] == '\"' || text[i] == ' ' ) arg_type = text[i];
	 else arg_type = ' ';

	  while( text[i] == ' ' || text[i] == '\"' ) ++i;
	  start = i; // this should be the start of the argument
	  // ok now we should be able to find the end of the argument
	
	  while(  text[i] != arg_type ) ++i;

	  end = i;

	  // now we need to see if we have a valid argument
      if( end - start > 1 ) ++arg_count;
      arg_type = ' ';	
  }

  return arg_count;
}

