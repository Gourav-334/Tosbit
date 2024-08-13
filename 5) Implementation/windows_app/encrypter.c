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
	static char output[MAX_ENCRYPTED_SIZE] = {0};
	
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

	return output;
}





char *decrypt(char *input)
{
	static char output[MAX_ENCRYPTED_SIZE] = {0};
	char buffer[MAX_DECRYPTED_SIZE] = {0};

	for (int i=0; i<strlen(input); i++)
	{
		if (input[i]=='0')
		{
			for (int j=0; j<TOTAL_CHARS; j++)
			{
				if (!strcmp(buffer,prime_codes[j]))
				{
					const_charappend(output,keyboard_chars[j]);
					memset(buffer, 0, strlen(buffer)*sizeof(char));

					break;
				}

				else if (strcmp(buffer,prime_codes[j]))
				{
					continue;
				}
			}
		}



		else if (input[i]!='0')
		{
			charappend(buffer,input[i]);

			continue;
		}
	}

	return output;
}



#endif