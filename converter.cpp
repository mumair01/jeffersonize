

#include "converter.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include <locale>
#include <codecvt>
#include <exception>
#include <unistd.h>
using namespace std;

const char *create_char_point(string);

// Function file_exists
// Params : string byRef
// Does; Returns true if the file exists, false otherwise
inline bool file_exists(const string &name)
{
	ifstream f(name.c_str());
    return f.good();
}



// Default Consturctor.
converter::converter()
{
	path_CA = "";
}


// Param Const.
converter::converter(const string path, const string path2, const string t )
{
	path_CA = path;
	path_CHAT = path2;
	type = t;
}


// Function read_file
// Params: None
/* 
	Reads the file to a wchar_t vector.
	Returns false for an error.
*/
bool converter::read_file()
{	
	wchar_t c;
	string path_read;
	if ( type == type1)
		path_read = path_CA;
	else if ( type == type2)
		path_read = path_CHAT;
	// open as a byte stream
    std::wifstream fin(path_read, std::ios::binary);
    // apply BOM-sensitive UTF-8 facet
    fin.imbue(std::locale(fin.getloc(),
       new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    if ( ! fin.is_open())
    {
    	cerr << "ERROR: File failed to open\n";
    	return false;
    }

    while( ! fin.eof())
    {
    	fin.get(c);
    	all_file.push_back(c);
    }

    return true;

}


// Function out_file
// Params: Path to the CHAT/output file.
/*
	Writes the entire vector of wchar_t to the 
	output file.
	Returns false for an error.
*/
bool converter::out_file(const string temp)
{

	// Opening a UTF-8 temp file for writing.
    std::wofstream fout(temp, std::ios::binary);
    // apply BOM-sensitive UTF-8 facet
    fout.imbue(std::locale(fout.getloc(),
       new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    if ( ! fout.is_open() )
    {
    	cerr << "ERROR: Output file failed to open. Check Permissions\n";
    	return false;
    }
    // Going through the vector.
	for (vector<wchar_t>::iterator i = all_file.begin() ;i !=  all_file.end() ; ++i )
		fout << *i;

	return true;
}

// Function run();
// Params: None
// Does: Main function executing all modifiers.
void converter::run()
{
	bool run1 = read_file();
	if ( run1 == false )
	{
		cerr << "ERROR: File failed to open\n";
		return;
	}

	// Conversion functions.
	if ( type == type1)
	{
		ca_chat bmain(all_file);
		bmain.run(all_file);
		out_file(path_CHAT);
	}
	else if ( type == type2)
	{
		chat_ca bmain(all_file);
		bmain.run(all_file);
		out_file(path_CA);
	}
}






























