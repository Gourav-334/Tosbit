#include <stdio.h>



int main()
{
	FILE *fptr;

	fptr = fopen("subject.pdf", "rb");

	for (int i=0; i<100; i++)
	{
		printf("%c", fgetc(fptr));
	}

	return 0;
}