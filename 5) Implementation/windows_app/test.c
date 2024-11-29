#include "syntax_parser.c"



int main()
{
	//syntax_parser("Gourav");

	FILE *fptr = NULL;
	char c;

	fptr = fopen("data\\db1\\table1\\details.json", "r");
	if (fptr==NULL) {perror("The fuck you writing man?");}

	while(!feof(fptr))
	{
		c = fgetc(fptr);

		if (c=='\t') {printf("YES! HELL YEAH!\n");}

		printf("%c", c);
	}

	return 0;
}
