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

	2. DATE: Monday, July 23rd 2018
		By: Muhammad Umair

		Indent: Removed the custom indent in script 
				in favor of CLAN's indent script.
				Indent.exe is now a requirement
	3. DATE: Thrsday, July 26th 2018
		By: Muhammd Umair
		Utterance end marker:
		If there is a space+period combination at
		the end of an utterane, the new function will
		remove it.
		The utterance end marker is removed if there 
		is a latch symbol+period combination.

*/


#include "chat_ca.h"


	const static wchar_t newline = 0x000a;
	const static wchar_t at_symbol = 0x0040;
	const static wchar_t colon = 0x003a;
	const static wchar_t star = 0x002a;
	const static wchar_t space = 0x0020;
	const static wchar_t tab = 0x0009;
	const static wchar_t period = 0x002e;
	const static wchar_t letter_low_vertical = 0x02CC;
	const static wchar_t question_mark = 0x003f;
	const static wchar_t glottal_stop = 0x0294;
	const static wchar_t exclamation = 0x0021;
	const static wchar_t hash_symbol = 0x0023;
	const static wchar_t fullwidth_exclamation = 0xFF01;
	const static wchar_t latch_symbol = 0x2248;
	const static wchar_t less_sign = 0x003c;
	const static wchar_t greater_sign = 0x003e;
	const static wchar_t black_up_triangle = 0x25B2;
	const static wchar_t black_down_triangle = 0x25BC;
	const static wchar_t lower_one_eighth = 0x2581;
	const static wchar_t down_arrow = 0x2193;
	const static wchar_t left_white_triangle = 0x25C1;
	const static wchar_t upper_one_eighth = 0x2594;
	const static wchar_t up_arrow = 0x2191;
	const static wchar_t fisheye = 0x25c9;
	const static wchar_t combining_low_line = 0x0332;
	const static wchar_t Black_feathered_down_arrow = 0x27B4;
	const static wchar_t Black_feathered_up_arrow = 0x27B6;
	const static wchar_t left_paran = 0x0028;
	const static wchar_t right_paran = 0x0029;
	const static wchar_t left_square = 0x005b;
	const static wchar_t right_square = 0x005d;
	const static wchar_t double_integral = 0x222C;
	const static wchar_t degree = 0x00B0;
	const static wchar_t x = 0x0078;
	const static wchar_t caret = 0x005E;
	const static wchar_t smile_symbol = 0x263A;
	const static wchar_t pound_symbol = 0x00A3;
	const static wchar_t white_down_triangle = 0x2207;
	const static wchar_t white_up_triangle = 0x2206;
	const static wchar_t right_floor = 0x230B;
	const static wchar_t left_floor = 0x230A;
	const static wchar_t right_ceil = 0x2309;
	const static wchar_t left_ceil = 0x2308;
	const static wchar_t creaky_star = 0x204E;



// Default const.
chat_ca::chat_ca()
{
	meta_end = 0;
}



// Param const.
chat_ca::chat_ca(vector<wchar_t> all_file)
{
	// Finding the metadata end value.
	int len = 0;
	for ( unsigned i = 0 ;i < all_file.size() ; i++ )
	{
		if (all_file[i] == at_symbol)
			len = i;
		else
			break;
		while( all_file[i] != newline )
			i++;
	}
	meta_end = len;
}



// Function add
// Params: position and unicode symbol
/*
	Inserts the given unicode symbol
	at the specified position in the vector.
*/
void chat_ca::add(unsigned pos, wchar_t symbol, vector<wchar_t> &all_file)
{
	all_file.insert(all_file.begin()+pos, 1, symbol);
}
void chat_ca::add(unsigned pos, wchar_t symbol , vector<wchar_t> &all_file,int instances)
{
	all_file.insert(all_file.begin()+pos, instances, symbol);
}




// Function run
// Params: Vectors of wide chars byRef.
/*
	Runs all the modifier functions in the correct order.
	Issues that are being resolved:
	1. Changing the mid TCU period symbol.
	2. CHanging the mid TCU question marks.
	3. Changing the mid TCU exclamation.
	4. Converting the doubtful material markers.
		// **NOTE: Should be done before fast/slow start
		//			and overlap.
	5. Changing the very fast speech delimiters.
	6. Changing the very slow speech delimiters.
	7. Changing the smiley voice delimiters.
	8. Changing the creaky voice delimiters.
	9. Changing the loudness markers.
	10. Changing the overlap markers.
	11. Changing the fast talk delimiters.
	12. Changing the slow talk delimiters.
	13. Changing the comment markers.
	14. Changing the unintelligible speech markers.
	15. Changing the whisper delimiters.
	16. Changing the mid TCU upwards intonation markers.
	17. Changing the mid TCU downwards intonation markers.
	18. Changing lower one eighth.
	19. Changing upper one eighth.
	20. Changing the fast start symbols.
	21. Changing the turn initial TCU's.
*/
void chat_ca::run(vector<wchar_t> &all_file)
{
	if ( all_file.size() <= 0 )
	{
		cerr << "ERROR: File Empty\n";
		return;
	}

	// Changing the mid TCU period symbol
	std::vector<wchar_t> period_start = {letter_low_vertical};
	std::vector<wchar_t> period_end = {space};
	std::vector<wchar_t> period_start_f = {period};
	delim_pair(all_file, period_start, period_end, period_start_f, period_end,0,0,0);
	// Changing the mid TCU question marks
	std::vector<wchar_t> question_start = {glottal_stop};
	std::vector<wchar_t>  question_start_f = {question_mark};
	delim_pair(all_file,question_start,period_end,question_start_f,period_end,0,0,1);
	// Changing the mid TCU exclamation marks.
	std::vector<wchar_t> exclamation_start = {fullwidth_exclamation};
	std::vector<wchar_t> exclamation_start_f = {exclamation};
	delim_pair(all_file,exclamation_start,period_start_f,exclamation_start_f,period_start_f,0,0,0);
	// Converting the doubtful material delims.
	// **NOTE: Should be done before fast/slow start
	//			and overlap.
	std::vector<wchar_t> doubt_start = {less_sign};
	std::vector<wchar_t> doubt_end1 = {greater_sign,space,left_square,question_mark,right_square};
	std::vector<wchar_t> doubt_end2 = {greater_sign,left_square,question_mark,right_square};
	std::vector<wchar_t> doubt_start_f = {left_paran};
	std::vector<wchar_t> doubt_end_f = {right_paran};
	delim_pair(all_file,doubt_start, doubt_end1,doubt_start_f,doubt_end_f,0,0,0);
	delim_pair(all_file,doubt_start, doubt_end2,doubt_start_f,doubt_end_f,0,0,0);
	// Changing the very fast speech delimiters.
	std::vector<wchar_t> very_fast_start = {black_up_triangle};
	std::vector<wchar_t> very_fast_start_f = {greater_sign,greater_sign};
	std::vector<wchar_t> very_fast_end_f = {less_sign,less_sign};
	delim_pair(all_file,very_fast_start,very_fast_start,very_fast_start_f,very_fast_end_f,0,0,0);
	// Changing the very slow speech delimiters.
	std::vector<wchar_t> very_slow_start = {black_down_triangle};
	delim_pair(all_file,very_slow_start,very_slow_start,very_fast_end_f,very_fast_start_f,0,0,0);
	// Changing the smiley voice delimiters.
	std::vector<wchar_t> smiley_start = {smile_symbol};
	std::vector<wchar_t> smiley_end = {pound_symbol};
	delim_pair(all_file,smiley_start,smiley_start,smiley_end,smiley_end,0,0,0);
	// Changing the creaky voice delimiters.
	std::vector<wchar_t> creaky_start = {creaky_star};
	std::vector<wchar_t> creaky_end = {hash_symbol};
	delim_pair(all_file,creaky_start,creaky_start,creaky_end,creaky_end,0,0,0);
	// Changing the loudness markers.
	loud(all_file);
	// Changing the overlap markers.
	std::vector<wchar_t> overlap_start = {less_sign};
	std::vector<wchar_t> overlap_end = {greater_sign,space,left_square,greater_sign,right_square};
	std::vector<wchar_t> overlap_start_f = {left_ceil};
	std::vector<wchar_t> overlap_end_f = {right_ceil};
	std::vector<wchar_t> overlap_end2 = {greater_sign,space,left_square,less_sign,right_square};
	std::vector<wchar_t> overlap_start_f2 = {left_floor};
	std::vector<wchar_t> overlap_end_f2 = {right_floor};
	std::vector<wchar_t> overlap_end3 = {greater_sign,left_square,greater_sign, right_square};
	std::vector<wchar_t> overlap_end4 = {greater_sign,left_square,less_sign,right_square};
	delim_pair(all_file,overlap_start,overlap_end3,overlap_start_f,overlap_end_f,0,0,2);
	delim_pair(all_file,overlap_start,overlap_end4,overlap_start_f2,overlap_end_f2,0,0,2);
	delim_pair(all_file,overlap_start,overlap_end,overlap_start_f,overlap_end_f,0,0,2);
	delim_pair(all_file,overlap_start,overlap_end2,overlap_start_f2,overlap_end_f2,0,0,2);

	// **NOTE: Removing the custom indent function 
	//			in favor of the talkbank script.
	//indent(all_file);



	// Changing the fast talk delimiters
	std::vector<wchar_t> fast_talk = {white_up_triangle};
	std::vector<wchar_t> fast_start_f = {greater_sign};
	std::vector<wchar_t> fast_end_f = {less_sign};
	delim_pair(all_file,fast_talk,fast_talk,fast_start_f,fast_end_f,0,0,0);
	// Changing the slow talk delimiters.
	std::vector<wchar_t> slow_talk = {white_down_triangle};
	delim_pair(all_file,slow_talk,slow_talk,fast_end_f,fast_start_f,0,0,0);
	// Changing the comment markers.
	std::vector<wchar_t> comm_start = {left_square, caret, space};
	std::vector<wchar_t> comm_end = {right_square};
	std:: vector<wchar_t> comm_start_f = {left_paran,left_paran};
	std::vector<wchar_t> comm_end_f = {right_paran,right_paran};
	delim_pair(all_file,comm_start,comm_end,comm_start_f, comm_end_f,0,0,0);
	// Changing the unintelligible speech markers.
	std::vector<wchar_t> un_start = {x,x,x};
	std::vector<wchar_t> un_end = {space};
	std::vector<wchar_t> un_start_f = {right_paran,space,space,space,left_paran};
	delim_pair(all_file,un_start,un_end,un_start_f,un_end,0,0,0);
	// Changing the whisper delimiters.
	std::vector<wchar_t> whisper_start = {double_integral};
	std::vector<wchar_t> whisper_start_f = {degree,degree};
	delim_pair(all_file,whisper_start,whisper_start,whisper_start_f,whisper_start_f,0,0,0);
	// Changing the mid TCU upwards intonation symbols.
	std::vector<wchar_t> ui_start = {Black_feathered_up_arrow};
	std::vector<wchar_t> ui_end = {space};
	std::vector<wchar_t> ui_start_f = {combining_low_line,colon};
	delim_pair(all_file,ui_start,ui_end,ui_start_f,ui_end,0,0,0);
	// Changing the mid TCU downwards intonation symbols.
	std::vector<wchar_t> di_start = {Black_feathered_down_arrow};
	std::vector<wchar_t> di_start_f = {colon,combining_low_line};
	delim_pair(all_file,di_start,ui_end, di_start_f, ui_end,1,0,0);
	// Changing the mid TCU latching symbols.
	//std::vector<wchar_t> latch_start = {space1,latch_symbol1,space1};
	//std::vector<wchar_t> latch_start_f = {latch_symbol1};
	//delim_pair(all_file,latch_start,ui_end,latch_start_f,ui_end,0,0,0);
	latching(all_file,latch_symbol);
	// Changing the lower one eighth delimiters.
	std::vector<wchar_t> loe_start = {lower_one_eighth};
	std::vector<wchar_t> loe_start_f = {down_arrow,down_arrow};
	delim_pair(all_file,loe_start,loe_start,loe_start_f,loe_start_f,0,0,0);
	// Changing the upper one eighth delimiters.
	std::vector<wchar_t> uoe_start = {upper_one_eighth};
	std::vector<wchar_t> uoe_start_f = {up_arrow,up_arrow};
	delim_pair(all_file,uoe_start,uoe_start,uoe_start_f,uoe_start_f,0,0,0);
	// Changing the fast start symbols.
	std::vector<wchar_t> fast_start = { left_white_triangle};
	delim_pair(all_file,fast_start, un_end,fast_end_f,un_end,0,0,0);
	// Changing the turn initia TCU
	turn_initial_TCU(all_file);

	//**NOTE: Added to remove the CHAT utterance end marker
	rm_utterance_end(all_file);
	

}



// Function delim_pair
// Prams: vector file stream, starting delimiters pair,
//		  end delimiters pair.
/*
	Given the pair of starting delimiters and 
	the pair of ending delimiters, checks if the
	start pair occurs in the same TCU. If it does,
	replaces the vectors with the final pairs.
	**NOTE: This can also be used if there is no 
			pair by giving it a space as the second
			argument, since a space is always
			guaranteed to be present.
	Also has the ability to insert the new start or end
	delimiters a specified position forwards or backwards.
	Negative sign for backwards movement and positive for 
	forward movement has to be specified.
	Zero for no movement.
	**NOTE: Since this function adds at one position, if 
			there are more than one delimiters to be added,
			they should be in reverse order in the vector.
	The final parameter represents the additional case that 
	needs to be run for a particular issue before the changes
	are applied.
	For no additional check, the case is zero.
*/
void chat_ca::delim_pair(vector<wchar_t> &all_file, vector<wchar_t> start_delims, 
	vector<wchar_t> end_delims, vector<wchar_t> final_start, vector<wchar_t> final_end,
	 unsigned move_start, unsigned move_end, int check_case)
{
	bool found = false;
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		unsigned pos1;
		if (( all_file[i] == start_delims[0]) && ( found == false ))
		{
			pos1 = i;
			for ( unsigned j = 0 ; j < start_delims.size() ; j++ )
			{
				found = true;
				if ( all_file[i++] != start_delims[j])
				{
					found = false;
					break;
				}
			}
		}
		if ( all_file[i] == newline )
		{
			if ( all_file[i+1] == star)
				found = false;
		}
		// For overlap markers case number 2
		if ( check_case == 2 )
		{	
			if ( found == true  && all_file[i] == less_sign)
			{
				found = false;
				i--;
			}
		}
		if ( all_file[i] == end_delims[0] && found == true )
		{
			unsigned pos2 = i;
			bool found2 = true;
			for ( unsigned j = 0 ; j < end_delims.size() ; j++ )
			{
				if ( all_file[i++] != end_delims[j])
					found2 = false;
			}
			if (  found2 == true )
			{
				switch (check_case)
				{
					case 1: 
					{
						if ( mid_TCU_question_check1(all_file,pos1) == false )
							continue;
					}
				}
				for ( unsigned j = 0 ; j < start_delims.size() ; j++ )
					all_file.erase(all_file.begin()+pos1);
				for ( unsigned j = 0 ; j < final_start.size() ; j++ )
					add(pos1+move_start,final_start[j], all_file);
				unsigned diff =  start_delims.size() - final_start.size();
				pos2 -= diff;
				for ( unsigned j = 0 ; j < end_delims.size() ; j++ )
					all_file.erase(all_file.begin()+pos2);
				for ( unsigned j = 0 ; j < final_end.size() ; j++ )
					add(pos2+move_end, final_end[j] , all_file);
				found = false;
				i = pos1+1;					// **NOTE: Change in ca_chat at the end.
			}
		}
	}
}




// Function loud()
// Params: Vector file stream
/*
	Finds the loudness delimiters and capitalizes
	all capitalizable letters in b/w.
*/
void chat_ca::loud(vector<wchar_t> &all_file)
{
	bool first = false;
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		unsigned pos1;
		if ( all_file[i] == fisheye && first == false)
		{
			pos1 = i;
			first = true;
			i++;
		}	
		if ( all_file[i] == newline && all_file[i+1] == star )
			first = false;
		if ( all_file[i] == fisheye && first == true )
		{
			all_file.erase(all_file.begin()+pos1);
			for ( unsigned j = pos1 ; j < i-1 ; j++ )
			{
				if ( all_file[j] >= 0x0061 && all_file[j] <= 0x007a )
					all_file[j] -= 0x20;
			}
			all_file.erase(all_file.begin()+i-1);
			first = false;
		}
	}
}





// Function indent
// Params: Vector file stream.
/*
	Finds a pair of overlap markers and indents them
	to be in line with each other.
*/
void chat_ca::indent(vector<wchar_t> &all_file)
{
	unsigned col = 0;
	bool new_TCU = false, line1 = false, line2 = false;
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		unsigned pos1,pos2,col1,col2;
		col++;
		if ( all_file[i] == left_ceil )
		{
			pos1 = i;
			col1 = col;
			line1 = new_TCU;
		}
		if ( all_file[i] == newline && all_file[i+1] == star)
		{
			new_TCU = true;
			col = 0;
		}
		else if ( all_file[i] == newline)
		{
			new_TCU = false;
			col = 0;
		}
		if ( all_file[i] == left_floor)
		{
			pos2 = i;
			col2 = col;
			line2 = new_TCU;
			if ( col1 < col2)
			{
				unsigned diff = col2 - col1;
				if (( line1 == true && line2 == false) || ( line1 == false && line2 == true ))
					diff-=3;
				for ( unsigned j = 0 ; j < diff ; j++ )
				{
					add(pos1, space , all_file);
					i++;
				}
			}
			else
			{
				unsigned diff = col1 - col2;
 				if (( line1 == true && line2 == false) || ( line1 == false && line2 == true ))
					diff+=3;
				for ( unsigned j = 0 ; j < diff ; j++ )
				{
					add(pos2, space , all_file);
					i++;
				}
			}

		}
	}	
}


// Function turn_initial_TCU
// Params: vector file stream
/*
	Finds the first char of a turn after speaker
	ID and decapitalizes.
*/
void chat_ca::turn_initial_TCU(vector<wchar_t> &all_file)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if ( all_file[i] == colon && all_file[i+1] == tab)
		{
			i+=2;
			do
			{
				if (( all_file[i] >= 0x0061 && all_file[i] <= 0x007a ) || (all_file[i] >= 0x0041 && all_file[i] <= 0x005a ))
					break;
				i++;
			}while(all_file[i] != newline && all_file[i+1] != star); 
			if ( all_file[i] >= 0x0061 && all_file[i] <= 0x007a )
				all_file[i] -=0x20;
		}
	}
}




void chat_ca::latching(vector<wchar_t> &all_file,wchar_t delim)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if ( all_file[i] == delim )
		{
			if (( all_file[i-1] == space) && (all_file[i-1] != tab))
			{
				all_file.erase(all_file.begin()+i-1);
				i--;
			}
			if (( all_file[i+1] == space) || (all_file[i+1] == tab))
				all_file.erase(all_file.begin()+i+1);
		}
	}
}



bool chat_ca::mid_TCU_question_check1(vector<wchar_t> all_file, unsigned pos1)
{
	if ( all_file[pos1+1] == right_square && all_file[pos1-1] == left_square)
		return false;
	return true; 
}


// Function rm_utterance_end
// Params: Vector file stream.
// Does: Removes the end of utterance space + period
//		combination from every utterance.
void chat_ca::rm_utterance_end(vector<wchar_t> &all_file)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		bool check = false;
		unsigned pos = 0, pos2 = 0;
		if ((all_file[i-1] == space && all_file[i] == period) || (all_file[i-1] == latch_symbol && all_file[i] == period))
		{
			pos = i+1;
			pos2 = i;
			while (all_file[pos] != newline)
			{
				if ( all_file[pos] == 0x0015)
				{
					check = true;
					break;
				}
				if ( all_file[pos] != space && all_file[pos] != tab)
					break;
				pos++;
			} 
		}
		if (check == true)
			all_file.erase(all_file.begin()+pos2);
	}
}










































