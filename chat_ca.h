/*
	Class containing all the modifier 
	functions for conversion from 
	CHAT to CAlite.
*/


/*
	Updates:
	1. DATE: Monday, July 16th 2018
		BY: Muhammad Umair
		
		Speaker ID asterisk
		In line with user feedback, the 
		program no longer removes the turn
		initial asterisk before the speaker 
		ID.
		The remove speaker_ID function was removed.

*/


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <locale>
#include <codecvt>
#include <exception>
#include <unistd.h>
using namespace std;


#ifndef CHAT_CA_H_
#define CHAT_CA_H_

class chat_ca 
{
	private:
		// End of of the metadata vector postition.
		unsigned meta_end;

	public:
		// Default const.
		chat_ca();

		// Param const.
		chat_ca(vector<wchar_t>);

		// Main function.
		void run(vector<wchar_t> &);

		// Add symbols to vector.
		void add(unsigned, wchar_t, vector<wchar_t> &);
		void add(unsigned, wchar_t,vector<wchar_t> &, int);

		// Modifier functions.
		void delim_pair(vector<wchar_t> &, vector<wchar_t> , vector<wchar_t>, vector<wchar_t>,
		 vector<wchar_t>, unsigned, unsigned, int);
		void loud(vector<wchar_t> &);
		void indent(vector<wchar_t> &);
		void turn_initial_TCU(vector<wchar_t> &);
		void latching(vector<wchar_t> &,wchar_t);
		bool mid_TCU_question_check1(vector<wchar_t> , unsigned);
		void rm_utterance_end(vector<wchar_t> &);
};



#endif