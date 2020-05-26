/*
Color Output Library
Nathaniel Collier
7/17/2006 

*/
#include <string>
#include <stdarg.h>
#include <fstream>
using namespace std;



#define NUM_TERM_CODES 31
#define MAX_E 1000000
#define ESC_CODE  "\033"

bool check_color( char x );
string strip_color( string text );
string add_color( string text );
void cprintf( const char* text, ... );
string form_color(char a,char b);

void html_form_color(char a,char b,string& x);
void wprintf(string html_file, const char* text, ... );



  // Constant Declerations

  bool color_on = true;

  // console codes
  char const* term_code[ NUM_TERM_CODES ] = {
    "[0;34m", "[1;34m", "[0;30m", "[1;30m", "[0;32m",
    "[1;32m", "[0;36m", "[1;36m", "[0;31m", "[1;31m",
    "[0;35m", "[1;35m", "[0;33m", "[1;33m", "[0;37m",
    "[1;37m",
    "[40m", "[41m", "[42m", "[43m", "[44m", "[45m", "[46m", "[47m",
    "[4m",    "[5m",    "[0m",    "[7m",    "[1m",
    "[2m",    "[8m"
  };

  // html codes
  char const* html_code[ NUM_TERM_CODES ] = {
    "<font color=""#00008B"">", "<font color=""#0000FF"">", "<font color=""#808080"">", "<font color=""#FFFFFF"">", "<font color=""#006400"">",
    "<font color=""#00FF00"">", "<font color=""#008B8B"">", "<font color=""#OOFFFF"">", "<font color=""#8B0000"">", "<font color=""#FF0000"">",
    "<font color=""#800080"">", "<font color=""#FF00FF"">", "<font color=""#804000"">", "<font color=""#FFFF00"">", "<font color=""#808080"">",
    "<font color=""#FFFFFF"">",
    " ", " ", " ",
    " ", " ",
    " ", " ", " ",
    " ", " ", " ", " ", " ", " ", " "
  };

  // this is the index for console and html
  enum temp_code_index
  {
    C_BLUE_F ,  C_LIGHT_BLUE_F , C_BLACK_F, C_DARK_GREY_F, C_GREEN_F,
    C_LIGHT_GREEN_F, C_CYAN_F ,  C_LIGHT_CYAN_F, C_RED_F, C_LIGHT_RED_F, 
    C_PURPLE_F , C_LIGHT_PURPLE_F, C_BROWN_F, C_YELLOW_F, C_LIGHT_GREY_F,
    C_WHITE_F,
    C_BLACK_B, C_RED_B, C_GREEN_B,
    C_YELLOW_B, C_BLUE_B, 
    C_PURPLE_B, C_CYAN_B, C_WHITE_B,
    S_UNDERLINE, S_BLINK, S_RESET, S_REVERSE, S_BRIGHT, S_DIM, S_HIDDEN
  };

  #define NUM_COLOR_TOKENS 17

  const char color_tokens[NUM_COLOR_TOKENS] = {
	'b' ,'B' ,'z' ,'Z' ,'g' ,'G' ,'c', 'C', 'r', 'R', 'p', 'P', 'o', 'Y', 'w' ,'W','O' };

 
 




/**

*/
bool check_color( char x )
{
 bool color_found = false;

 
 for( int i=0; i < NUM_COLOR_TOKENS; ++i )
 {
   if( x == color_tokens[i] )
   {
      color_found = true;
	  break;
   }
 }

 return color_found;

}


/**


*/
string strip_color( string text )
{
 
  for( int i=0; i < text.size(); ++i )
  {
    if( text[i] == '&' && check_color( text[i+1] ))
	  {
	  	// assign text all but that substring
	  	//cout << "ColorSeq: [" << text[i] << text[i+1] << "]\n";
		  text = text.substr(0, i ) + text.substr( i + 2, string::npos );
		  
		  i -= 2; // need to decrease i by 2 since we shifted the array 2 characters to the left
	  }     
  }
  return text;
}


/**

*/
string add_color( string text )
{
  string x;
  for( int i=0; i < text.size(); ++i )
  {
  
	if( text[i] == '&' && check_color( text[i+1] ))
	{
	  x += form_color( text[i], text[i+1] );
	  i++;
	}
	else
	{
          x += text[i];
	} 
  }


  return x;
}


/**

*/
void cprintf( const char* text, ... )
{
  string x;
  va_list args;
  char buf[MAX_E];
  const char *str;
  
  va_start( args, text );
  vsnprintf( buf, MAX_E, text, args );
  va_end( args );
  x =  ( color_on == true ) ? add_color( buf ) : strip_color( buf ) ;
  str = x.c_str();
  printf( "%s", str );
  //cout << str;
}

   

/**

*/
string form_color(char a,char b)
{
 string x;
  bool is_color = true;
 
  if( a== '&' || a == '^' || a == '%' )
  {
   switch( a )
   {
    case '&':
     switch( b )
     {
      // fore ground colors
      case 'b': x = term_code[ C_BLUE_F ]; break;
      case 'B': x = term_code[ C_LIGHT_BLUE_F ]; break;
      case 'z': x = term_code[ C_BLACK_F ]; break;
      case 'Z': x = term_code[ C_DARK_GREY_F ]; break;
      case 'g': x = term_code[ C_GREEN_F ]; break;
      case 'G': x = term_code[ C_LIGHT_GREEN_F ]; break;
      case 'c': x = term_code[ C_CYAN_F ]; break;
      case 'C': x = term_code[ C_LIGHT_CYAN_F ]; break;
      case 'r': x = term_code[ C_RED_F ]; break;
      case 'R': x = term_code[ C_LIGHT_RED_F ]; break;
      case 'p': x = term_code[ C_PURPLE_F ]; break;
      case 'P': x = term_code[ C_LIGHT_PURPLE_F ]; break;
      case 'o': x = term_code[ C_BROWN_F ]; break;
      case 'Y': x = term_code[ C_YELLOW_F ]; break;
      case 'w': x = term_code[ C_LIGHT_GREY_F ]; break;
      case 'W': x = term_code[ C_WHITE_F ]; break;
      default: is_color = false; break;
     }
     break;
   case '^':
     switch( b )
     {
      // back ground colors
      case 'b': x = term_code[ C_BLUE_B ]; break;
      case 'z': x = term_code[ C_BLACK_B ]; break;
      case 'g': x = term_code[ C_GREEN_B ]; break;
      case 'c': x = term_code[ C_CYAN_B ]; break;
      case 'r': x = term_code[ C_RED_B ]; break;
      case 'p': x = term_code[ C_PURPLE_B ]; break;
      case 'y': x = term_code[ C_YELLOW_B ]; break;
      case 'w': x = term_code[ C_WHITE_B ]; break;
     default: is_color = false; break;
     }
    break;
   case '%':
     switch( b )
     {
     // special tokens
     case 'R': x = term_code[ S_RESET ]; break;
     case 'u': x = term_code[ S_UNDERLINE ]; break;
     case 'r': x = term_code[ S_REVERSE ]; break;
     case 'b': x = term_code[ S_BLINK ]; break;
     case 'B': x = term_code[ S_BRIGHT ]; break;
     case 'd': x = term_code[ S_DIM ]; break;
     case 'h': x = term_code[ S_HIDDEN ]; break;
     default: is_color = false; break;
     }
    break;
   default:
   x = a + b; // no term codes where found so set x to what it allready is
   break;
  }
 }
 if( is_color == true )
 {
  x.insert( 0, ESC_CODE );
 }

 return x;
}




// wprintf still needs to be converted over to the new way of doing things like
// cprintf

/**
  This version of the color printf outputs html formated color text
*/
void wprintf(string filename, const char* text, ... )
{
  
   string color;
  string buffer;
  string x;
  ofstream html_file;

  html_file.open( filename.c_str(),ios::app ); // open the file in append mode
  
  if( !html_file )
  {
    // this is a big problem if the file won't open
    return;
  }

  char buf[MAX_E];
  va_list args;

  va_start( args, text );

  vsnprintf( buf, MAX_E, text, args );
  va_end( args );

  buffer = buf;

  for(int i=0;i<buffer.size();++i)
  {
   if(buffer[i]=='&' || buffer[i]=='^' || buffer[i]=='%' )
   { 
     html_form_color(buffer[i],buffer[i+1],color);
     x+=color;
     color.erase();
     ++i;
   }
   else
   if( buffer[i] == '\n' || buffer[i] == '\t' || buffer[i] == ' ' )
   {
     switch( buffer[i] )
	{
	  case '\n':
	     // need to get rid of buffer[i] though
	     // maybe insert the string at the position i to get rid of the character at i
	     // do this for the other html tokens as well
	     x += "<br>";
	    break;
	  case '\t':
	     // need to get rid of buffer[i] though
	     
	     x += "&nbsp;&nbsp;&nbsp;&nbsp;";
	    break;
	  case ' ':
	     // need to get rid of buffer[i] though
	     
	     x += "&nbsp;";
	    break;
	} 
   }
   x+=buffer[i];

  }
     
  html_file << x;

  html_file.close();
  return;
}


void html_form_color(char a,char b,string& x)
{
 bool is_color = true;
 
  if( a== '&' || a == '^' || a == '%' )
  {
   switch( a )
   {
    case '&':
     switch( b )
     {
      // fore ground colors
      case 'b': x = html_code[ C_BLUE_F ]; break;
      case 'B': x = html_code[ C_LIGHT_BLUE_F ]; break;
      case 'z': x = html_code[ C_BLACK_F ]; break;
      case 'Z': x = html_code[ C_DARK_GREY_F ]; break;
      case 'g': x = html_code[ C_GREEN_F ]; break;
      case 'G': x = html_code[ C_LIGHT_GREEN_F ]; break;
      case 'c': x = html_code[ C_CYAN_F ]; break;
      case 'C': x = html_code[ C_LIGHT_CYAN_F ]; break;
      case 'r': x = html_code[ C_RED_F ]; break;
      case 'R': x = html_code[ C_LIGHT_RED_F ]; break;
      case 'p': x = html_code[ C_PURPLE_F ]; break;
      case 'P': x = html_code[ C_LIGHT_PURPLE_F ]; break;
      case 'o': x = html_code[ C_BROWN_F ]; break;
      case 'Y': x = html_code[ C_YELLOW_F ]; break;
      case 'w': x = html_code[ C_LIGHT_GREY_F ]; break;
      case 'W': x = html_code[ C_WHITE_F ]; break;
      default: is_color = false; break;
     }
     break;
   case '^':
     switch( b )
     {
      // back ground colors
      case 'b': x = html_code[ C_BLUE_B ]; break;
      case 'z': x = html_code[ C_BLACK_B ]; break;
      case 'g': x = html_code[ C_GREEN_B ]; break;
      case 'c': x = html_code[ C_CYAN_B ]; break;
      case 'r': x = html_code[ C_RED_B ]; break;
      case 'p': x = html_code[ C_PURPLE_B ]; break;
      case 'y': x = html_code[ C_YELLOW_B ]; break;
      case 'w': x = html_code[ C_WHITE_B ]; break;
     default: is_color = false; break;
     }
    break;
   case '%':
     switch( b )
     {
     // special tokens
     case 'R': x = html_code[ S_RESET ]; break;
     case 'u': x = html_code[ S_UNDERLINE ]; break;
     case 'r': x = html_code[ S_REVERSE ]; break;
     case 'b': x = html_code[ S_BLINK ]; break;
     case 'B': x = html_code[ S_BRIGHT ]; break;
     case 'd': x = html_code[ S_DIM ]; break;
     case 'h': x = html_code[ S_HIDDEN ]; break;
     default: is_color = false; break;
     }
    break;
   default:
   x = a + b; // no html codes where found so set x to what it allready is
   break;
  }
 }
 if( is_color == true )
 {
  x.insert( 0, ESC_CODE );
 }
}





