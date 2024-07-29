#ifndef ENCRYPTER_C
	#define ENCRYPTER_C

#define MAX_OUTPUT_SIZE 93


#include "encrypter.h"



/* 

The order: total 47

`~1!2@3#4$5%6^7&8*9(0)-_=+		Keyboard row: 1
qQwWeErRtTyYuUiIoOpP[{]}\|		Keyboard row: 2
aAsSdDfFgGhHjJkKlL;:'"			Keyboard row: 3
zZxXcCvVbBnNmM,<.>/?			Keyboard row: 4

'0' means letter separation,
'00' means term/word separation.

 */



const char keyboard_chars[TOTAL_CHARS] = {' ','`','~','1','!','2','@','3','#','4',		//10
	'$','5','%','6','^','7','&','8','*','9','(','0',')','-','_','=','+','q','Q','w',	//30
	'W','e','E','r','R','t','T','y','Y','u','U','i','I','o','O','p','P','[','{',']',	//50
	'}','a','A','s','S','d','D','f','F','g','G','h','H','j','J','k','K','l','L',';',	//70
	':','\'','\"','z','Z','x','X','c','C','v','V','b','B','n','N','m','M',',','<',		//89
	'.','>','/','?'																		//93
};

const char *prime_codes[TOTAL_CHARS] = {
    "11", "13", "17", "19", "23", "29", "31", "37", "41", "43", "47", "53", "59",		//13
    "61", "67", "71", "73", "79", "83", "89", "97", "113", "127", "131", "137", 		//25
    "139", "149", "151", "157", "163", "167", "173", "179", "181", "191", "193", 		//36
    "197", "199", "211", "223", "227", "229", "233", "239", "241", "251", "257", 		//47
    "263", "269", "271", "277", "281", "283", "293", "311", "313", "317", "331", 		//58
    "337", "347", "349", "353", "359", "367", "373", "379", "383", "389", "397", 		//69
    "419", "421", "431", "433", "439", "443", "449", "457", "461", "463", "467", 		//80
    "479", "487", "491", "499", "521", "523", "541", "547", "557", "563", "569",		//91
    "571", "577"																		//93
};



char *encrypt(char *input)
{
	static char output[MAX_OUTPUT_SIZE]; int cursor_pos = 0;
	memset(output, 0, MAX_OUTPUT_SIZE*sizeof(char));
	
	for (int i=0; i<strlen(input); i++)
	{
		for (int j=0; j<TOTAL_CHARS; j++)
		{
			if (keyboard_chars[j]==input[i])
			{
				constrappend(output, &cursor_pos, prime_codes[j]);
				charappend(output, &cursor_pos, '0');

				break;
			}
		}
	}

	charappend(output, &cursor_pos, '0');
	memset((output + cursor_pos), 0, (strlen(output)-cursor_pos)*sizeof(char));

	return output;
}


char *decrypt(char *input)
{
	static char output[MAX_OUTPUT_SIZE]; int str_cursor_pos = 0;
	memset(output, 0, MAX_OUTPUT_SIZE*sizeof(char));

	char character[4]; int char_cursor_pos = 0;
	memset(character, 0, strlen(character)*sizeof(char));

	int zero_count = 0;
	
	for (int i=0; i<strlen(input); i++)
	{
		if (input[i]!='0')
		{
			if (zero_count==1) {zero_count = 0;}

			charappend(character, &char_cursor_pos, input[i]);
		}

		else if ((input[i]=='0')&&(zero_count==0))
		{
			zero_count++;

			for (int j=0; j<TOTAL_CHARS; j++)
			{
				if (!strcmp(character, prime_codes[j]))
				{
					charappend(output, &str_cursor_pos, keyboard_chars[j]);
					memset(character, 0, strlen(character)*sizeof(char));
					char_cursor_pos = 0;

					break;
				}
			}
		}

		else if ((input[i]=='0')&&(zero_count==1))
		{
			zero_count = 0;
			
			break;
		}
	}

	return output;
}



#endif