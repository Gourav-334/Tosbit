/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#ifndef ENCRYPTER_C
	#define ENCRYPTER_C



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










/* All possible inputs coming from STDOUT (keyboard) */

const char keyboard_chars[TOTAL_CHARS] = {' ','`','~','1','!','2','@','3','#','4',		//10
	'$','5','%','6','^','7','&','8','*','9','(','0',')','-','_','=','+','q','Q','w',	//30
	'W','e','E','r','R','t','T','y','Y','u','U','i','I','o','O','p','P','[','{',']',	//50
	'}','a','A','s','S','d','D','f','F','g','G','h','H','j','J','k','K','l','L',';',	//70
	':','\'','\"','z','Z','x','X','c','C','v','V','b','B','n','N','m','M',',','<',		//89
	'.','>','/','?'																		//93
};





/* Equivalent encrypted prime codes for STDOUT symbols */

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










/* Encrypts the passed argument string */

char *encrypt(char *input)
{
	static char output[MAX_ENCRYPTED_SIZE] = {0};
	

	/* This loop ensures each character is encrypted */

	for (int i=0; i<strlen(input); i++)
	{
		/* This loop searches for the encrypted code for a particular character */

		for (int j=0; j<TOTAL_CHARS; j++)
		{
			if (keyboard_chars[j]==input[i])
			{
				constrappend(output, prime_codes[j]);
				charappend(output, '0');

				break;
			}
		}
	}

	charappend(output, '0');


	return output;
}










/* Decrypts the passed argument string */

char *decrypt(char *input)
{
	static char output[MAX_ENCRYPTED_SIZE] = {0};
	char buffer[MAX_DECRYPTED_SIZE] = {0};

	int zero_count = 0;


	/* This loop ensures that each character is considered for decryption */

	for (int i=0; i<strlen(input); i++)
	{
		if ((input[i]!='0')&&(input[i]!='1')&&(input[i]!='2')&&(input[i]!='3')&&(input[i]!='4')&&
			(input[i]!='5')&&(input[i]!='6')&&(input[i]!='7')&&(input[i]!='8')&&(input[i]!='9'))
		{
			continue;
		}


		/* Separates each ASCII letter */

		if ((input[i]=='0') && (zero_count==0))
		{
			/* Searches for ASCII letter of current encrypted code in buffer */

			if (input[i+1]=='0') {zero_count++;}


			for (int j=0; j<TOTAL_CHARS; j++)
			{
				/* Transform if matching code is found */

				if (!strcmp(buffer,prime_codes[j]))
				{
					const_charappend(output,keyboard_chars[j]);
					memset(buffer, 0, strlen(buffer)*sizeof(char));

					break;
				}



				/* Continue if code isn't found yet */

				else if (strcmp(buffer,prime_codes[j]))
				{
					continue;
				}
			}
		}



		else if ((input[i]=='0') && (zero_count==1))
		{
			zero_count = 0;

			break;
		}



		/* If this character is part of current word (word != memory unit) */

		else if (input[i]!='0')
		{
			charappend(buffer,input[i]);

			continue;
		}
	}


	return output;
}










char keymapped(char *input)
{
	for (int i=0; i<TOTAL_CHARS; i++)
	{
		if (!strcmp(input, prime_codes[i])) {return keyboard_chars[i];}
	}

	return ' ';
}



#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */