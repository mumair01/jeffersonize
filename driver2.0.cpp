/*
	UPDATES:
	1. DATE: Tuesday, July 24th 2018
		BY:	   Muhammad Umair
			Removed rhe check extension feature because
			it made the converter difficult to use.
			**NOTE: This may expose the program to 
					potential issues.

	2. DATE: Thursday, August 2nd 2018
		BY: Muhammad Umair
			As part of changing the name of the program
			to jeffersonize, changed any references of 
			converter to jeffersonize.
*/
/*
	Main Driver file for the 
	bi-directional conveter.
*/



#include <string.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include "converter.h"

using namespace std;

// Function definitions
inline bool file_exists(const string &);
void ca_chat( char const * []);
void chat_ca( char const * []);
char *create_char_point(char const * []);
bool check_extension(char *, char *);
string generate_output_file_path(string,string,string, string &,string &);

int main(int argc, char const *argv[])
{
	if ( argc != 3 )
	{
		cerr << endl;
		cerr << "Usage: ./jeffersonize [calite2chat OR chat2calite] [directory]\n";
	    cerr << endl;
		return 0;
	}
	// Checking if the file exists.
	if ( ! file_exists(argv[2]))
	{
		cerr << "ERROR: File does not exist\n";
		return 0;
	}
	// Calling the appropriate converter function
	cout << argv[1] << endl;
	if ( strcmp(argv[1], "calite2chat") == 0 )
		ca_chat(argv);
	else if ( strcmp(argv[1] , "chat2calite") == 0 )
		chat_ca(argv);
	else
		cout << "ERROR: Incorrect conversion type specified\n";
	
	return 0;
}



// Function file_exists
// Params : string byRef
// Does; Returns true if the file exists, false otherwise
inline bool file_exists(const string &name)
{
	ifstream f(name.c_str());
    return f.good();
}

// Functions ca_chat
// Does: Runs the main ca-chat converter.
void ca_chat( char const *argv[])
{
	//char *path = create_char_point(argv);
	char *ext = new char[3];
	ext[0] = '.', ext[1] = 'c',ext[2] = 'a';
	//if( check_extension(path,ext) == false )
	//	return;
	string in_file_name, out_file_name;
	string out_path = generate_output_file_path(argv[2], "S.ca", "cha", in_file_name, out_file_name);
	delete [] ext;
	// Interface messages.
	cout << endl;
	cout << "jeffersonize performing analysis:\n";
	cout << "From file: <" << in_file_name << ">\n";
	cout << "Output file: <" << out_file_name << ">\n";
	cout << endl;
	string file_arg = argv[2];
	converter mainb(file_arg,out_path,"calite2chat");
	mainb.run();
}

// Function chat_ca
// Does: Runs the main chat to ca converter
void chat_ca( char const *argv[])
{
	//char *path = create_char_point(argv);
	char *ext = new char[4];
	ext[0] = '.', ext[1] = 'c' , ext[2] = 'h', ext[3] = 'a';
	//if (check_extension(path,ext) == false )
	//	return;
	string in_file_name, out_file_name;
	string out_path = generate_output_file_path(argv[2], "cha", "S.ca", in_file_name, out_file_name);
	delete [] ext;
	// Interface messages.
	cout << endl;
	cout << "jeffersonize performing analysis:\n";
	cout << "From file: <" << in_file_name << ">\n";
	cout << "Output file: <" << out_file_name << ">\n";
	cout << endl;
	string file_arg = argv[2];
	converter mainb(out_path,file_arg,"chat2calite");
	mainb.run();
}


// Function create_char_point
// Does: Convertes file name to dynamic a char pointer.
char * create_char_point(char const *argv[])
{
	string file_arg = argv[2];
	char *path = new char[file_arg.length()];
	for ( unsigned i = 0 ;i < file_arg.length() ; i++ )
	{
		path[i] = argv[2][i];
	}
	return path;
}

// Function check_extension
// Does: Verifies the file extension.
bool check_extension(char *path, char *intended_ext)
{
	char *ext = strrchr(path,'.');
	if (( ext == NULL) || ( strcmp(ext,intended_ext) != 0 ))
	{
		cerr << "ERROR: Wrong file extension.\n";
		return false;
	}
	return true;
}

// Function generate_output_file_path
// Does: Generates the name of the output
//		 file path and the output file,
string generate_output_file_path(string path,string ext,string new_ext,
	 string &in_file_name, string &out_file_name)
{
	// Generating the original file name
	std::size_t pos1 = path.find_last_of("/")+1;
	in_file_name = path.substr(pos1);
	// Generating the output file path
	std::size_t pos2 = path.find(ext);
	path = path.substr(0,pos2) + new_ext;
	// Generating the output file name
	std::size_t pos3 = path.find_last_of("/") +1;
	out_file_name = path.substr(pos3);
	return path;
}























