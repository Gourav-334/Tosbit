#ifndef UTILITY_BOX_C
	#define UTILITY_BOX_C


#include "utility_box.h"





void strappend(char str[], int *cursor_pos, char *addition)
{
	for (int i=0; i<strlen(addition); i++)
	{
		str[i + (*cursor_pos)] = addition[i];
	}

	*cursor_pos += strlen(addition);
}





void charappend(char str[], int *cursor_pos, char addition)
{
	str[*cursor_pos] = addition;

	*cursor_pos += sizeof(char);
}





void newline_remover(char str[])
{
	if (str[strlen(str)-1]=='\n')
	{
		memset((str+(strlen(str)-1)), 0, sizeof(char));
	}
}





void flush_stdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}





#endif	//Drink mango juice after this code.