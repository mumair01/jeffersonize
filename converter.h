/*
	A somewhat generic class, responsible for 
	file manipulation and type verification.
*/


#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "ca_chat.h"
#include "chat_ca.h"
#include <string>
#include <vector>
using namespace std;



class converter
{
	private:

		// Storing the file.
		vector<wchar_t> all_file;

		// The path to the CA file.
		string path_CA;

		// Path to the CHAT file.
		string path_CHAT;

		// Type of the converter,
		string type;

		// Definition for the type of conveters
		const string type1 = "calite2chat";
		const string type2 = "chat2calite";


	public:

		// Default constructor
		converter();

		// Param const.
		converter(const string, const string, const string);

		// Read file.
		bool read_file();

		// Writes the current stream to file.
		bool out_file(const string);

		// Runs the converting class.
		void run();


};


#endif





















































