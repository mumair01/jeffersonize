#include "ca_chat.h"


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
	const static wchar_t bullet = 0x0015;
	const static wchar_t creaky_star = 0x204E;



// Default const.
ca_chat::ca_chat()
{
	meta_end = 0;
}


// Param const.
ca_chat::ca_chat(vector<wchar_t> all_file)
{
	// Finding the metadata end value
    int len = 0;
	for ( unsigned i = 0 ;i < all_file.size() ; i++ )
	{
		if (all_file[i] == at_symbol )
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
void ca_chat::add(unsigned pos, wchar_t symbol, vector<wchar_t> &all_file)
{
	all_file.insert(all_file.begin()+pos, 1, symbol);
}
void ca_chat::add(unsigned pos, wchar_t symbol , vector<wchar_t> &all_file,int instances)
{
	all_file.insert(all_file.begin()+pos, instances, symbol);
}


// Function run
// Params: vector of wide chars byRef
/*
	Runs all the modifier functions in the correct orrder.
	Issues that are being resolved:
	1. Adding CHAT speaker ID asterisk.
	2. Changing mid TCU Period marker.
	3. Changing the mid TCU question marks.
	4. Changing the mid TCU exclamation marks.
	5. Adding the TCU end terminators.
	6. Replacing creaky voice delimiters.
	7. Replacing the double up arrows.
	8. Replacing the double down arrows.
	9. Replacing the smiley voice delimiters.
	10. Replacing the very fast speech delimiters.
	11. Replacing the very slow speech delimiters.
	12. Changing the mid TCU upwards intonation shifts.
	13. Changing the mid TCU downwards intonation shifts.
	14. Changing the comments markers.
		// **NOTE: Comments should be changed BEFORE doubtful markers.
	15. Changing the whisper markers.
	16. Changing the single out carats delimiters.
		// **NOTE: This should only be done after 
		//		   changing the very slow and very fast
		//		   delimiters.
	17. Changing the single in carats delimiters.
		// **NOTE: This should only be done after 
		//		   changing the very slow and very fast
		//		   delimiters.
	18. Changing the fast start delimiters.
	19. Changing the doubtful material markers.
		// **NOTE: Should be applied after the single out 
		//		   and in carat functions.
	20. Changing the  overlap markers
	21. Changing the loudness markers.
	22. CHanging the unintelligible speech markers.
	23. Capitalizing turn initial TCU.
	24. Adding spaces to the latch symbol.
	25. Removing extra metadata, spaces, and lines.
	26. Adding the eof marker.
*/	   
void ca_chat::run(vector<wchar_t> &all_file)
{
	if ( all_file.size() <= 0 )
	{
		cerr << "ERROR: File Empty\n";
		return;
	}

	// Adding speaker_ID asterisk
	add_speaker_ID(all_file);
	// Changing mid TCU period
	mid_TCU_exec_ques(all_file,period,letter_low_vertical);
	mid_TCU_period_correct(all_file);
	// Changing mid TCU question
	mid_TCU_exec_ques(all_file, question_mark,glottal_stop);
	// Changing mid TCU exclamation
	mid_TCU_exec_ques(all_file,exclamation,fullwidth_exclamation);
	// Adds TCU terminators
	space_period(all_file);
	// Replacing the creaky voice delimiters.
	simple_replace_double(all_file,hash_symbol,creaky_star,1);
	// Replacing double down arrows.
	simple_replace_double(all_file,down_arrow,lower_one_eighth,2);
	// Replacing double up arrows.
	simple_replace_double(all_file,up_arrow,upper_one_eighth,2);
	// Replacing the smiley voice delimiters.
	simple_replace_double(all_file,pound_symbol,smile_symbol,1);
	// Changing the very fast speech delims.
	std::vector<wchar_t> vf_start = {greater_sign,greater_sign};
	std::vector<wchar_t> vf_end = {less_sign,less_sign};
	std::vector<wchar_t> vf_start_f = { black_up_triangle};
	delim_pair(all_file,vf_start,vf_end,vf_start_f,vf_start_f,0,0,0);
	//Changing the very slow speech delimiters.
	std::vector<wchar_t> vs_start_f = {black_down_triangle};
	delim_pair(all_file,vf_end,vf_start,vs_start_f,vs_start_f,0,0,0);
	// Changing the mid TCU upwards intonation symbols.
	std::vector<wchar_t> di_start = {colon,combining_low_line};
	std::vector<wchar_t> di_start_f = {Black_feathered_up_arrow};
	std::vector<wchar_t> di_end_f = {space};
	delim_pair(all_file,di_start,di_end_f,di_start_f,di_end_f,0,0,0);
	// Changing the mid TCU downwards intonation symbols.
	std::vector<wchar_t> ui_start = {combining_low_line,colon};
	std::vector<wchar_t> ui_start_f = {Black_feathered_down_arrow};
	delim_pair(all_file,ui_start,di_end_f,ui_start_f,di_end_f,-1,0,0);
	// Changing the comments markers
	// **NOTE: Comments should be changed BEFORE doubtful markers.
	std::vector<wchar_t> com_start = {left_paran,left_paran};
	std::vector<wchar_t> com_end = {right_paran,right_paran};
	std::vector<wchar_t> com_start_f = {space, caret, left_square};
	std::vector<wchar_t> com_end_f = {right_square,space};
	delim_pair(all_file,com_start,com_end,com_start_f,com_end_f,0,0,0);
	// Changing the whisper markers.
	std::vector<wchar_t> whisper_start = {degree,degree};
	std::vector<wchar_t> whisper_end = {double_integral};
	delim_pair(all_file,whisper_start, whisper_start, whisper_end, whisper_end, 0,0,0);
	// Changing the single out carats deliminters.
	// **NOTE: This should only be done after 
	//		   changing the very slow and very fast
	//		   delimiters.
	std::vector<wchar_t> single_out_start = {less_sign};
	std::vector<wchar_t> single_out_end = {greater_sign};
	std::vector<wchar_t> single_out_start_f = {white_down_triangle};
	delim_pair(all_file,single_out_start, single_out_end, single_out_start_f, single_out_start_f,0,0,0);
	// Changing the single in carats delimiters.
	// **NOTE: This should only be done after 
	//		   changing the very slow and very fast
	//		   delimiters.
	std::vector<wchar_t> single_in_f = {white_up_triangle};
	delim_pair(all_file,single_out_end,single_out_start, single_in_f,single_in_f,0,0,0);
	// Changing the fast start delimiters.
	simple_replace_double(all_file,less_sign,left_white_triangle,1);
	// Changing the doubtful material markers.
	// **NOTE: Should be applied after the single out 
	//		   and in carat functions.
	std::vector<wchar_t> doubt_start = {left_paran};
	std::vector<wchar_t> doubt_end = {right_paran};
	std::vector<wchar_t> doubt_start_f = {less_sign};
	std::vector<wchar_t> doubt_end_f = {right_square,question_mark,left_square,space,greater_sign};
	delim_pair(all_file , doubt_start , doubt_end , doubt_start_f , doubt_end_f , 0 , 0,1);
	// Converting the first part of the overlap marker.
	std::vector<wchar_t> overlap_end_f = {right_square, greater_sign, left_square, space, greater_sign};
	std::vector<wchar_t> overlap_start_f = {less_sign};
	std::vector<wchar_t> overlap_start = {left_ceil};
	std::vector<wchar_t> overlap_end = {right_ceil};
	delim_pair(all_file, overlap_start,overlap_end,overlap_start_f, overlap_end_f, 0,0,0);
	// Converting the second part of the overlap markers.
	std::vector<wchar_t> overlap_end_f2 = {right_square,less_sign,left_square,space,greater_sign};
	std::vector<wchar_t> overlap_start2 = {left_floor};
	std::vector<wchar_t> overlap_end2 = {right_floor};
	delim_pair(all_file,overlap_start2,overlap_end2,overlap_start_f,overlap_end_f2,0,0,0);
	// Changing the loudness delimiters.
	loud(all_file);
	// Changing the unintelligible speech markers
	std::vector<wchar_t> unintelligible_start = {left_paran,space,space,space,right_paran};
	std::vector<wchar_t> unintelligible_end = {space};
	std::vector<wchar_t> unintelligible_start_f = {x,x,x};
	delim_pair(all_file,unintelligible_start,unintelligible_end,unintelligible_start_f,unintelligible_end,0,0,0);
	// Capitalizing the turn initial TCU
	turn_initial_TCU(all_file);
	// Adding spaces to the latch symbol.
	latching(all_file,latch_symbol);
	// Removing additional spaces
	line_space(all_file,3);
	// Removing additional metadata
	remove_extra_metadata(all_file);
	// Removing extra line.
	remove_extra_line(all_file);
	// Adding the eof marker.
	add(all_file.size() , '\0' , all_file);
}



// Function add_speaker ID
// Params: file stream
/*
	Traverses through file stream.
	Finds where speaker ID is and adds
	the delimiter before the ID.
*/
void ca_chat::add_speaker_ID(vector<wchar_t> &all_file)
{

	// Checking if the delimiters need to be added.
	bool add_ID = true;
	for (unsigned i = 0 ; i < all_file.size() ; i++ )
	{
		if ( all_file[i] == star)
		{
			add_ID = false;
			break;
		}
		while( all_file[i] != newline && i < all_file.size() )
			i++;
	}

	if ( add_ID == false )
		return;

	// Going through vector and changing delimiters
	// if condition is met.
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		int pos = 0;
		bool found_ID = false;
		if ( all_file[i] == newline )
		{
			pos = i+1;
			int thresh = 10, count = 0;
			while( count < thresh )
			{
				count++;
				i++;
				if ( all_file[i] == newline )
					break;
				if ( all_file[i] == colon )
				{
					if ( all_file[++i] == tab )
					{
						found_ID = true;
						break;
					}
				}
			}
			if ( found_ID == true )
				add(pos,star,all_file,1);
		}
	}

	return;
}




// Function: analyze_mid_TCU_period()
// Params: file stream vector
//			delimiters to replace.
/*
	Goes through the vector stream.
	If start_delim is found and is not
	at the end of a TCU, it 
	is replaced by the end_delim.
*/
void ca_chat::mid_TCU_exec_ques(vector<wchar_t> &all_file, wchar_t start_delim, wchar_t end_delim)
{
	// Going through file.
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if (all_file[i] == start_delim  && all_file[i-1] != left_square && all_file[i+1] != right_square)
		{
			unsigned count = i;
			do
			{
				count++;
			}while((all_file[count] == space ) || (all_file[i] == tab ));
			if ( all_file[count] != bullet)
			{
				all_file.erase(all_file.begin()+i);
				add(i,end_delim,all_file,1);
			}
			else
			{
				while( all_file[count] != newline )
					count++;
				if (( all_file[count+1] != star ) && (all_file[count+1] != at_symbol))
				{
					all_file.erase(all_file.begin()+i);
					add(i,end_delim,all_file,1);
				}
			}
		}
	}
}



// Function space_period
// Params: file stream vector
/*
	If a bullet is encountered, checks if 
	last element is not a terminator and next
	line has speaker ID. If this is the case,
	adds a line teminator.
*/
void ca_chat::space_period(vector<wchar_t> &all_file)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if ( all_file[i] == bullet)
		{
			unsigned count1 = i, count2 = i;
			bool check1 = false, check2 = false;
			do
			{
				count1--;
			}while(( all_file[count1] == space  || all_file[count1] == tab ) && (count1 < all_file.size() - 1 ));
			if (( all_file[count1] != period) && (all_file[count1] != question_mark ) && (all_file[count1] != exclamation))
				check1 = true;
			do
			{
				count2++;
			}while(( all_file[count2] != newline ) && (count2 < all_file.size() - 1));
			count2++;
			if ( all_file[count2] == star)
				check2 = true;
			if ( check1 == true && check2 == true )
			{
				add(count1+1,space,all_file,1);
				add(count1+2,period,all_file,1);
				i+=2;
			}
			while( all_file[i] != newline)
				i++;
		}
	}
}


// Function simple_replace.
// Params: stream of vectors, unicode delimiter values 
//		   for symbols to be repalced and num of 
//		   delimiters to be replaced.
/*
	Goes through the vector stream until the first delim
	is found. Deletes the given num of delims after 
	confirming that it is part of a piar within the 
	same TCU.
	Then adds the new delmiiters in place of the 
	deleted delimiters.
*/
void ca_chat::simple_replace_double(vector<wchar_t> &all_file, wchar_t start_delim, wchar_t end_delim, int amount)
{
	bool first = false;
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		int pos1;
		if ( all_file[i] == start_delim && first == false )
		{
			first = true;
			pos1 = i;
			i+= amount;
		}

		if ( all_file[i] == newline )
		{
			if ( all_file[i+1] == star )
				first = false;
		}

		if ( all_file[i] == start_delim && first == true )
		{
			first = false;
			for ( int j = 0 ;j < amount ; j++ )
			{
				all_file.erase(all_file.begin()+pos1);
			}
			add(pos1,end_delim,all_file,1);
			for ( int j = 0 ; j < amount ; j++ )
			{
				all_file.erase(all_file.begin()+i- (amount - 1 ));
			}
			add(i,end_delim,all_file,1);
		}
	}
}


// Function latching
// Params: Vector stream and value of latching delim.
/*
	Finds the latching delim and adds spaces before 
	and after it if not already present.
*/
void ca_chat::latching(vector<wchar_t> &all_file, wchar_t delim)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if ( all_file[i] == delim )
		{
			if (( all_file[i-1] != space) && (all_file[i-1] != tab))
			{
				add(i,space,all_file);
				i++;
			}
			if (( all_file[i+1] != space) && (all_file[i+1] != tab))
			{
				add(i+1,space,all_file);
				i++;
			}
		}
	}
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
void ca_chat::delim_pair(vector<wchar_t> &all_file, vector<wchar_t> start_delims, 
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
						if  (check_doubtful_case1(all_file,pos1,pos2) == false)
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
			}
		}
	}
}


// Function line_space
// Params: Vector file stream. Threshold representing the 
//		   amount of successive spaces after which deletion
//		   should occur.
/*
	Deletes successive spaces greater than the threshold 
	specified.
*/
void ca_chat::line_space(vector<wchar_t> & all_file, unsigned threshold)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if (( all_file[i] == space ) && (all_file[i+1] == space ))
		{
			unsigned pos1 = i;
			unsigned count = 0;
			while( all_file[i++] == space )
				count++;
			if ( count >= threshold)
			{
				for ( unsigned j = 1 ; j < count ; j++ )
				{
					all_file.erase(all_file.begin()+pos1);
				}
			}
		}
	}
}




// Function mid_TCU_period_correct
// Params: vector file stream
/*
	The mid_TCU_exec_ques function might change 
	a period inside a pause indicator.
	Rectifies that problem.
*/
void ca_chat::mid_TCU_period_correct(vector<wchar_t> &all_file)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if ( all_file[i] == letter_low_vertical )
		{
			unsigned pos1 = i, pos2 = i;
			do
			{
				pos1--;
			}while( all_file[pos1] >= 0x0030 && all_file[pos1] <= 0x0039 );
			do
			{
				pos2++;
			}while( all_file[pos2] >= 0x0030 && all_file[pos2] <= 0x0039 );
			if (( all_file[pos1] == left_paran && all_file[pos2] == right_paran ) || (all_file[i+1] == newline))
			{
				all_file.erase(all_file.begin()+i);
				add(i,period,all_file);
			}
		}
	}
}



// Function loud
// Params:  File stream vector
/*
	Finds any successive capital letters except 
	for speaker ID, converts them to small and 
	adds the loud speech delimiters.
	**NOTE: Always use AFTER the line_space function.
*/
void ca_chat::loud(vector<wchar_t> &all_file)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if (( all_file[i] >= 0x0041 && all_file[i] <= 0x005a ) && (all_file[i+1] != space))
		{
			bool ID = false, next = false;
			unsigned pos1 = i,count = 0;
			vector<wchar_t> chars;
			do
			{
				chars.push_back(all_file[i]);
				if (( all_file[i] >= 0x0041 && all_file[i] <= 0x005a ) && ( count > 0) )
					next = true;
				if (all_file[i] < 0x0061 || all_file[i] > 0x007a )
					count++;
				if ( all_file[i] >= 0x0061 && all_file[i] <= 0x007a )
					break;
				if (all_file[i] == colon && all_file[i+1] == tab)
				{
					ID = true;
					break;
				} 
				i++;
			}while(all_file[i] != newline || all_file[i+1] != star);
			if (( ID == false ) && ( count > 2 ) && (next == true ))
			{
				int index = 0;
				for ( unsigned j = 0 ; j < chars.size() ; j++ )
				{
					if (chars[j] >= 0x0041 && chars[j] <= 0x005a )
					{
						index = j;
						chars[j] += 0x20;
					}
					all_file.erase(all_file.begin()+pos1+j);
					add(pos1+j,chars[j],all_file);
				}
				add(pos1,fisheye,all_file);
				add(pos1+index+2, fisheye,all_file);
			} 
		}
	}
}



// Function check_doubtful_case1
// Params: Vector file stream and position range to check.
/*
	Returns true is doubtful marker changes need to be made,
	which is when there is an alphabet b/w parantheses.
*/
bool ca_chat::check_doubtful_case1(vector<wchar_t> all_file, unsigned pos1, unsigned pos2)
{
	for ( unsigned i = pos1 ; i < pos2 ; i++ )
	{
		if ( all_file[i] == left_paran && all_file[i+1] == period && all_file[i+2] == right_paran )
			return false;
		if (( all_file[i] >= 0x0061 && all_file[i] <= 0x007a ) || (all_file[i] >= 0x0041 && all_file[i] <= 0x005a )) 
			return true;
		if ( all_file[i] == right_paran )
			return false;
	}
	return false;

}



// Function turn_initial_TCU
// Params: Vector file stream.
/*
	Finds the end of the speaker ID and 
	decapitalizes the next decapitalizable character.
	Also removes extra space from in front of the speaker ID.
*/
void ca_chat::turn_initial_TCU(vector<wchar_t> &all_file)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if (all_file[i] == colon && all_file[i+1] == tab )
		{
			i+=2;
			do
			{
				if (( all_file[i] >= 0x0061 && all_file[i] <= 0x007a ) || (all_file[i] >= 0x0041 && all_file[i] <= 0x005a ))
					break;
				if ( all_file[i] == space || ( all_file[i] == tab ))
					all_file.erase(all_file.begin()+i);
				else
					i++;
			}while( all_file[i] != newline && all_file[i+1] != star);
			if ( all_file[i] >= 0x0041 && all_file[i] <= 0x005a)
				all_file[i] += 0x20;
		}
	}
}



// Function remove_extra_metadata
// Params: Vector file stream
/*
	Removes all metadata before @begin.
*/
void ca_chat::remove_extra_metadata(vector<wchar_t> &all_file)
{
	for ( unsigned i = 0 ; i < meta_end ; i++ )
	{
		if ( all_file[i] == at_symbol && all_file[i+1] == 0x0042 && all_file[i+2] == 0x0065)
		{
			for ( unsigned j = 0 ; j < i ; j++ )
			{
				all_file.erase(all_file.begin());
				meta_end--;
			}
			return;
		}
	}
}



// Function remove_extra_lines
// Params: Vector file stream
/*
	Removes one of any two successive lines from 
	the stream.
*/
void ca_chat::remove_extra_line(vector<wchar_t> &all_file)
{
	for ( unsigned i = meta_end ; i < all_file.size() ; i++ )
	{
		if ( all_file[i] == at_symbol && all_file[i+1] == 0x0045 && all_file[i+2] == 0x006e && all_file[i+3] == 0x0064 )
		{
			i+= 4;
			while( all_file[i] == newline && i < all_file.size())
				all_file.erase(all_file.begin()+i);
			return;
		}
		unsigned count = 0;
		if (all_file[i] == newline && all_file[i+1] == newline )
		{
			unsigned pos = i;
			while(all_file[i] == newline && i < all_file.size())
			{
				i++;
				count++;
			}
			for ( unsigned j = 0 ; j < count - 1 ; j++ )
				all_file.erase(all_file.begin()+pos);
		}
	}
}














