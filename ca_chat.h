/*
	Class containing all the  modifier 
	functions for conversion from CAlite 
	to CHAT.
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

#ifndef CA_CHAT_H_
#define CA_CHAT_H_




class ca_chat
{
	private:

		// End of the metadata vector position.
		unsigned meta_end;

	public:

		// Default const.
		ca_chat();

		// Param const.
		ca_chat(vector<wchar_t>);

		// Main function
		void run(vector<wchar_t> &);

		// Add symbols to vector.
		void add(unsigned, wchar_t, vector<wchar_t> &);
		void add(unsigned, wchar_t,vector<wchar_t> &, int);

		// Modifier functions.
		void add_speaker_ID(vector<wchar_t> &);
		void mid_TCU_exec_ques(vector<wchar_t> &, wchar_t, wchar_t );
		void space_period(vector<wchar_t> &);
		void simple_replace_double(vector<wchar_t> &, wchar_t, wchar_t, int);
		void latching(vector<wchar_t> &, wchar_t);
		void delim_pair(vector<wchar_t> &, vector<wchar_t> , vector<wchar_t>, vector<wchar_t>,
		 vector<wchar_t>, unsigned, unsigned, int);
		void line_space(vector<wchar_t> &, unsigned);
		void mid_TCU_period_correct(vector<wchar_t> &);
		void loud(vector<wchar_t> &);
		bool check_doubtful_case1(vector<wchar_t> , unsigned,unsigned);
		void turn_initial_TCU(vector<wchar_t> &);
		void remove_extra_metadata(vector<wchar_t> &);
		void remove_extra_line(vector<wchar_t> &);
};	




#endif






