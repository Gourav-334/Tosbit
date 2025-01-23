#include "../include/transition_tool.h"










/* Change one state to another as per the given state & input symbol.
PRECAUTION: Don't include string terminator in symbol[] or transition[]. 

function(input_symbol, array_of_symbols, one-to-one_mappings, current_state, else_state) */

void changeState(char input, char symbols[], char transition[], int *state, int dump)
{
	int index, commas=0, flag=FALSE;
	char str[4] = {0};



	for (int i=0; i<strlen(symbols); i++)
	{
		if (input==symbols[i]) {index = i; flag = TRUE; break;}
	}



	if (flag==FALSE) {*state = dump;}

	else if (flag==TRUE)
	{
		for (int i=0; i<strlen(transition); i++)
		{
			if (transition[i]==',' && commas<index) {commas++;}
			else if (transition[i]!=',' && commas==index) {str[strlen(str)] = transition[i];}
			else if (transition[i]==',' && commas==index) {break;}
			else {continue;}
		}

		*state = atoi(str);
	}
}










/* Sets up the break condition as per a given state. 

function(current_state, state_to_set_brk_TRUE, current_break_value) */

void breakValue(int *state, int breakState, int *brk)
{
	if (*state==breakState) {*brk = TRUE;}
}










/* Appends a character to a given string.

function(current_state, state_to_allow_append, string, character_to_add) */

void appendState(int *state, int breakState, char *target, char value)
{
	if (*state==breakState) {target[strlen(target)] = value;}
}










/* Checks limit of a string & changes state and sets break value to TRUE if limit is crossed.

function(string_to_check, limit_set, current_state, new_state, current_break_value) */

void limitChecker(char *target, int limit, int *state, int newState, int *brk)
{
	if (strlen(target)>=limit) {*state = newState; *brk = TRUE;}
}



