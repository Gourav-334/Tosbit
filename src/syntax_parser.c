/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/syntax_parser.h"




















/* The automaton, each state has to be defined for all situations. */

void syntaxParser(char username[], char *user_cmd)
{
	/* Calculating performance. */

	struct timespec start, end;



	/* Syntax parsing & feedback loop. */

	while (TRUE)
	{
		/* Resetting command buffer. */

		memset(command, 0, sizeof(command));
		printf("TOS> ");


		/* For driver manager piping. */

		if (user_cmd==NULL) {fgets(command, COMMAND_MAX_LENGTH, stdin);}
		else {strcpy(command, user_cmd); printf("%s\n", command);}


		/* Measuring START time. */

		clock_gettime(CLOCK_MONOTONIC, &start);


		/* Filtering illegal characters. */

		if (illegalChars(command, "\"[]")==TRUE)
			{printf("ERROR: Please don't use \", [ or ]\n\n"); continue;}





		/* Parsing of the entered command. */

		for (int i=0; i<strlen(command); i++)
		{
			switch (state)
			{
				case 0: changeState(command[i], " @oOsSmMdDcCpPuU", "0,1,3,3,16,16,47,47,73,73,95,95,116,116,152,152", &state, 2); break;
				case 1: changeState(command[i], "@", "0", &state, 1); break;
				case 2: breaker = TRUE; break;
				case 3: changeState(command[i], "pP", "4,4", &state, 2); break;
				case 4: changeState(command[i], "eE", "5,5", &state, 11); breakValue(&state, 11, &breaker); break;
				case 5: changeState(command[i], "nN", "6,6", &state, 11); breakValue(&state, 11, &breaker); break;
				case 6: changeState(command[i], " ", "13", &state, 11); breakValue(&state, 11, &breaker); break;
				case 7: changeState(command[i], "bB", "8,8", &state, 11); breakValue(&state, 11, &breaker); break;
				case 8: changeState(command[i], " ", "14", &state, 11); breakValue(&state, 11, &breaker); break;
				case 9: changeState(command[i], " ", "10", &state, 9); appendState(&state, 9, database, command[i]); limitChecker(database, 16, &state, 15, &breaker); break;
				case 10: changeState(command[i], " ", "10", &state, 12); breakValue(&state, 12, &breaker); break;
				case 13: changeState(command[i], " dD", "13,7,7", &state, 11); breakValue(&state, 11, &breaker); break;
				case 14: clearEntity("database"); changeState(command[i], " ", "14", &state, 9); appendState(&state, 9, database, command[i]); break;
				case 16: changeState(command[i], "hH", "17,17", &state, 28); breakValue(&state, 28, &breaker); break;
				case 17: changeState(command[i], "oO", "18,18", &state, 28); breakValue(&state, 28, &breaker); break;
				case 18: changeState(command[i], "wW", "19,19", &state, 28); breakValue(&state, 28, &breaker); break;
				case 19: changeState(command[i], " ", "20", &state, 28); breakValue(&state, 28, &breaker); break;
				case 20: clearEntity("table"); changeState(command[i], " sSaA", "20,22,22,31,31", &state, 132); appendState(&state, 132, table, command[i]); break;
				case 21: changeState(command[i], " ", "29", &state, 21); appendState(&state, 21, table, command[i]); break;
				case 22: changeState(command[i], "tT", "23,23", &state, 28); breakValue(&state, 28, &breaker); break;
				case 23: changeState(command[i], "rR", "24,24", &state, 28); breakValue(&state, 28, &breaker); break;
				case 24: changeState(command[i], "uU", "25,25", &state, 28); breakValue(&state, 28, &breaker); break;
				case 25: changeState(command[i], "cC", "26,26", &state, 28); breakValue(&state, 28, &breaker); break;
				case 26: changeState(command[i], "tT", "27,27", &state, 28); breakValue(&state, 28, &breaker); break;
				case 27: clearEntity("table"); changeState(command[i], " ", "30", &state, 28); breakValue(&state, 28, &breaker); break;
				case 29: changeState(command[i], " ", "29", &state, 28); break;
				case 30: changeState(command[i], " ", "30", &state, 21); appendState(&state, 21, table, command[i]); break;
				case 31: changeState(command[i], "lL", "32,32", &state, 37); breakValue(&state, 37, &breaker); break;
				case 32: changeState(command[i], "lL", "33,33", &state, 37); breakValue(&state, 37, &breaker); break;
				case 33: changeState(command[i], " ", "34", &state, 37); breakValue(&state, 37, &breaker); break;
				case 34: changeState(command[i], " dDtT", "34,35,35,39,39", &state, 37); breakValue(&state, 37, &breaker); break;
				case 35: changeState(command[i], "bB", "36,36", &state, 37); breakValue(&state, 37, &breaker); break;
				case 36: changeState(command[i], " ", "38", &state, 37); breakValue(&state, 37, &breaker); break;
				case 38: changeState(command[i], " ", "38", &state, 37); breakValue(&state, 37, &breaker); break;
				case 39: changeState(command[i], "aA", "40,40", &state, 46); breakValue(&state, 46, &breaker); break;
				case 40: changeState(command[i], "bB", "41,41", &state, 46); breakValue(&state, 46, &breaker); break;
				case 41: changeState(command[i], "lL", "42,42", &state, 46); breakValue(&state, 46, &breaker); break;
				case 42: changeState(command[i], "eE", "43,43", &state, 46); breakValue(&state, 46, &breaker); break;
				case 43: changeState(command[i], "sS", "44,44", &state, 46); breakValue(&state, 46, &breaker); break;
				case 44: changeState(command[i], " ", "45", &state, 46); breakValue(&state, 46, &breaker); break;
				case 45: changeState(command[i], " ", "45", &state, 46); breakValue(&state, 46, &breaker); break;
				case 47: changeState(command[i], "aA", "48,48", &state, 63); breakValue(&state, 63, &breaker); break;
				case 48: changeState(command[i], "kK", "49,49", &state, 63); breakValue(&state, 63, &breaker); break;
				case 49: changeState(command[i], "eE", "50,50", &state, 63); breakValue(&state, 63, &breaker); break;
				case 50: changeState(command[i], " ", "51", &state, 63); breakValue(&state, 63, &breaker); break;
				case 51: changeState(command[i], " tTdD", "51,52,52,66,66", &state, 63); breakValue(&state, 63, &breaker); break;
				case 52: changeState(command[i], "aA", "53,53", &state, 63); breakValue(&state, 63, &breaker); break;
				case 53: changeState(command[i], "bB", "54,54", &state, 63); breakValue(&state, 63, &breaker); break;
				case 54: changeState(command[i], "lL", "55,55", &state, 63); breakValue(&state, 63, &breaker); break;
				case 55: changeState(command[i], "eE", "56,56", &state, 63); breakValue(&state, 63, &breaker); break;
				case 56: changeState(command[i], " ", "57", &state, 63); breakValue(&state, 63, &breaker); break;
				case 57: clearEntity("table"); changeState(command[i], " ", "57", &state, 58); appendState(&state, 58, table, command[i]); break;
				case 58: changeState(command[i], " (", "59,60", &state, 58); appendState(&state, 58, table, command[i]); limitChecker(table, 17, &state, 65, &breaker); break;
				case 59: changeState(command[i], " (", "59,60", &state, 63); breakValue(&state, 63, &breaker); break;
				case 60: clearEntity("buffer"); changeState(command[i], ")", "64", &state, 61); appendState(&state, 61, buffer, command[i]); limitChecker(buffer, (BUFFER_MAX_LENGTH-1), &state, 130, &breaker); break;
				case 61: changeState(command[i], ")", "62", &state, 61); appendState(&state, 61, buffer, command[i]); break;
				case 62: changeState(command[i], " ", "62", &state, 63); breakValue(&state, 63, &breaker); break;
				case 66: changeState(command[i], "bB", "67,67", &state, 71); breakValue(&state, 71, &breaker); break;
				case 67: changeState(command[i], " ", "68", &state, 71); breakValue(&state, 71, &breaker); break;
				case 68: clearEntity("database"); changeState(command[i], " ", "68", &state, 69); appendState(&state, 69, database, command[i]); break;
				case 69: changeState(command[i], " ", "70", &state, 69); appendState(&state, 69, database, command[i]); limitChecker(database, (DATABASE_MAX_LENGTH-1), &state, 72, &breaker); break;
				case 70: changeState(command[i], " ", "70", &state, 71); breakValue(&state, 71, &breaker); break;
				case 73: changeState(command[i], "eE", "74,74", &state, 88); breakValue(&state, 88, &breaker); break;
				case 74: changeState(command[i], "lL", "75,75", &state, 88); breakValue(&state, 88, &breaker); break;
				case 75: changeState(command[i], "eE", "76,76", &state, 88); breakValue(&state, 88, &breaker); break;
				case 76: changeState(command[i], "tT", "77,77", &state, 88); breakValue(&state, 88, &breaker); break;
				case 77: changeState(command[i], "eE", "78,78", &state, 88); breakValue(&state, 88, &breaker); break;
				case 78: changeState(command[i], " ", "79", &state, 88); breakValue(&state, 88, &breaker); break;
				case 79: changeState(command[i], " tTdD", "79,80,80,89,89", &state, 88); breakValue(&state, 88, &breaker); break;
				case 80: changeState(command[i], "aA", "81,81", &state, 88); breakValue(&state, 88, &breaker); break;
				case 81: changeState(command[i], "bB", "82,82", &state, 88); breakValue(&state, 88, &breaker); break;
				case 82: changeState(command[i], "lL", "83,83", &state, 88); breakValue(&state, 88, &breaker); break;
				case 83: changeState(command[i], "eE", "84,84", &state, 88); breakValue(&state, 88, &breaker); break;
				case 84: changeState(command[i], " ", "85", &state, 88); breakValue(&state, 88, &breaker); break;
				case 85: clearEntity("table"); changeState(command[i], " ", "85", &state, 86); appendState(&state, 86, table, command[i]); break;
				case 86: changeState(command[i], " ", "87", &state, 86); appendState(&state, 86, table, command[i]); limitChecker(table, (TABLE_MAX_LENGTH-1), &state, 65, &breaker); break;
				case 87: changeState(command[i], " ", "87", &state, 88); breakValue(&state, 88, &breaker); break;
				case 89: changeState(command[i], "bB", "90,90", &state, 94); breakValue(&state, 94, &breaker); break;
				case 90: changeState(command[i], " ", "91", &state, 94); breakValue(&state, 94, &breaker); break;
				case 91: clearEntity("database"); changeState(command[i], " ", "91", &state, 92); appendState(&state, 92, database, command[i]); break;
				case 92: changeState(command[i], " ", "93", &state, 92); appendState(&state, 92, database, command[i]); limitChecker(database, (DATABASE_MAX_LENGTH-1), &state, 72, &breaker); break;
				case 93: changeState(command[i], " ", "93", &state, 94); breakValue(&state, 94, &breaker); break;
				case 95: changeState(command[i], "lL", "96,96", &state, 109); breakValue(&state, 109, &breaker); break;
				case 96: changeState(command[i], "eE", "97,97", &state, 109); breakValue(&state, 109, &breaker); break;
				case 97: changeState(command[i], "aA", "98,98", &state, 109); breakValue(&state, 109, &breaker); break;
				case 98: changeState(command[i], "rR", "99,99", &state, 109); breakValue(&state, 109, &breaker); break;
				case 99: changeState(command[i], " ", "100", &state, 109); breakValue(&state, 109, &breaker); break;
				case 100: changeState(command[i], "tTdD", "101,101,110,100", &state, 109); breakValue(&state, 109, &breaker); break;
				case 101: changeState(command[i], "aA", "102,102", &state, 109); breakValue(&state, 109, &breaker); break;
				case 102: changeState(command[i], "bB", "103,103", &state, 109); breakValue(&state, 109, &breaker); break;
				case 103: changeState(command[i], "lL", "104,104", &state, 109); breakValue(&state, 109, &breaker); break;
				case 104: changeState(command[i], "eE", "105,105", &state, 109); breakValue(&state, 109, &breaker); break;
				case 105: changeState(command[i], " ", "106", &state, 109); breakValue(&state, 109, &breaker); break;
				case 106: clearEntity("table"); changeState(command[i], " ", "106", &state, 107); appendState(&state, 107, table, command[i]); break;
				case 107: changeState(command[i], " ", "108", &state, 107); appendState(&state, 107, table, command[i]); limitChecker(table, (TABLE_MAX_LENGTH-1), &state, 65, &breaker); break;
				case 108: changeState(command[i], " ", "108", &state, 109); breakValue(&state, 109, &breaker); break;
				case 110: changeState(command[i], "bB", "111,111", &state, 115); breakValue(&state, 115, &breaker); break;
				case 111: changeState(command[i], " ", "112", &state, 115); breakValue(&state, 115, &breaker); break;
				case 112: clearEntity("database"); changeState(command[i], " ", "112", &state, 113); appendState(&state, 113, database, command[i]); break;
				case 113: changeState(command[i], " ", "114", &state, 113); appendState(&state, 113, database, command[i]); limitChecker(database, (DATABASE_MAX_LENGTH-1), &state, 72, &breaker); break;
				case 116: changeState(command[i], "uU", "117,117", &state, 129); breakValue(&state, 129, &breaker); break;
				case 117: changeState(command[i], "sS", "118,118", &state, 129); breakValue(&state, 129, &breaker); break;
				case 118: changeState(command[i], "hH", "119,119", &state, 129); breakValue(&state, 129, &breaker); break;
				case 119: changeState(command[i], " ", "120", &state, 129); breakValue(&state, 129, &breaker); break;
				case 120: changeState(command[i], " tT", "120,121,121", &state, 129); breakValue(&state, 129, &breaker); break;
				case 121: changeState(command[i], "oO", "122,122", &state, 129); breakValue(&state, 129, &breaker); break;
				case 122: changeState(command[i], " ", "123", &state, 129); breakValue(&state, 129, &breaker); break;
				case 123: clearEntity("table"); changeState(command[i], " ", "123", &state, 124); appendState(&state, 124, table, command[i]); break;
				case 124: changeState(command[i], " (", "125,126", &state, 124); appendState(&state, 124, table, command[i]); limitChecker(table, (TABLE_MAX_LENGTH-1), &state, 65, &breaker); break;
				case 125: changeState(command[i], " (", "125,126", &state, 129); breakValue(&state, 129, &breaker); break;
				case 126: clearEntity("buffer"); changeState(command[i], ")", "128", &state, 127); appendState(&state, 127, buffer, command[i]); break;
				case 127: changeState(command[i], ")", "128", &state, 127); appendState(&state, 127, buffer, command[i]); limitChecker(buffer, (BUFFER_MAX_LENGTH-1), &state, 130, &breaker); break;
				case 128: changeState(command[i], " ", "128", &state, 131); breakValue(&state, 131, &breaker); break;
				case 132: changeState(command[i], " .", "133,134", &state, 132); appendState(&state, 132, table, command[i]); limitChecker(table, (TABLE_MAX_LENGTH-1), &state, 65, &breaker); break;
				case 133: changeState(command[i], " .", "133,134", &state, 150); breakValue(&state, 150, &breaker); break;
				case 134: changeState(command[i], " (", "135,136", &state, 150); breakValue(&state, 150, &breaker); break;
				case 135: changeState(command[i], " (", "135,136", &state, 150); breakValue(&state, 150, &breaker); break;
				case 136: clearEntity("buffer"); changeState(command[i], ")", "138", &state, 137); appendState(&state, 137, buffer, command[i]); break;
				case 137: changeState(command[i], ")", "139", &state, 137); appendState(&state, 137, buffer, command[i]); limitChecker(buffer, (BUFFER_MAX_LENGTH-1), &state, 130, &breaker); break;
				case 139: changeState(command[i], " wW", "139,140,140", &state, 150); breakValue(&state, 150, &breaker); break;
				case 140: changeState(command[i], "hH", "141,141", &state, 151); breakValue(&state, 151, &breaker); break;
				case 141: changeState(command[i], "eE", "142,142", &state, 151); breakValue(&state, 151, &breaker); break;
				case 142: changeState(command[i], "rR", "143,143", &state, 151); breakValue(&state, 151, &breaker); break;
				case 143: changeState(command[i], "eE", "145,145", &state, 151); breakValue(&state, 151, &breaker); break;
				case 145: changeState(command[i], " (", "145,146", &state, 151); breakValue(&state, 151, &breaker); break;
				case 146: clearEntity("buffer2"); changeState(command[i], ")", "148", &state, 147); appendState(&state, 147, buffer2, command[i]); break;
				case 147: changeState(command[i], ")", "148", &state, 147); appendState(&state, 147, buffer2, command[i]); limitChecker(buffer2, (BUFFER_MAX_LENGTH-1), &state, 130, &breaker); break;
				case 148: changeState(command[i], " ", "149", &state, 151); breakValue(&state, 151, &breaker); break;
				case 149: changeState(command[i], " ", "149", &state, 151); breakValue(&state, 151, &breaker); break;
				case 152: changeState(command[i], "pP", "153,153", &state, 173); breakValue(&state, 173, &breaker); break;
				case 153: changeState(command[i], "dD", "154,154", &state, 173); breakValue(&state, 173, &breaker); break;
				case 154: changeState(command[i], "aA", "155,155", &state, 173); breakValue(&state, 173, &breaker); break;
				case 155: changeState(command[i], "tT", "156,156", &state, 173); breakValue(&state, 173, &breaker); break;
				case 156: changeState(command[i], "eE", "157,157", &state, 173); breakValue(&state, 173, &breaker); break;
				case 157: changeState(command[i], " ", "158", &state, 173); breakValue(&state, 173, &breaker); break;
				case 158: clearEntity("table"); changeState(command[i], " ", "158", &state, 159); appendState(&state, 159, table, command[i]); break;
				case 159: changeState(command[i], " .", "160,161", &state, 159); appendState(&state, 159, table, command[i]); limitChecker(table, (TABLE_MAX_LENGTH-1), &state, 65, &breaker); break;
				case 160: changeState(command[i], " .", "160,161", &state, 173); breakValue(&state, 173, &breaker); break;
				case 161: changeState(command[i], " (", "161,162", &state, 173); breakValue(&state, 173, &breaker); break;
				case 162: clearEntity("buffer"); changeState(command[i], ")", "164", &state, 163); appendState(&state, 163, buffer, command[i]); break;
				case 163: changeState(command[i], ")", "164", &state, 163); appendState(&state, 163, buffer, command[i]); limitChecker(buffer, (BUFFER_MAX_LENGTH-1), &state, 130, &breaker); break;
				case 164: changeState(command[i], " wW", "164,165,165", &state, 174); breakValue(&state, 174, &breaker); break;
				case 165: changeState(command[i], "hH", "166,166", &state, 174); breakValue(&state, 174, &breaker); break;
				case 166: changeState(command[i], "eE", "167,167", &state, 174); breakValue(&state, 174, &breaker); break;
				case 167: changeState(command[i], "rR", "168,168", &state, 174); breakValue(&state, 174, &breaker); break;
				case 168: changeState(command[i], "eE", "169,169", &state, 174); breakValue(&state, 174, &breaker); break;
				case 169: changeState(command[i], " (", "169,170", &state, 174); breakValue(&state, 174, &breaker); break;
				case 170: clearEntity("buffer2"); changeState(command[i], ")", "172", &state, 171); appendState(&state, 171, buffer2, command[i]); break;
				case 171: changeState(command[i], ")", "172", &state, 171); appendState(&state, 171, buffer2, command[i]); limitChecker(buffer2, (BUFFER_MAX_LENGTH-1), &state, 130, &breaker); break;
			}



			if (breaker==TRUE) {breaker = FALSE; break;}
			
			newline_remover(command);
		}










		/* Stage where the result is implemented as per final state. */

		switch (state)
		{
			case 0: printf("OK: No changes are made!"); break;
			case 1: printf("ERROR: Comment brackets opened, but not closed!"); break;
			case 2: printf("ERROR: Unknown command passed!"); break;
			case 3: printf("ERROR: Did you meant \"open db db_name\"?"); break;
			case 4: printf("ERROR: Did you meant \"open db db_name\"?"); break;
			case 5: printf("ERROR: Did you meant \"open db db_name\"?"); break;
			case 6: printf("ERROR: Did you meant \"open db db_name\"?"); break;
			case 7: printf("ERROR: Did you meant \"open db db_name\"?"); break;
			case 8: printf("ERROR: Did you meant \"open db db_name\"?"); break;
			case 9: checkDbExistence(TRUE); break;
			case 10: checkDbExistence(TRUE); break;
			case 11: printf("ERROR: Did you meant \"open db db_name\"?"); break;
			case 12: printf("ERROR: Did you meant open db db_name?"); break;
			case 13: printf("ERROR: Did you meant \"open db db_name\"?"); break;
			case 14: printf("ERROR: No database name entered!"); break;
			case 15: printf("ERROR: Name of database must be 32 characters long at max!"); break;
			case 16: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 17: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 18: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 19: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 20: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 21: checkTableExistence(TRUE); break;
			case 22: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 23: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 24: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 25: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 26: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 27: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 28: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 29: checkTableExistence(TRUE); break;
			case 30: printf("ERROR: Did you meant \"show struct table_name\"?"); break;
			case 31: printf("ERROR: Try \"show all db\"."); break;
			case 32: printf("ERROR: Try \"show all db\"."); break;
			case 33: printf("ERROR: Try \"show all db\"."); break;
			case 34: printf("ERROR: Try \"show all db\"."); break;
			case 35: printf("ERROR: Try \"show all db\"."); break;
			case 36: allDatabases(); break;
			case 37: printf("ERROR: Try \"show all db\"."); break;
			case 38: allDatabases(); break;
			case 39: printf("ERROR: Try \"show all tables\"."); break;
			case 40: printf("ERROR: Try \"show all tables\"."); break;
			case 41: printf("ERROR: Try \"show all tables\"."); break;
			case 42: printf("ERROR: Try \"show all tables\"."); break;
			case 43: printf("ERROR: Try \"show all tables\"."); break;
			case 44: allTables(); break;
			case 45: allTables(); break;
			case 46: printf("ERROR: Try \"show all tables\"."); break;
			case 47: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 48: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 49: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 50: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 51: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 52: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 53: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 54: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 55: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 56: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 57: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 58: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 59: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 60: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 61: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 62: attributeParser(); break;
			case 63: printf("ERROR: Did you meant \"make table tbl_name (...)\"?"); break;
			case 64: attributeParser(); break;
			case 65: printf("ERROR: Table name can be of 16 characters max!"); break;
			case 66: printf("ERROR: Did you meant \"make db db_name\"?"); break;
			case 67: printf("ERROR: Did you meant \"make db db_name\"?"); break;
			case 68: printf("ERROR: Did you meant \"make db db_name\"?"); break;
			case 69: makeDb(); clearEntity("database"); break;
			case 70: makeDb(); clearEntity("database"); break;
			case 71: printf("ERROR: Did you meant \"make db db_name\"?"); break;
			case 72: printf("ERROR: Database name length (%d) exceeded!", DATABASE_MAX_LENGTH); break;
			case 73: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 74: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 75: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 76: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 77: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 78: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 79: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 80: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 81: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 82: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 83: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 84: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 85: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 86: deleteTable(TRUE); break;
			case 87: deleteTable(TRUE); break;
			case 88: printf("ERROR: Attempting deletion with \"delete table tbl_name\"?"); break;
			case 89: printf("ERROR: Attempting deletion with \"delete db db_name\"?"); break;
			case 90: printf("ERROR: Attempting deletion with \"delete db db_name\"?"); break;
			case 91: printf("ERROR: Attempting deletion with \"delete db db_name\"?"); break;
			case 92: deleteDb(TRUE); break;
			case 93: deleteDb(TRUE); break;
			case 94: printf("ERROR: Attempting deletion with \"delete db db_name\"?"); break;
			case 95: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 96: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 97: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 98: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 99: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 100: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 101: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 102: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 103: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 104: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 105: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 106: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 107: clearTable(); break;
			case 108: clearTable(); break;
			case 109: printf("ERROR: Try \"clear table tbl_name\"."); break;
			case 110: printf("ERROR: Try \"clear db db_name."); break;
			case 111: printf("ERROR: Try \"clear db db_name."); break;
			case 112: printf("ERROR: Try \"clear db db_name."); break;
			case 113: clearDb(); break;
			case 114: clearDb(); break;
			case 115: printf("ERROR: Try \"clear db db_name."); break;
			case 116: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 117: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 118: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 119: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 120: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 121: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 122: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 123: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 124: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 125: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 126: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 127: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 128: pushRow(); break;
			case 129: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 130: printf("ERROR: Buffer limit exceeded (command too long)!"); break;
			case 131: printf("ERROR: Did you meant \"push to tbl_name (...)\"?"); break;
			case 132: printf("ERROR: Did you meant \"show tbl_name.(...)\"?"); break;
			case 133: printf("ERROR: Did you meant \"show tbl_name.(...)\"?"); break;
			case 134: printf("ERROR: Did you meant \"show tbl_name.(...)\"?"); break;
			case 135: printf("ERROR: Did you meant \"show tbl_name.(...)\"?"); break;
			case 136: printf("ERROR: Did you meant \"show tbl_name.(...)\"?"); break;
			case 137: printf("ERROR: Did you meant \"show tbl_name.(...)\"?"); break;
			case 139: selectionParser(); break;
			case 140: printf("ERROR: Did you meant \"show tbl_name.(...) where (...)\"?"); break;
			case 141: printf("ERROR: Did you meant \"show tbl_name.(...) where (...)\"?"); break;
			case 142: printf("ERROR: Did you meant \"show tbl_name.(...) where (...)\"?"); break;
			case 143: printf("ERROR: Did you meant \"show tbl_name.(...) where (...)\"?"); break;
			case 145: printf("ERROR: Did you meant \"show tbl_name.(...) where (...)\"?"); break;
			case 146: printf("ERROR: Did you meant \"show tbl_name.(...) where (...)\"?"); break;
			case 147: printf("ERROR: Did you meant \"show tbl_name.(...) where (...)\"?"); break;
			case 148: printf("STAT: \'y\' rows found."); break;
			case 149: printf("STAT: \'y\' rows found."); break;
			case 150: printf("ERROR: Did you meant \"show tbl_name.(...)\"?"); break;
			case 151: printf("ERROR: Did you meant \"show tbl_name.(...) where (...)\"?"); break;
			case 152: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 153: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 154: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 155: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 156: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 157: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 158: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 159: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 160: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 161: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 162: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 163: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 164: updateParser(); break;
			case 165: printf("ERROR: Did you meant \"update tbl_name.(...) where (...)\"?"); break;
			case 166: printf("ERROR: Did you meant \"update tbl_name.(...) where (...)\"?"); break;
			case 167: printf("ERROR: Did you meant \"update tbl_name.(...) where (...)\"?"); break;
			case 168: printf("ERROR: Did you meant \"update tbl_name.(...) where (...)\"?"); break;
			case 169: printf("ERROR: Did you meant \"update tbl_name.(...) where (...)\"?"); break;
			case 170: printf("ERROR: Did you meant \"update tbl_name.(...) where (...)\"?"); break;
			case 171: printf("ERROR: Did you meant \"update tbl_name.(...) where (...)\"?"); break;
			case 172: printf("OK: Rows updated complexly."); break;
			case 173: printf("ERROR: Did you meant \"update tbl_name.(...)\"?"); break;
			case 174: printf("ERROR: Did you meant \"update tbl_name.(...) where (...)\"?"); break;
		}



		recordLog(username, command);
		memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));

		state = 0;



		/* Completing performance calculation. */

		clock_gettime(CLOCK_MONOTONIC, &end);
	    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    	
    	printf(" (%f sec)\n\n", time_taken);



		/* To break if only a single command was requested. */

		if (user_cmd==NULL) {continue;}
		else {break;}
	}
}




















/* Parses the attribute(s) passed for making a table. */

void attributeParser()
{
	for (int i=0; i<strlen(buffer); i++)
	{
		/* Parsing with DFA & Turing machine. */

		switch (state2)
		{
			case 0: clearEntity("dataType"); clearEntity("attribute"); changeState(buffer[i], " ,", "2,6", &state2, 1); breakValue(&state2, 6, &breaker2); appendState(&state2, 1, dataType, buffer[i]); break;
			case 1: changeState(buffer[i], " ,", "3,6", &state2, 1); breakValue(&state2, 6, &breaker2); appendState(&state2, 1, dataType, buffer[i]); break;
			case 2: changeState(buffer[i], " ,", "2,6", &state2, 1); breakValue(&state2, 6, &breaker2); appendState(&state2, 1, dataType, buffer[i]); break;
			case 3: changeState(buffer[i], " ,", "3,6", &state2, 4); breakValue(&state2, 6, &breaker2); checkDataType(); appendState(&state2, 4, attribute, buffer[i]);
				if (illegalChar(buffer[i], "+-*/%!=&|")==TRUE) {state2 = 9; breaker2 = TRUE;} break;	// I DISCOURAGE WRITING DFA STATES LIKE THIS & THUS KEEP IT MINIMUM.
			case 4: changeState(buffer[i], " ,", "5,0", &state2, 4); appendState(&state2, 4, attribute, buffer[i]);
				if (illegalChar(buffer[i], "+-*/%!=&|")==TRUE) {state2 = 9; breaker2 = TRUE;} break;	// I DISCOURAGE WRITING DFA STATES LIKE THIS & THUS KEEP IT MINIMUM.
			case 5: changeState(buffer[i], " ,", "5,0", &state2, 7); breakValue(&state2, 7, &breaker2); break;
		}


		/* Prematurely breaking from loop if DFA reaches dump state. */

		if (breaker2==TRUE) {breaker2 = FALSE; break;}
	}










	/* Final result, or action to be taken on last stage. */

	switch (state2)
	{
		case 0: printf("ERROR: Check if you passed any attributes & position of commas."); break;
		case 1: printf("ERROR: Check if all attribute names are given for each data type."); break;
		case 2: printf("ERROR: Check if you passed any attributes & position of commas."); break;
		case 3: printf("ERROR: Check if all attribute names are given for each data type."); break;
		case 4: clearEntity("attribute"); makeTable(); break;
		case 5: clearEntity("attribute"); makeTable(); break;
		case 6: printf("ERROR: Check if you passed any attributes & position of commas."); break;
		case 7: printf("ERROR: Add commas after data type & attribute name!"); break;
		case 8: printf("ERROR: (%s) Invalid data type passed!", dataType); break;
		case 9: printf("ERROR: Please don't use operators (+, -, *, /, %%, !, =, &, |) in name of attribute."); break;
	}


	clearEntity("buffer"); clearEntity("dataType"); clearEntity("attribute");

	state2 = 0; valid = TRUE;
}










/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */