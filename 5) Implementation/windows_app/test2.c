#include <stdio.h>

int main()
{
	FILE *reader, *writer;
	char c = '#';

	writer = fopen("data\\db1\\tables.json", "r+");

	while (c!='[')
	{
		c = fgetc(writer);
		printf("FTELL: %d\tCHAR: %c\n", ftell(writer), c);
	}

	fputc('$', writer);
	fclose(writer);

	return 0;
}