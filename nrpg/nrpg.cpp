/*
 * Nathaniel Collier
 * 4/3/2007
 * Password generator for nsh shell
 */

#include <iostream>
#include <string>


using namespace std;


#include "password.h"

/* nstring.so */
int arg_count( string line );

/* local functions */
void init_nrpg();
void shutdown_nrpg();
void show_syntax();
string nrpg( string cmd );


/* global variables */
password_list_t password_list;


void show_syntax()
{
      cout << "\nExpecting one of the following commands"
	     << "\nadd - add a new password that you generate yourself "
		 << "\nnew - generates a password given specific criteria by the user"
		 << "\ngen - generates a fast password given only the length.  The password"
		 << "\n      that is generated will consist of lower case numbers and letters"
		 << "\n      only"
		 << "\n***** Type the command without arguments to see its syntax *******";
}

/* 
 * Random Password Generator Command
 *  - used to edit generate and delete passwords
 *    from the password list
 */
string nrpg( string cmd )
{
  vector<string> arg_list = get_arg_array( cmd );

  if( arg_list.size() < 1 )
  {
    show_syntax();
	return "error: did not specify a proper option";
  }

  cout << "\nOption: " << arg_list[0]
	   << "\nArgs: " << arg_list.size();

  if( arg_list[0] == "add" )
  { 
    if( arg_list.size() != 7 + 1 )
	{
      cout << "\nExpecting<\"password\" \"description\" length number alpha alpha_case ascii>";
	  return "error: did not specify proper arguments for add option";
	}
	password_list.add_password_from_string( cmd );
  }
  else
  if( arg_list[0] == "new" )
  {
     // since this is a new password I am expecting
	 // the following
	 //     "\"description\" length number alpha alpha_case ascii"
	 if( arg_list.size() != 6 + 1 )
	 {
       cout << "\nExpecting <\"description\" length number alpha alpha_case ascii>";
	   return "error: did not specify proper arguments for new option";
	 }
	 // if we have our six arguments we can send them to the create_password function
	 password_type x;
	 x.description = arg_list[1];
	 x.length = atoi( arg_list[2].c_str() );
	 x.number = atoi( arg_list[3].c_str() );
	 x.alphabet = atoi( arg_list[4].c_str() );
	 x.alphabet_case = atoi( arg_list[5].c_str() );
	 x.ascii = atoi( arg_list[6].c_str() );
	 string password = password_list.create_password( x );
	 x.text = password;
     password_list.add_password( x );
     
	 cout << password_list.display_password( x );
  }
  else
  if( arg_list[0] == "gen" )
  {
	 if( arg_list.size() != 1 + 1 )
	 {
       cout << "\nExpecting a password size";
	   return "error: did not specify a password size";
	 }
     cout << "\nNew Password Generated: " 
		  << password_list.create_password( atoi( arg_list[1].c_str() ), 1, 1, 0, 0 );
  }
  else
  if( arg_list[0] == "list" )
  {
     cout << "\n" << password_list;
  }
  else
  {
     show_syntax();
	 return "error: failure to specify any arguments";
  }

  return "";
}


void init_nrpg()
{
  password_list.load( "password_list.txt" );
}


void shutdown_nrpg()
{
  password_list.write_password_list( "password_list.txt" );
  password_list.write_html_password_list( "password_list.html" );
}


