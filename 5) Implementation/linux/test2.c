#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
	char *fileBuffer;
	size_t TABLES_JSON_DEFAULT = 22;

	fileBuffer = malloc(TABLES_JSON_DEFAULT*sizeof(char));

	strcpy(fileBuffer, "GouravKumarMallickGoodB");

	printf("STR: %s\tLENGTH: %d\tSIZE: %d\n", fileBuffer, strlen(fileBuffer), sizeof(fileBuffer));

	return 0;
}