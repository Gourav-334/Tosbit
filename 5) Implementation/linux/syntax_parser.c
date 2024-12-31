/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "syntax_parser.h"










/*

STATISTICS:

Total DFA states: 				46

Total error types: 				10+
Total acknowledgement types:	5+

Total strange bugs:				5
Total silly bugs:				4

Search code: checkTableExistence

*/










/*

TO DEBUG:

i) For some reason, an extra character is getting read, leaving a blank or '\n'.
ii) The state remains the last one for some reason.
iii) Even if user passes a blank command, the stdin takes an invisible character.
iv) If a database is found to exist, the same database can't be found the next time.
v) memset() functions are getting skipped for unknown reason.
vi) Not only string formatting functions but my own strappend() is recursively adding the varaible
(if mentioned), not the directly passed strings. It has to do something with strappend() only, encrypter
is derived from it.
vii) Case 9, buffer has first character as space after emptying or maybe doesn't empty properly.



SOLUTION:

i) We terminate the loop after reading the 2nd last character of entered string (excluding the
unexpected character).
ii) Change the state to 0 after line analysis is complete, bloody fool!
iii) Bandage the program by assuming having read a character (continue from 2nd character).
iv) Check the formatted string function & state transitions.
v) It isn't skipped! You are trying to print the string after emptying it, idiot!
vi) Something is wrong with either variable "database" or the functions, or even variable "directory".
vii) First check if it is being emptied properly or not & then bandage it if required.

*/














/* The automaton, each state has to be defined for all situations. */

void syntaxParser(char username[])
{



	while (TRUE)
	{
		printf("TOS> ");
		fgets(command, COMMAND_MAX_LENGTH, stdin);
		memset((command + strlen(command)), 0, (COMMAND_MAX_LENGTH-strlen(command))*sizeof(char));



		if (illegalChars(command, "\"[]")==TRUE)
			{printf("ERROR: Please don't use \", [ or ]\n\n"); continue;}





		/* Semantic analysis of the entered command. */

		for (int i=0; i<strlen(command); i++)
		{
			switch (state)
			{
				case 0: changeState(command[i], " @oOsSmMdD", "0,1,3,3,16,16,47,47,73", &state, 2); break;
				case 1: changeState(command[i], "@", "0", &state, 1); break;
				case 2: brk = TRUE; break;
				case 3: changeState(command[i], "pP", "4,4", &state, 2); break;
				case 4: changeState(command[i], "eE", "5,5", &state, 11); breakValue(&state, 11, &brk); break;
				case 5: changeState(command[i], "nN", "6,6", &state, 11); breakValue(&state, 11, &brk); break;
				case 6: changeState(command[i], " ", "13", &state, 11); breakValue(&state, 11, &brk); break;
				case 7: changeState(command[i], "bB", "8,8", &state, 11); breakValue(&state, 11, &brk); break;
				case 8: changeState(command[i], " ", "14", &state, 11); breakValue(&state, 11, &brk); break;
				case 9: changeState(command[i], " ", "10", &state, 9); appendState(&state, 9, database, command[i]); limitChecker(database, 16, &state, 15, &brk); break;
				case 10: changeState(command[i], " ", "10", &state, 12); breakValue(&state, 12, &brk); break;
				case 13: changeState(command[i], " dD", "13,7,7", &state, 11); breakValue(&state, 11, &brk); break;
				case 14: clearEntity("database"); changeState(command[i], " ", "14", &state, 9); appendState(&state, 9, database, command[i]); break;
				case 16: changeState(command[i], "hH", "17,17", &state, 28); breakValue(&state, 28, &brk); break;
				case 17: changeState(command[i], "oO", "18,18", &state, 28); breakValue(&state, 28, &brk); break;
				case 18: changeState(command[i], "wW", "19,19", &state, 28); breakValue(&state, 28, &brk); break;
				case 19: changeState(command[i], " ", "20", &state, 28); breakValue(&state, 28, &brk); break;
				case 20: changeState(command[i], " sSaA", "20,22,22,31,31", &state, 28); break;
				case 21: changeState(command[i], " ", "29", &state, 21); appendState(&state, 21, table, command[i]); break;
				case 22: changeState(command[i], "tT", "23,23", &state, 28); breakValue(&state, 28, &brk); break;
				case 23: changeState(command[i], "rR", "24,24", &state, 28); breakValue(&state, 28, &brk); break;
				case 24: changeState(command[i], "uU", "25,25", &state, 28); breakValue(&state, 28, &brk); break;
				case 25: changeState(command[i], "cC", "26,26", &state, 28); breakValue(&state, 28, &brk); break;
				case 26: changeState(command[i], "tT", "27,27", &state, 28); breakValue(&state, 28, &brk); break;
				case 27: clearEntity("table"); changeState(command[i], " ", "30", &state, 28); breakValue(&state, 28, &brk); break;
				case 29: changeState(command[i], " ", "29", &state, 28); break;
				case 30: changeState(command[i], " ", "30", &state, 21); appendState(&state, 21, table, command[i]); break;
				case 31: changeState(command[i], "lL", "32,32", &state, 37); breakValue(&state, 37, &brk); break;
				case 32: changeState(command[i], "lL", "33,33", &state, 37); breakValue(&state, 37, &brk); break;
				case 33: changeState(command[i], " ", "34", &state, 37); breakValue(&state, 37, &brk); break;
				case 34: changeState(command[i], " dDtT", "34,35,35,39,39", &state, 37); breakValue(&state, 37, &brk); break;
				case 35: changeState(command[i], "bB", "36,36", &state, 37); breakValue(&state, 37, &brk); break;
				case 36: changeState(command[i], " ", "38", &state, 37); breakValue(&state, 37, &brk); break;
				case 38: changeState(command[i], " ", "38", &state, 37); breakValue(&state, 37, &brk); break;
				case 39: changeState(command[i], "aA", "40,40", &state, 46); breakValue(&state, 46, &brk); break;
				case 40: changeState(command[i], "bB", "41,41", &state, 46); breakValue(&state, 46, &brk); break;
				case 41: changeState(command[i], "lL", "42,42", &state, 46); breakValue(&state, 46, &brk); break;
				case 42: changeState(command[i], "eE", "43,43", &state, 46); breakValue(&state, 46, &brk); break;
				case 43: changeState(command[i], "sS", "44,44", &state, 46); breakValue(&state, 46, &brk); break;
				case 44: changeState(command[i], " ", "45", &state, 46); breakValue(&state, 46, &brk); break;
				case 45: changeState(command[i], " ", "45", &state, 46); breakValue(&state, 46, &brk); break;
				case 47: changeState(command[i], "aA", "48,48", &state, 63); breakValue(&state, 63, &brk); break;
				case 48: changeState(command[i], "kK", "49,49", &state, 63); breakValue(&state, 63, &brk); break;
				case 49: changeState(command[i], "eE", "50,50", &state, 63); breakValue(&state, 63, &brk); break;
				case 50: changeState(command[i], " ", "51", &state, 63); breakValue(&state, 63, &brk); break;
				case 51: changeState(command[i], " tTdD", "51,52,52,66,66", &state, 63); breakValue(&state, 63, &brk); break;
				case 52: changeState(command[i], "aA", "53,53", &state, 63); breakValue(&state, 63, &brk); break;
				case 53: changeState(command[i], "bB", "54,54", &state, 63); breakValue(&state, 63, &brk); break;
				case 54: changeState(command[i], "lL", "55,55", &state, 63); breakValue(&state, 63, &brk); break;
				case 55: changeState(command[i], "eE", "56,56", &state, 63); breakValue(&state, 63, &brk); break;
				case 56: changeState(command[i], " ", "57", &state, 63); breakValue(&state, 63, &brk); break;
				case 57: clearEntity("table"); changeState(command[i], " ", "57", &state, 58); appendState(&state, 58, table, command[i]); break;
				case 58: changeState(command[i], " (", "59,60", &state, 58); appendState(&state, 58, table, command[i]); limitChecker(table, 17, &state, 65, &brk); break;
				case 59: changeState(command[i], " (", "59,60", &state, 63); breakValue(&state, 63, &brk); break;
				case 60: clearEntity("buffer"); changeState(command[i], ")", "64", &state, 61); appendState(&state, 61, buffer, command[i]); break;
				case 61: changeState(command[i], ")", "62", &state, 61); appendState(&state, 61, buffer, command[i]); break;
				case 62: changeState(command[i], " ", "62", &state, 63); breakValue(&state, 63, &brk); break;
				case 66: changeState(command[i], "bB", "67,67", &state, 71); breakValue(&state, 71, &brk); break;
				case 67: changeState(command[i], " ", "68", &state, 71); breakValue(&state, 71, &brk); break;
				case 68: changeState(command[i], " ", "68", &state, 69); appendState(&state, 69, database, command[i]); break;
				case 69: changeState(command[i], " ", "70", &state, 69); appendState(&state, 69, database, command[i]); limitChecker(database, (DATABASE_MAX_LENGTH-1), &state, 72, &brk); break;
				case 70: changeState(command[i], " ", "70", &state, 71); breakValue(&state, 71, &brk); break;
				case 73: changeState(command[i], "eE", "74.74", &state, 88); breakValue(&state, 88, &brk); break;
				case 74: changeState(command[i], "lL", "75,75", &state, 88); breakValue(&state, 88, &brk); break;
				case 75: changeState(command[i], "eE", "76,76", &state, 88); breakValue(&state, 88, &brk); break;
				case 76: changeState(command[i], "tT", "77,77", &state, 88); breakValue(&state, 88, &brk); break;
				case 77: changeState(command[i], "eE", "78,78", &state, 88); breakValue(&state, 88, &brk); break;
				case 78: changeState(command[i], " ", "79", &state, 88); breakValue(&state, 88, &brk); break;
				case 79: changeState(command[i], " tT", "79,80,80", &state, 88); breakValue(&state, 88, &brk); break;
				case 80: changeState(command[i], "aA", "81,81", &state, 88); breakValue(&state, 88, &brk); break;
				case 81: changeState(command[i], "bB", "82,82", &state, 88); breakValue(&state, 88, &brk); break;
				case 82: changeState(command[i], "lL", "83,83", &state, 88); breakValue(&state, 88, &brk); break;
				case 83: changeState(command[i], "eE", "84,84", &state, 88); breakValue(&state, 88, &brk); break;
				case 84: changeState(command[i], " ", "85", &state, 88); breakValue(&state, 88, &brk); break;
				case 85: clearEntity("table"); changeState(command[i], " ", "85", &state, 86); appendState(&state, 86, table, command[i]); break;
				case 86: changeState(command[i], " ", "87,87", &state, 86); appendState(&state, 86, table, command[i]); limitChecker(table, (TABLE_MAX_LENGTH-1), &state, 72, &brk); break;
				case 87: changeState(command[i], " ", "87", &state, 88); breakValue(&state, 88, &brk); break;
			}


			if (brk==TRUE) {brk = FALSE; break;}
			if (i==strlen(command)-2) {break;}
		}










		/* Stage where the result is implemented as per final state. */

		switch (state)
		{
			case 0: printf("OK: No changes are made!\n\n"); break;
			case 1: printf("ERROR: Comment brackets opened, but not closed!\n\n"); break;
			case 2: printf("ERROR: Unknown command passed!\n\n"); break;
			case 3: printf("ERROR: Did you meant \"open db db_name\"?\n\n"); break;
			case 4: printf("ERROR: Did you meant \"open db db_name\"?\n\n"); break;
			case 5: printf("ERROR: Did you meant \"open db db_name\"?\n\n"); break;
			case 6: printf("ERROR: Did you meant \"open db db_name\"?\n\n"); break;
			case 7: printf("ERROR: Did you meant \"open db db_name\"?\n\n"); break;
			case 8: printf("ERROR: Did you meant \"open db db_name\"?\n\n"); break;
			case 9: checkDbExistence(TRUE); break;
			case 10: checkDbExistence(TRUE); break;
			case 11: printf("ERROR: Did you meant \"open db db_name\"?\n\n"); break;
			case 12: printf("ERROR: Did you meant open db db_name?\n\n"); break;
			case 13: printf("ERROR: Did you meant \"open db db_name\"?\n\n"); break;
			case 14: printf("ERROR: No database name entered!\n\n"); break;
			case 15: printf("ERROR: Name of database must be 32 characters long at max!\n\n"); break;
			case 16: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 17: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 18: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 19: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 20: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 21: checkTableExistence(TRUE); break;
			case 22: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 23: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 24: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 25: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 26: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 27: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 28: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 29: checkTableExistence(TRUE); break;
			case 30: printf("ERROR: Did you meant \"show struct table_name\"?\n\n"); break;
			case 31: printf("ERROR: Try \"show all db\".\n\n"); break;
			case 32: printf("ERROR: Try \"show all db\".\n\n"); break;
			case 33: printf("ERROR: Try \"show all db\".\n\n"); break;
			case 34: printf("ERROR: Try \"show all db\".\n\n"); break;
			case 35: printf("ERROR: Try \"show all db\".\n\n"); break;
			case 36: allDatabases(); break;
			case 37: printf("ERROR: Try \"show all db\".\n\n"); break;
			case 38: allDatabases(); break;
			case 39: printf("ERROR: Try \"show all tables\".\n\n"); break;
			case 40: printf("ERROR: Try \"show all tables\".\n\n"); break;
			case 41: printf("ERROR: Try \"show all tables\".\n\n"); break;
			case 42: printf("ERROR: Try \"show all tables\".\n\n"); break;
			case 43: printf("ERROR: Try \"show all tables\".\n\n"); break;
			case 44: allTables(); break;
			case 45: allTables(); break;
			case 46: printf("ERROR: Try \"show all tables\".\n\n"); break;
			case 47: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 48: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 49: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 50: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 51: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 52: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 53: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 54: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 55: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 56: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 57: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 58: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 59: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 60: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 61: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 62: attributeParser(); break;
			case 63: printf("ERROR: Did you meant \"make table tbl_name (...)\"?\n\n"); break;
			case 64: attributeParser(); break;
			case 65: printf("ERROR: Table name can be of 16 characters max!\n\n"); break;
			case 66: printf("ERROR: Did you meant \"make db db_name\"?\n\n"); break;
			case 67: printf("ERROR: Did you meant \"make db db_name\"?\n\n"); break;
			case 68: printf("ERROR: Did you meant \"make db db_name\"?\n\n"); break;
			case 69: makeDb(); clearEntity("database"); break;
			case 70: makeDb(); clearEntity("database"); break;
			case 71: printf("ERROR: Did you meant \"make db db_name\"?\n\n"); break;
			case 72: printf("ERROR: Database name length (%d) exceeded!\n\n", DATABASE_MAX_LENGTH); break;
			case 73: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 74: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 75: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 76: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 77: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 78: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 79: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 80: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 81: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 82: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 83: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 84: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 85: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
			case 86: printf("OK: Table cleared!\n\n"); break;
			case 87: printf("OK: Table cleared!\n\n"); break;
			case 88: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?\n\n"); break;
		}



		memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));

		state = 0;
	}
}




















/* Parses the attribute(s) passed for making a table. */

void attributeParser()
{
	for (int i=0; i<strlen(buffer); i++)
	{
		/* Semantic analysis with DFA & Turing machine. */

		switch (state2)
		{
			case 0: clearEntity("dataType"); clearEntity("attribute"); changeState(buffer[i], " ,", "2,6", &state2, 1); breakValue(&state2, 6, &brk2); appendState(&state2, 1, dataType, buffer[i]); break;
			case 1: changeState(buffer[i], " ,", "3,6", &state2, 1); breakValue(&state2, 6, &brk2); appendState(&state2, 1, dataType, buffer[i]); break;
			case 2: changeState(buffer[i], " ,", "2,6", &state2, 1); breakValue(&state2, 6, &brk2); appendState(&state2, 1, dataType, buffer[i]); break;
			case 3: changeState(buffer[i], " ,", "3,6", &state2, 4); breakValue(&state2, 6, &brk2); checkDataType(); appendState(&state2, 4, attribute, buffer[i]); break;
			case 4: changeState(buffer[i], " ,", "5,0", &state2, 4); appendState(&state2, 4, attribute, buffer[i]); break;
			case 5: changeState(buffer[i], " ,", "5,0", &state2, 7); breakValue(&state2, 7, &brk2); break;
		}


		if (brk2==TRUE) {brk2 = FALSE; break;}
		//if (i==strlen(buffer)-2) {break;}			// Will it work?
	}










	/* Final result, or action to be taken on last stage. */

	switch (state2)
	{
		case 0: printf("ERROR: Check if you passed any attributes & position of commas.\n\n"); break;
		case 1: printf("ERROR: Check if all attribute names are given for each data type.\n\n"); break;
		case 2: printf("ERROR: Check if you passed any attributes & position of commas.\n\n"); break;
		case 3: printf("ERROR: Check if all attribute names are given for each data type.\n\n"); break;
		case 4: clearEntity("dataType"); clearEntity("attribute"); makeTable(); break;
		case 5: clearEntity("dataType"); clearEntity("attribute"); makeTable(); break;
		case 6: printf("ERROR: Check if you passed any attributes & position of commas.\n\n"); break;
		case 7: printf("ERROR: Add commas after data type & attribute name!\n\n"); break;
		case 8: printf("ERROR: Invalid data type passed!\n\n"); break;
	}


	clearEntity("buffer"); clearEntity("dataType"); clearEntity("attribute");

	state2 = 0; valid = TRUE;
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */
