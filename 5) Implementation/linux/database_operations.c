#include "database_operations.h"




















/* Initializations */

FILE *fptr = NULL;
FILE *fptr2 = NULL;
FILE *cache = NULL;

char command[COMMAND_MAX_LENGTH] = {0};
char database[DATABASE_MAX_LENGTH] = {0};
char table[TABLE_MAX_LENGTH] = {0};
char directory[DIRECTORY_MAX_LENGTH] = {0};
char buffer[BUFFER_MAX_LENGTH] = {0};
char dataType[DATA_TYPE_MAX_LENGTH] = {0};
char attribute[ATTRIBUTE_MAX_LENGTH] = {0};
char key[KEY_MAX_LENGTH] = {0};
char value[VALUE_MAX_LENGTH] = {0};

char flusher = '$';

int state = 0;							// Main automaton
int state2 = 0;							// Table attribute automaton
int zero_count = 0;

int brk = FALSE;						// Set TRUE when the syntax goes wrong.
int brk2 = FALSE;
int valid = TRUE;						// Syntax if found wrong, only then invalid.




















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
	else if (!strcmp(str,"key")) {memset(key, 0, KEY_MAX_LENGTH*sizeof(char));}
	else if (!strcmp(str,"value")) {memset(value, 0, VALUE_MAX_LENGTH*sizeof(char));}
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
		printf("ERROR: No database opened yet!\n\n");
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










/* This funstion checks if a invalid data type was passed. (NOT "CASE INSENSITIVE") */

void checkDataType()
{
	if ((!strcmp(dataType,"int"))||(!strcmp(dataType,"float"))||(!strcmp(dataType,"string"))||(!strcmp(dataType,"bool"))||(!strcmp(dataType,"media"))) {}
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
// float

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





	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database opened yet!\n\n");}



	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==FALSE)
	{
		printf("ERROR: No table named \"%s\" exists!\n\n", table);
	}


	
	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==TRUE)
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

				while (!((c2=='\t' && c=='\t')||(c2=='\t' && c==']')))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					if ((c2=='\t' && c=='\t')||(c2=='\t' && c==']')) {invCount++; tail = charCount - 1;}
				}


				/* Pasting required content to 'chache.tosbit' file. */

				cache = fopen("data/cache.tosbit", "w");
				fseek(fptr, 0, SEEK_SET); charCount = 0;

				while (charCount!=head)
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}

				fflush(cache);


				fseek(fptr, tail, SEEK_SET);


				/* WARNING: Beware! FEOF in any WHILE loop always reads an extra garbage value. */

				while (!reachedEOF(fptr))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}

				fflush(cache);

				fclose(fptr); fclose(cache);



				/* Write content in cache.tosbit to respective 'tables.json' */

				fptr = fopen(directory, "w");
				cache = fopen("data/cache.tosbit", "r");

				while (!reachedEOF(cache))
				{
					c2 = c; c = fgetc(cache); charCount++;

					fputc(c, fptr);
				}

				fflush(fptr);

				fclose(fptr); fclose(cache);

				system("rm -rf data/cache.tosbit");



				/* Removing ',' if last entry was read. ,\n\t]\n} */

				fptr = fopen(directory, "r+");
				fseek(fptr, -6, SEEK_END);

				if (fgetc(fptr)==',')
				{
					fseek(fptr, -1, SEEK_CUR);
					fputs("\n\t]\n} ", fptr);

					fflush(fptr);
				}

				fclose(fptr);



				printf("OK: Table deleted successfully!\n\n");
				break; // Why does this overwrites entire file if files not closed?
			}



			else if (strcmp(table,buffer)) {continue;}
		}
	}
}










/* Deleting a database. */

void deleteDb()
{
	char c = '$', c2 = '$';
	int charCount = 0, invCount = 0;
	int head, tail;





	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database named \"%s\" exists!\n\n", database);}



	else if (checkDbExistence(FALSE)==TRUE)
	{
		/* Removing the database related directory. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm -rf data/%s", database);

		system(directory);



		/* Erasing name from list of all available databases. */

		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/databases.json");

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



			if (!strcmp(database,buffer))
			{
				/* Searching for two consecutive tab-spaces. */

				while (!((c2=='\t' && c=='\t')||(c2=='\t' && c==']')))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					if ((c2=='\t' && c=='\t')||(c2=='\t' && c==']')) {invCount++; tail = charCount - 1;}
				}


				/* Pasting required content to 'chache.tosbit' file. */

				cache = fopen("data/cache.tosbit", "w");
				fseek(fptr, 0, SEEK_SET); charCount = 0;

				while (charCount!=head)
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}

				fflush(cache);

				fseek(fptr, tail, SEEK_SET);


				/* WARNING: Beware! FEOF in any WHILE loop always reads an extra garbage value. */

				while (!reachedEOF(fptr))
				{
					c2 = c; c = fgetc(fptr); charCount++;

					fputc(c, cache);
				}

				fflush(cache);

				fclose(fptr); fclose(cache);



				/* Write content in cache.tosbit to respective 'tables.json' */

				fptr = fopen(directory, "w");
				cache = fopen("data/cache.tosbit", "r");

				while (!reachedEOF(cache))
				{
					c2 = c; c = fgetc(cache); charCount++;

					fputc(c, fptr);
				}

				fflush(fptr);

				fclose(fptr); fclose(cache);

				system("rm -rf data/cache.tosbit");



				/* Removing ',' if last entry was read. ,\n\t]\n} */

				fptr = fopen(directory, "r+");
				fseek(fptr, -6, SEEK_END);

				if (fgetc(fptr)==',')
				{
					fseek(fptr, -1, SEEK_CUR);
					fputs("\n\t]\n} ", fptr);

					fflush(fptr);
				}

				fclose(fptr);



				printf("OK: Database deleted successfully!\n\n");
				break; // Why does this overwrites entire file if files not closed?
			}



			else if (strcmp(table,buffer)) {continue;}
		}
	}
}





/* Clears any requested table (clears of all data it holds). */

void clearTable()
{
	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database opened yet!\n\n");}


	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==FALSE)
	{
		printf("ERROR: No table named \"%s\" exists!\n\n", table);
	}


	else if (checkDbExistence(FALSE)==TRUE && checkTableExistence(FALSE)==TRUE)
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "data/%s/%s/rows.json", database, table);

		fptr = fopen(directory, "w");

		fputs("{\n\t\"rows\": [\n\t]\n}", fptr);
		fflush(fptr);

		fclose(fptr);


		printf("OK: Table cleared successfully!\n\n");
	}
}





/* Clear all the tables present in a database. */

void clearDb()
{
	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database named \"%s\" exists!\n\n", database);}


	else if (checkDbExistence(FALSE)==TRUE)
	{
		clearEntity("directory");
		snprintf(directory, sizeof(directory), "rm -rf data/%s", database);
		system(directory);

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


		printf("OK: Database cleared successfully!\n\n");
	}
}










/* Checking if unique value exists or not. (UNTESTED ON UNIQUE KEYS) */

int checkUnique(char value[], int currArg, int totalArg)
{
	int invCount=0;
	char value2[strlen(value)];
	char c='$', c2='$';


	fseek(fptr2, 14, SEEK_SET);

	while (!reachedEOF(fptr2))
	{
		memset(value2, 0, strlen(value)*sizeof(char));
		invCount = 0;

		fseek(fptr2, 1, SEEK_CUR);

		while (invCount!=((currArg-1)*4)+3) {c2 = c; c = fgetc(fptr2); if(c=='\"') {invCount++;}}
		do {c2 = c; c = fgetc(fptr2); value2[strlen(c)] = c;} while (c!='\"');

		if (!strcmp(value,value2)) {return FALSE;}

		while (invCount!=totalArgs*4) {c2 = c; c = fgetc(fptr2);}
		invCount = 0;
		fseek(fptr2, 4, SEEK_CUR);

		c2 = c; c = fgetc(fptr2);

		if (c==',') {fseek(fptr2, 4, SEEK_CUR); continue;}
		else if (c=='\n') {return TRUE;}
		else {printf("ERROR: rows.json file for current table is corrupted!\n\n"); return TRUE;}

		// If having problem with "return", keep the "return TRUE;" line outside loop & break there.
	}
}










/* Data type parsing & validating automaton. */

void typeParser()
{
	if (!strcmp(dataType,"int"))
	{
		for (int i=0; i<strlen(buffer); i++)
		{
			/* Parsing with DFA & Turing machine. */

			switch (state2)
			{
				// Write switch cases...
			}


			if (brk2==TRUE) {brk2 = FALSE; break;}
		}





		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			// Write switch cases...
		}


		// Clear required entities...

		state2 = 0; valid = TRUE;
	}
}










/* Pushing row into a table. {push to programmer(1, Gourav, 97.2)} */

void pushRow()
{
	/* Declarations */

	char c='$', c2='$';
	int commaCount=0, invCount=0, buffIndex=0, totalArg, currArg=0;

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/details.json", database, table);
	fptr = fopen(directory, "r");

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/rows.json", database, table);
	fptr2 = fopen(directory, "r+");



	/* Safety checks */

	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database opened yet!\n\n"); fclose(fptr); fclose(fptr2); return;}
	else if (checkTableExistence(FALSE)==FALSE) {printf("ERROR: No table named \"%s\" exists!\n\n", table); fclose(fptr); fclose(fptr2); return;}



	/* Checking number of argument (less or more or enough). */

	for (int i=0; i<strlen(buffer); i++) {if(buffer[i]==',') {commaCount++;}}
	totalArg = commaCount + 1;

	while (!reachedEOF(fptr))
	{
		c2 = c; c = fgetc(fptr);

		if (c=='\"') {invCount++;}
	}


	if ((totalArg)<(invCount/6)) {printf("ERROR: Very few values passed!\n\n"); fclose(fptr); fclose(fptr2); return;}
	else if ((totalArg)>(invCount/6)) {printf("ERROR: Too many arguments passed!\n\n"); fclose(fptr); fclose(fptr2); return;}

	invCount = 0;
	fseek(fptr, 0, SEEK_SET);



	/* Verifying data types of passed arguments. */

	while (!reachedEOF(fptr))
	{
		clearEntity("attribute"); clearEntity("dataType"); clearEntity("key"); clearEntity("value");

		currArg++;


		do {c2 = c; c = fgetc(fptr);} while (c!='\"');
		do {c2 = c; c = fgetc(fptr); if(c!='\"') {attribute[strlen(attribute)] = c;}} while (c!='\"');

		fseek(fptr, 4, SEEK_CUR);	// Saving search computation time.
		do {c2 = c; c = fgetc(fptr); if(c!='\"') {dataType[strlen(dataType)] = c;}} while (c!='\"');

		fseek(fptr, 3, SEEK_CUR);	// Saving search computation time.
		do {c2 = c; c = fgetc(fptr); if(c!='\"') {key[strlen(key)] = c;}} while (c!='\"');

		for (int i=buffIndex; i<strlen(buffer); i++)
		{
			if (buffer[i]==',') {buffIndex = i + 1; break;}
			else {value[strlen(value)] = buffer[i];}
		}


		fseek(fptr, 3, SEEK_CUR);	// For checking if EOF reached afterwards.


		//printf("ATTR: %s, DT: %s, KEY: %s, VAL: %s\n", attribute, dataType, key, value);

		if (!strcmp(key,"unique"))
		{
			if (checkUnique(value, currArg, totalArg)==FALSE)
			{
				printf("ERROR: Duplicate for unique key \"%s\"!\n\n", attribute);
			}
		}


		typeParser();
	}



	/* Closing file descriptors safely. */

	fclose(fptr); fclose(fptr2);
}