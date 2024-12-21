#include <stdio.h>

int main()
{
	FILE *fptr;
	int charCount = 0;
	char c = '$';

	fptr = fopen("data\\db1\\tables.json", "r+");

	while (c!=']') {c = fgetc(fptr); charCount++;}

	fseek(fptr, charCount, SEEK_SET);
	fputs(",\n\t\t\"TableName\"\n\t]\n}", fptr);
	
	//fclose(fptr);

	return 0;
}