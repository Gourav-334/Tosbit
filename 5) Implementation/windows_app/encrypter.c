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





char *encrypt(char *input)
{
	static char output[MAX_OUTPUT_SIZE];
	memset(output, 0, MAX_OUTPUT_SIZE*sizeof(char));
	
	for (int i=0; i<strlen(input); i++)
	{
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
	memset((output + strlen(output)), 0, (strlen(output)-strlen(output))*sizeof(char));

	return output;
}





char *decrypt(char *input)
{
	static char output[MAX_OUTPUT_SIZE];
	memset(output, 0, MAX_OUTPUT_SIZE*sizeof(char));

	char character[4] = {0}; 
	int zero_count = 0;
	
	for (int i=0; i<strlen(input); i++)
	{
		if (input[i]!='0')
		{
			if (zero_count==1) {zero_count = 0;}

			charappend(character, input[i]);
		}

		else if ((input[i]=='0')&&(zero_count==0))
		{
			zero_count++;

			for (int j=0; j<TOTAL_CHARS; j++)
			{
				if (!strcmp(character, prime_codes[j]))
				{
					charappend(output, keyboard_chars[j]);
					memset(character, 0, strlen(character)*sizeof(char));

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