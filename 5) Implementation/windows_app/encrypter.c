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



#endif



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */