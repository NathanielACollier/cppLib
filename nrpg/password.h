/*
Nathaniel Collier
9/30/2006
Password Datatype
*/
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


/* nfunc.cpp */
void open_out_file( ofstream& fout,string filename );
void open_in_file( ifstream& fin,string filename );
int RNUM( int min, int max );

/* nstring.so */
string get_line_kyb();
vector<string> get_arg_array( string line );



#ifndef PASSWORD_H
#define PASSWORD_H





struct password_type
{
    string text;
    string description;
    bool number;
    bool alphabet;
    bool alphabet_case;
    bool ascii;
    int length;

	friend ostream& operator << (ostream& , password_type& );
};


class password_list_t
{
  private:
    string html_filename;
    string password_filename;
    list<password_type>  password_list;
    bool pwd_load;
  public:
    password_list_t( );
   ~password_list_t();
    void load( string password_filename );
    void write_html_password_list( string html_filename );
    void write_password_list( string password_filename );
    void add_password( password_type temp );
	void add_password_from_string( string password );
    string gen_password(int length, bool number, bool alpha, bool alpha_case, bool ascii );
    bool is_load();
	password_type read_from_string( string password );
	string gen_password_string( string line );
	friend ostream& operator << ( ostream& scr, password_list_t& x );
	string create_password( int length, bool number, bool alpha, bool alpha_case, bool ascii );
	string create_password( password_type x );
	string display_password( password_type x );
	
};

//////////////////////////////////  Private Data Members ///////////////////////////////////

string password_list_t::gen_password(int length, bool number, bool alpha, bool alpha_case, bool ascii )
{
   char current = '*';
   stringstream password;
   
   for( int i=0; i < length; ++i )
   {
     if( ascii  == true )
     {
       current = RNUM( 33, 126 );
       password << current;
     }
     else
     if( number  == true && alpha  == true )
     {
       char number = RNUM( 48, 57 );
       char letter;
       if( alpha_case == true )
       {
         letter = RNUM( 65, 90 );
         if( RNUM(1,2) == 2 ) letter = tolower( letter );
       }
       else
       {
         letter = RNUM( 97, 122 );
       }

       if( RNUM(1,2) == 2 )
       {
         current = letter;
       }
       else
       {
         current = number;
       }

       password << current;
            
     }
     else
     if( number == false && alpha  == true )
     {
       if( alpha  == true )
       {
        current = RNUM( 65, 90 );
        if( RNUM(1,2 ) == 2 )
        {
          password << tolower( current );
        }	
        else
        {
           password << current;
        }
       }
       else
       {
         current = RNUM( 97, 122 );
          password << current;
       }
      }
      else
      if(  number  == true &&  alpha   == false )
      {
        current = RNUM( 48, 57 );
        password << current;
      }
   }

  return password.str();
}





///////////////////////////////////  Public Data Members ///////////////////////////////////

// constructor
password_list_t::password_list_t( )
{ 
  pwd_load = false;
}

// destructor
password_list_t::~password_list_t()
{



}




void password_list_t::load(string password_filename )
{
   ifstream password_in;
   string line;
   int list_length(0);
   password_type current;
   vector<string> arg_list;
   
   password_in.open( password_filename.c_str() );

   if( !password_in )
   {
     pwd_load = false;

   }	
   else
   {

	 while( getline( password_in, line ) )
	 {
	   if( line.size() < 1 ) continue;
	   current = read_from_string( line );
	   password_list.push_back( current );
     }
      pwd_load = true;
       password_in.close();
  }
 
}





void password_list_t::write_html_password_list( string html_filename )
{
   ofstream fout;
   open_out_file( fout, html_filename );

   fout<< "<html>\n"
       << "<head>\n"
       << "<title> Password List </title>\n"
       << "</head>\n"
       << "<body>\n"
       << "<table style=\"text-align: left; width: 100%;\" border=\"0\" cellpadding=\"0\" cellspacing=\"10\">\n"
       << "<tbody>\n"
       << "<tr>\n"
       << " <td><big><span style=\"font-weight: bold;\">Description</span></big></td>\n"
       << " <td><big><span style=\"font-weight: bold;\">Password</span></big></td>\n"
       << " <td><big><span style=\"font-weight: bold;\">Length</span></big></td>\n"
       << " <td><big><span style=\"font-weight: bold;\">Number</span></big></td>\n"
       << " <td><big><span style=\"font-weight: bold;\">Alphabet</span></big></td>\n"
       << " <td style=\"font-weight: bold;\"><big>Case Sensitive</big></td>\n"
       << " <td style=\"font-weight: bold;\"><big>ASCII</big></td>\n"
			  << "</tr>\n";
                 
   for(  list<password_type>::iterator marker = password_list.begin();  marker != password_list.end(); ++marker )
   {
      fout<< "<tr>\n"
	  << "<td>" << marker->description << "</td>\n"
	  << "<td>" << marker->text << "</td>\n"
          << "<td>" << marker->length << "</td>\n";
      if( marker->number == false ) fout<< "<td>false</td>\n"; else fout<< "<td>true</td>\n";
      if( marker->alphabet == false ) fout<< "<td>false</td>\n"; else fout<< "<td>true</td>\n";
      if( marker->alphabet_case == false ) fout<< "<td>false</td>\n"; else fout<< "<td>true</td>\n";
      if( marker->ascii == false ) fout<< "<td>false</td>\n"; else fout<< "<td>true</td>\n";
      fout<< "</tr>\n";
   }

   fout<< "</tbody>\n"
       << "</table>\n"
       << "<br>\n"
       << "</body>\n"
       << "</html>\n";
   fout.close();	
}

/* 
 *
 * encapsulates the gen_password function so that it
 * can be overloaded without having 2 copies of that 
 * function
 */
string password_list_t::create_password( password_type x )
{
  return gen_password( x.length, x.number, x.alphabet, x.alphabet_case, x.ascii );
}

string password_list_t::create_password( int length, bool number, bool alpha, bool alpha_case, bool ascii )
{
  return gen_password( length, number, alpha, alpha_case, ascii );
}

void password_list_t::write_password_list( string password_filename )
{
  ofstream pwd_out;
  open_out_file( pwd_out, password_filename );

  pwd_out << *this;

  pwd_out.close();
}



void password_list_t::add_password( password_type temp )
{
  password_list.push_back( temp );
  pwd_load = true;
}



bool password_list_t::is_load()
{
  return pwd_load;
}


password_type password_list_t::read_from_string( string password )
{
  password_type x;
  vector<string> arg_list = get_arg_array( password );

  x.text = arg_list[0];
  x.description = arg_list[1];
  x.length = atoi( arg_list[2].c_str() );
  x.number = atoi( arg_list[3].c_str() );
  x.alphabet = atoi( arg_list[4].c_str() );
  x.alphabet_case = atoi( arg_list[5].c_str() );
  x.ascii = atoi( arg_list[6].c_str() );

  return x;
}



void password_list_t::add_password_from_string( string password )
{
   password_list.push_back( read_from_string( password ) );
}

/*
 *  Generates a password given 
 *     "\"description\" length number alpha alpha_case ascii"
 */
string password_list_t::gen_password_string( string line )
{
   /* line should be in the following format
      "\"description\" length number alpha alpha_case ascii"
   */
  password_type x;
  stringstream buffer;
  vector<string> arg_list = get_arg_array( line );

  x.description = arg_list[0];
  x.length = atoi( arg_list[1].c_str() );
  x.number = atoi( arg_list[2].c_str() );
  x.alphabet = atoi( arg_list[3].c_str() );
  x.alphabet_case = atoi( arg_list[4].c_str() );
  x.ascii = atoi( arg_list[5].c_str() );
  x.text = create_password( x );

  buffer << x;
  return buffer.str();
}


ostream& operator << ( ostream& scr, password_list_t& x )
{
    for(  list<password_type>::iterator marker = x.password_list.begin();
			                             marker != x.password_list.end();
										 ++marker )
  {
    scr << *marker;
  }
  return scr;
}

ostream& operator << (ostream& scr , password_type& x )
{
  scr << "\"" << x.text << "\" \"" <<  x.description << "\" " <<  x.length << " " 
	  << x.number << " " <<  x.alphabet << " " <<  x.alphabet_case << " " <<  x.ascii << "\n";
  return scr;
}


string password_list_t::display_password( password_type x )
{
  stringstream display;

  display << "\nPassword:        " << x.text <<
	         "\nDescription:     " << x.description <<
			 "\nLength:          " << x.length <<
			 "\n----Contains---- " <<
			 "\nNumbers:         " << (( x.number ) ? "true" : "false") <<
			 "\nAlphabetic:      " << (( x.alphabet ) ? "true" : "false") <<
			 "\nCase Sensative:  " << (( x.alphabet_case ) ? "true" : "false") <<
			 "\nAscii:           " << (( x.ascii ) ? "true" : "false");
  return display.str();
}

 #endif 
