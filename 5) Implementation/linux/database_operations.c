#include "database_operations.h"




















/* Initializations */

FILE *fptr = NULL;
FILE *cache = NULL;

char command[COMMAND_MAX_LENGTH] = {0};
char database[DATABASE_MAX_LENGTH] = {0};
char table[TABLE_MAX_LENGTH] = {0};
char directory[DIRECTORY_MAX_LENGTH] = {0};
char buffer[BUFFER_MAX_LENGTH] = {0};
char dataType[DATA_TYPE_MAX_LENGTH] = {0};
char attribute[ATTRIBUTE_MAX_LENGTH] = {0};

char flusher = '$';

int state = 0;							// Main automaton
int state2 = 0;							// Table attribute automaton
int zero_count = 0;

int brk = FALSE;						// Set TRUE when the syntax goes wrong.
int brk2 = FALSE;
int valid = TRUE;						// Syntax if found wrong, only then invalid.

int TABLES_JSON_DEFAULT = 48;
int EXPANSION_SIZE = 22;




















/* This function clears a string, identified through entered value of string. */

void clearEntity(char *str)
{
	if (!strcmp(str,"command")) {memset(command, 0, COMMAND_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"database")) {memset(database, 0, DATABASE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"table")) {memset(table, 0, TABLE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"directory")) {memset(directory, 0, DIRECTORY_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"buffer")) {memset(buffer, 0, BUFFER_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"dataType")) {memset(dataType, 0, DATA_TYPE_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"attribute")) {memset(attribute, 0, ATTRIBUTE_MAX_LENGTH*sizeof(char));}
}










/* Checks if the user requested database exists or not. */

int checkDbExistence(int msg)
{
	int existence;

	snprintf(directory, sizeof(directory), "data/%s/tables.json", database);
	fptr = fopen(directory, "r");



	if (fptr==NULL && msg==TRUE)
	{
		existence = FALSE;

		printf("ERROR: No database named \"%s\" exists!\n\n", database);
		clearEntity("database");
	}



	else if (fptr==NULL && msg==FALSE)
	{
		existence = FALSE;
	}



	else if (fptr!=NULL && msg==TRUE)
	{
		existence = TRUE;
		printf("STAT: Database %s online!\n\n", database);

		fclose(fptr);
	}



	else if (fptr!=NULL && msg==FALSE)
	{
		existence = TRUE;

		fclose(fptr);
	}



	return existence;
}










/* Checks if a user requested table exists or not. */

int checkTableExistence(int msg)
{
	int existence;

	snprintf(directory, sizeof(directory), "data/%s/%s/details.json", database, table);
	fptr = fopen(directory, "r");



	if (strlen(database)==0 && msg==TRUE) {printf("ERROR: No database opened yet!\n\n");}
	else if (fptr==NULL && msg==FALSE) {existence = FALSE;}


	else if (fptr==NULL && msg==TRUE)
	{
		printf("ERROR: No table named \"%s\" exists!\n\n", table);
		clearEntity("table");

		existence = FALSE;
	}


	else if (fptr!=NULL && msg==FALSE) {existence = TRUE;}
	else if (fptr!=NULL && msg==TRUE) {tableStructure(); existence = TRUE;}


	return existence;
}










/* Shows structure of the requested table (console design comes before fetching). */

void tableStructure()
{
	printf("+"); for (int i=0; i<(32+11+10+2); i++) {printf("-");} printf("+\n");
	printf("|         ATTRIBUTE NAME         | DATA TYPE | KEY TYPE |\n");
	printf("+"); for (int i=0; i<(32+11+10+2); i++) {printf("-");} printf("+\n");





	char c = '$', c2 = '$';

	while (!(c2==']' && c=='\n'))
	{

		// Printing the attribute name.

		printf("|");

		c = '$'; c2 = '$';


		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';

		clearEntity("buffer");

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			if (c!='\"'){buffer[strlen(buffer)] = c;}
		}

		c = '$'; c2 = '$';

		printf("%s", buffer);
		for (int i=strlen(buffer); i<32; i++) {printf(" ");}





		// Printing the attribute data type.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';

		clearEntity("buffer");

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			if (c!='\"'){buffer[strlen(buffer)] = c;}
		}

		c = '$'; c2 = '$';

		printf("%s", buffer);
		for (int i=strlen(buffer); i<11; i++) {printf(" ");}





		// Printing the key type of attribute.

		printf("|");

		while (c!='\"') {c2 = c; c = fgetc(fptr);}
		c = '$'; c2 = '$';

		clearEntity("buffer");

		while(c!='\"')
		{
			c2 = c; c = fgetc(fptr);
			if (c!='\"'){buffer[strlen(buffer)] = c;}
		}



		// Resetting is done at top to avoid detecting end of attribute in JSON file.



		printf("%s", buffer);
		for (int i=strlen(buffer); i<10; i++) {printf(" ");}
		printf("|\n");

		c = fgetc(fptr); c2 = c; c = fgetc(fptr);
	}





	c = '$'; c2 = '$';
	printf("+"); for (int i=0; i<(32+11+10+2); i++) {printf("-");} printf("+\n\n");

	clearEntity("buffer");
	fclose(fptr);
}











/* Shows all the available databases. */

void allDatabases()
{
	fptr = fopen("data/databases.json", "r");
	if (fptr==NULL) {printf("ERROR: databases.json file not found!\n\n");}

	char c = '$';
	int count = 0, reading = FALSE;



	while (count!=3)
	{
		c = fgetc(fptr);

		if (c=='\"') {count++;}
		if (feof(fptr)) {printf("ERROR: No databases found!\n\n");}
	}



	reading = TRUE;
	clearEntity("buffer");
	c = fgetc(fptr);						// Advance reading byte after ("), to enter while loop. 



	printf("+----------------+\n");
	printf("|   DATABASES    |\n");
	printf("+----------------+\n");

	while (!feof(fptr))
	{
		while (c!='\"') {buffer[strlen(buffer)] = c; c = fgetc(fptr);}

		reading = FALSE;
		c = '$';

		printf("|%s", buffer);
		for (int i=strlen(buffer); i<16; i++) {printf(" ");}
		printf("|\n");

		clearEntity("buffer");



		while (c!='\"')
		{
			c = fgetc(fptr);
			if (feof(fptr)) {break;}
		}

		reading = TRUE;

		c = fgetc(fptr);			// Advance reading byte after ("), to enter while loop. 
	}



	clearEntity("buffer");
	fclose(fptr);



	printf("+----------------+\n\n");
}










/* Shows all available tables in the online database. */

void allTables()
{
	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/tables.json", database);

	fptr = fopen(directory, "r");

	if (fptr==NULL)
	{
		printf("ERROR: No database named \"%s\" exists.\n\n", database);
		return;
	}





	char c = '$';
	int count = 0, reading = FALSE;


	while (count!=3)
	{
		c = fgetc(fptr);

		if (c=='\"') {count++;}
		if (feof(fptr)) {printf("STAT: Database is empty.\n\n"); break;}
	}





	/* Print tables only if atleast 1 table exists i.e. less than 3 (2) \" are read from tables.json */

	if (count==3)
	{
		reading = TRUE;
		clearEntity("buffer");
		c = fgetc(fptr);				// Advance reading byte after ("), to enter while loop. 



		printf("+----------------+\n");
		printf("|    TABLES      |\n");
		printf("+----------------+\n");

		while (!feof(fptr))
		{
			while (c!='\"') {buffer[strlen(buffer)] = c; c = fgetc(fptr);}

			reading = FALSE;
			c = '$';

			printf("|%s", buffer);
			for (int i=strlen(buffer); i<16; i++) {printf(" ");}
			printf("|\n");

			clearEntity("buffer");



			while (c!='\"')
			{
				c = fgetc(fptr);
				if (feof(fptr)) {break;}
			}

			reading = TRUE;

			c = fgetc(fptr);			// Advance reading byte after ("), to enter while loop. 
		}



		clearEntity("buffer");
		fclose(fptr);



		printf("+----------------+\n\n");
	}
}










/* This funstion checks if a invalid data type was passed. (MAKE THEM CASE INSENSITIVE) */

void checkDataType()
{
	if ((!strcmp(dataType,"int"))||(!strcmp(dataType,"float"))||(!strcmp(dataType,"string"))||(!strcmp(dataType,"bool"))) {}
	else {valid = FALSE; state2 = 8; brk2 = TRUE;}
}










/* Creates a table & configures many files. */

void makeTable()
{
	char decision, c='$', c2='$';

	int write = TRUE;
	int charCount = 0, invCount = 0;

	char insertStr[32] = {0};



	if (checkDbExistence(FALSE)==FALSE)
	{
		printf("ERROR: No database opened yet!\n\n");
		write = FALSE;
	}



	else if ((checkDbExistence(FALSE)==TRUE) && (checkTableExistence(FALSE)==TRUE))
	{
		printf("Table already exists!\n\n");
		printf("Overwrite data to disk? (y/n): "); decision = getchar();


		if (decision=='n') {write = FALSE;}

		else if (decision=='y')
		{
			clearEntity("directory");
			snprintf(directory, sizeof(directory), "cd data/%s && rm -rf %s", database, table);

			system(directory);
		}
	}



	else if ((checkDbExistence(FALSE)==TRUE) && (checkTableExistence(FALSE)==FALSE))
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.json", database);
		fptr = fopen(directory, "r+");



		while (!(c2==']'&&c=='\n'))
		{
			charCount++;
			c2 = c; c = fgetc(fptr);

			if (c=='\"') {invCount++;}
		}

		fflush(fptr);


		if (invCount==2) {snprintf(insertStr, sizeof(insertStr), "\n\t\t\"%s\"\n\t]\n}", table);}
		else if (invCount>2) {snprintf(insertStr, sizeof(insertStr), ",\n\t\t\"%s\"\n\t]\n}", table);}


		fseek(fptr, (charCount-4), SEEK_SET);
		fputs(insertStr, fptr);
		fflush(fptr);



		fclose(fptr);
	}





	/* If new table is made, or if an exisiting table is overwritten. */

	if (write==TRUE)
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "cd data/%s && mkdir %s", database, table);

		system(directory);

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/rows.json", database, table);
		

		/* rows.json */

		fptr = fopen(directory, "w");
		fputs("{\n\t\"rows\": [\n\t]\n}", fptr);
		fflush(fptr);

		fclose(fptr);



		/* details.json */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/details.json", database, table);

		fptr = fopen(directory, "w");


		fputs("{\n\t", fptr);
		fflush(fptr);


		for (int i=0; i<strlen(buffer); i++)
		{
			while (buffer[i]==' ') {i++;}
			while (buffer[i]!=' ') {dataType[strlen(dataType)] = buffer[i]; i++;}
			while (buffer[i]==' ') {i++;}
			while (buffer[i]!=',' && i!=strlen(buffer)) {attribute[strlen(attribute)] = buffer[i]; i++;}

			clearEntity("directory");
			snprintf(directory, sizeof(directory), "\"%s\": [\"%s\", \"regular\"]", attribute, dataType);
			fputs(directory, fptr);
			fflush(fptr);

			if (buffer[i]==',') {fputs(",\n\t", fptr);}

			clearEntity("dataType"); clearEntity("attribute");
		}

		fputs("\n}", fptr);
		fflush(fptr);


		fclose(fptr);
		clearEntity("buffer");

		printf("OK: Table created successfully!\n\n");
	}
}










/* Make a database on user's request. */

void makeDb()
{
	char decision, c='$', c2='$';

	int write = TRUE;
	int charCount = 0, invCount = 0;

	char insertStr[32] = {0};


	
	/* If database already exists. */

	if (checkDbExistence(FALSE)==TRUE)
	{
		printf("Database already exists!\n\n");
		printf("Overwrite data to disk? (y/n): "); decision = getchar();


		if (decision=='n') {write=FALSE;}

		else if (decision=='y')
		{
			clearEntity("directory");
			snprintf(directory, sizeof(directory), "cd data && rm -rf %s", database);

			system(directory);
		}
	}



	/* If database doesn't exist. */

	else
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/databases.json");
		fptr = fopen(directory, "r+");



		while (!(c2==']'&&c=='\n'))
		{
			charCount++;
			c2 = c; c = fgetc(fptr);

			if (c=='\"') {invCount++;}
		}

		fflush(fptr);


		/* Insert into databases.json as per if any database exist or not. */

		if (invCount==2) {snprintf(insertStr, sizeof(insertStr), "\n\t\t\"%s\"\n\t]\n}", database);}
		else if (invCount>2) {snprintf(insertStr, sizeof(insertStr), ",\n\t\t\"%s\"\n\t]\n}", database);}

		fseek(fptr, (charCount-4), SEEK_SET);
		fputs(insertStr, fptr);
		fflush(fptr);



		fclose(fptr);
	}





	/* If new database is created, or if an existing one is overwritten. */

	if (write==TRUE)
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "cd data && mkdir %s", database);

		system(directory);

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.json", database);



		/* tables.json */

		fopen(directory, "w");
		fputs("{\n\t\"tables\": [\n\t]\n}", fptr);
		fflush(fptr);

		fclose(fptr);

		clearEntity("buffer");
		
		printf("OK: Database created successfully!\n\n");
	}
}










/* Deleting a table. */

void deleteTable()
{
	char c = '$', c2 = '$';
	int charCount = 0, invCount = 0;
	int head, tail;





	if (checkTableExistence(FALSE)==FALSE) {printf("ERROR: No table named \"%s\" exists!\n\n", table);}

	
	else if (checkTableExistence(FALSE)==TRUE)
	{
		/* Removing the table related directory. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm -rf data/%s/%s", database, table);

		system(directory);



		/* Erasing name from list of all available tables. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/tables.json", database);

		fptr = fopen(directory, "r");



		while (invCount!=2)
		{
			c2 = c; c = fgetc(fptr); charCount++;
			if (c=='\"') {invCount++;}
		}





		/* Searching for two consecutive tab-spaces. */

		while (!reachedEOF(fptr))
		{	
			do {
				c2 = c; c = fgetc(fptr); charCount++;

				if (c2=='\t' && c=='\t') {invCount++; head = charCount - 1;}

			} while (c!='\"');




			/* Storing characters to buffer. */

			clearEntity("buffer");

			do {
				c2 = c; c = fgetc(fptr); charCount++;

				if (c!='\"') {buffer[strlen(buffer)] = c;}

			} while (c!='\"');



			if (!strcmp(table,buffer))
			{
				/* Searching for two consecutive tab-spaces. */

				while (!(c2=='\t' && c=='\t'))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					if (c2=='\t' && c=='\t') {invCount++; tail = charCount - 1;}
				}


				/* Pasting required content to 'chache.tosbit' file. */

				cache = fopen("data/cache.tosbit", "w");
				fseek(fptr, 0, SEEK_SET); charCount = 0;

				while (charCount!=head)
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}


				fseek(fptr, tail, SEEK_SET);

				/* WARNING: Beware! FEOF in any WHILE loop always reads an extra garbage value. */

				while (!reachedEOF(fptr))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}


				fclose(fptr); fclose(cache);


				/* Write content in cache.tosbit to respective 'tables.json' */

				fptr = fopen(directory, "w");
				cache = fopen("data/cache.tosbit", "r");

				while (!reachedEOF(cache))
				{
					c2 = c; c = fgetc(cache); charCount++;

					fputc(c, fptr);
				}

				fclose(fptr); fclose(cache);

				system("rm -rf data/cache.tosbit");



				printf("OK: Table has been successfully deleted!\n\n");
				break; // Why does this overwrites entire file if files not closed?
			}



			else if (strcmp(table,buffer)) {continue;}
		}
	}
}