#include "../include/database_operations.h"




















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
char pureValue[VALUE_MAX_LENGTH] = {0};

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
	else if (!strcmp(str,"pureValue")) {memset(pureValue, 0, VALUE_MAX_LENGTH*sizeof(char));}
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
		do {c2 = c; c = fgetc(fptr2); value2[strlen(value2)] = c;} while (c!='\"');

		if (!strcmp(value,value2)) {return FALSE;}

		while (invCount!=totalArg*4) {c2 = c; c = fgetc(fptr2);}
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

int typeParser()
{
	int status;
	FILE *media;



	/* int: Integers */

	if (!strcmp(dataType,"int"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " 0123456789", "0,1,1,1,1,1,1,1,1,1,1", &state2, 3); breakValue(&state2, 3, &brk2); appendState(&state2, 1, pureValue, value[i]); break;
				case 1: changeState(value[i], "0123456789 ", "1,1,1,1,1,1,1,1,1,1,2", &state2, 3); breakValue(&state2, 3, &brk2); appendState(&state2, 1, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 4, &brk2); break;
				case 2: changeState(value[i], " ", "2", &state2, 3); breakValue(&state2, 3, &brk2); break;
			}


			if (brk2==TRUE) {brk2 = FALSE; break;}
		}





		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);





		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: printf("ERROR: (%s) Argument passed as integer is blank!\n\n", pureValue); status = FALSE; break;
			case 1: state2 = 0; status = TRUE; break;
			case 2: state2 = 0; status = TRUE; break;
			case 3: printf("ERROR: (%s) An integer argument is expected!\n\n", pureValue); status = FALSE; break;
			case 4: printf("ERROR: (%s) Integer value passed exceeds 32 digits!\n\n", pureValue); status = FALSE; break;
		}


		state2 = 0; valid = TRUE;
	}





	/* string: String */

	else if (!strcmp(dataType,"string"))
	{
		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);

		if (strlen(pureValue)>VALUE_MAX_LENGTH-1) {printf("ERROR: (%s) String value passed exceeds 32 digits!\n\n", pureValue); status = FALSE;}
	}





	/* float: Floating point decimals */

	else if (!strcmp(dataType,"float"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " 0123456789", "0,1,1,1,1,1,1,1,1,1,1", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 1, pureValue, value[i]); break; // Debug this headache, man...
				case 1: changeState(value[i], "0123456789.", "1,1,1,1,1,1,1,1,1,1,2", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 1, pureValue, value[i]); appendState(&state2, 2, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &brk2); break;
				case 2: changeState(value[i], "0123456789", "3,3,3,3,3,3,3,3,3,3", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 3, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &brk2); break;
				case 3: changeState(value[i], "0123456789", "3,3,3,3,3,3,3,3,3,3", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 3, pureValue, value[i]); limitChecker(pureValue, (VALUE_MAX_LENGTH-1), &state2, 7, &brk2); break;
				case 4: changeState(value[i], " ", "4", &state2, 5); breakValue(&state2, 5, &brk2); appendState(&state2, 1, pureValue, value[i]); break;
			}


			if (brk2==TRUE) {brk2 = FALSE; break;}
		}





		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);





		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: printf("ERROR: (%s) Argument passed as float is blank!\n\n", pureValue); status = FALSE; break;
			case 1: printf("ERROR: (%s) Float has no decimal point!\n\n", pureValue); status = FALSE; break;
			case 2: printf("ERROR: (%s) No number written after decimal point!\n\n", pureValue); status = FALSE; break;
			case 3: state2 = 0; status = TRUE; break;
			case 4: state2 = 0; status = TRUE; break;
			case 5: printf("ERROR: (%s) Supposed float argument is not float!\n\n", pureValue); status = FALSE; break;
			case 6: printf("ERROR: (%s) Float value passed exceeds 32 digits!\n\n", pureValue); status = FALSE; break;
		}


		state2 = 0; valid = TRUE;
	}





	/* bool: Boolean */

	else if (!strcmp(dataType,"bool"))
	{
		for (int i=0; i<strlen(value); i++)
		{
			switch (state2)
			{
				case 0: clearEntity("pureValue"); changeState(value[i], " ft", "0,1,6", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 1, pureValue, value[i]); break;
				case 1: changeState(value[i], "a", "2", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 2, pureValue, value[i]); break;
				case 2: changeState(value[i], "l", "3", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 3, pureValue, value[i]); break;
				case 3: changeState(value[i], "s", "4", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 4, pureValue, value[i]); break;
				case 4: changeState(value[i], "e", "5", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 5, pureValue, value[i]); break;
				case 5: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &brk2); break;
				case 6: changeState(value[i], "r", "7", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 7, pureValue, value[i]); break;
				case 7: changeState(value[i], "u", "8", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 8, pureValue, value[i]); break;
				case 8: changeState(value[i], "e", "9", &state2, 11); breakValue(&state2, 11, &brk2); appendState(&state2, 9, pureValue, value[i]); break;
				case 9: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &brk2); break;
				case 10: changeState(value[i], " ", "10", &state2, 11); breakValue(&state2, 11, &brk2); break;
			}


			if (brk2==TRUE) {brk2 = FALSE; break;}
		}





		/* Re-removal of whitespaces in case value was dumped beforehand. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);





		/* Final result, or action to be taken on last stage. */

		switch (state2)
		{
			case 0: printf("ERROR: (%s) Argument passed as boolean is blank!\n\n", pureValue); status = FALSE; break;
			case 1: printf("ERROR: (%s) Did you meant \"false\"!\n\n", pureValue); status = FALSE; break;
			case 2: printf("ERROR: (%s) Did you meant \"false\"!\n\n", pureValue); status = FALSE; break;
			case 3: printf("ERROR: (%s) Did you meant \"false\"!\n\n", pureValue); status = FALSE; break;
			case 4: printf("ERROR: (%s) Did you meant \"false\"!\n\n", pureValue); status = FALSE; break;
			case 5: state2 = 0; status = TRUE; break;
			case 6: printf("ERROR: (%s) Did you meant \"true\"!\n\n", pureValue); status = FALSE; break;
			case 7: printf("ERROR: (%s) Did you meant \"true\"!\n\n", pureValue); status = FALSE; break;
			case 8: printf("ERROR: (%s) Did you meant \"true\"!\n\n", pureValue); status = FALSE; break;
			case 9: state2 = 0; status = TRUE; break;
			case 10: state2 = 0; status = TRUE; break;
			case 11: printf("ERROR: (%s) Argument is neither \"true\" or \"false\"!\n\n", pureValue); status = FALSE; break;
		}


		state2 = 0; valid = TRUE;
	}





	/* media: Media files */

	else if (!strcmp(dataType,"media"))
	{
		/* Removing whitespaces. */

		clearEntity("pureValue");
		spaceRemover(value, pureValue, VALUE_MAX_LENGTH);

		

		/* Checking existence of media file. */

		media = fopen(pureValue, "r");

		if (media==NULL) {printf("ERROR: (%s) No such provided path exists!\n\n", pureValue); status = FALSE;}
		else {printf("OK: File is being compressed...\n\n"); status = TRUE;}
	}



	return status;
}










/* Pushing row into a table. {push to programmer(1, Gourav, 97.2)} */

void pushRow()
{
	/* Declarations */

	char c='$', c2='$';
	int commaCount=0, invCount=0, buffIndex=0, totalArg, currArg=0;
	char currAttribute[33]={0}, currDataType[33]={0}, currValue[33]={0};



	/* Queue objects (structures). */

	Queue attributeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll
	};

	Queue dataTypeQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll
	};

	Queue valueQueue = {
		.n = 0,
		.pos = 0,
		.m = NULL,
		.head = NULL, 
		.temp = NULL,
		.trav = NULL,
		.queue = Queue_queue,
		.clear = Queue_clear,
		.getIndex = Queue_getIndex,
		.getValue = Queue_getValue,
		.peek = Queue_peek,
		.showAll = Queue_showAll
	};



	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/details.json", database, table);
	fptr = fopen(directory, "r");

	clearEntity("directory");
	snprintf(directory, sizeof(directory), "data/%s/%s/rows.json", database, table);
	fptr2 = fopen(directory, "r+");



	/* Safety checks */

	if (checkDbExistence(FALSE)==FALSE) {printf("ERROR: No database opened yet!\n\n"); return;}
	else if (checkTableExistence(FALSE)==FALSE) {printf("ERROR: No table named \"%s\" exists!\n\n", table); return;}



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


		if (!strcmp(key,"unique"))
		{
			if (checkUnique(value, currArg, totalArg)==FALSE)
			{
				printf("ERROR: Duplicate for unique key \"%s\"!\n\n", attribute);
			}
		}


		if (typeParser()==FALSE) {return;}


		attributeQueue.queue(&attributeQueue, attribute);
		dataTypeQueue.queue(&dataTypeQueue, dataType);
		valueQueue.queue(&valueQueue, pureValue);	
	}

	fclose(fptr);		// For "details.json"



	/* Inserting values. */

	fseek(fptr2, -6, SEEK_END);
	c2 = c; c = fgetc(fptr2);

	if (c=='}') {fputs(",\n", fptr2);}

	fputs("\n\t\t{", fptr2);


	for (int i=0; i<totalArg; i++)
	{
		/* Clearing strings & pasting the required value (for shorter string names). */

		memset(currAttribute, 0, sizeof(currAttribute));
		memset(currDataType, 0, sizeof(currDataType));
		memset(currValue, 0, sizeof(currValue));

		strcpy(currAttribute, attributeQueue.getValue(&attributeQueue,i));
		strcpy(currDataType, dataTypeQueue.getValue(&dataTypeQueue,i));
		strcpy(currValue, valueQueue.getValue(&valueQueue,i));



		/* Inserting arguments to JSON document. */

		clearEntity("buffer");
		snprintf(buffer, sizeof(buffer), "\n\t\t\t\"%s\": ", currAttribute);
		fputs(buffer, fptr2);

		clearEntity("buffer");

		if ((!strcmp(currDataType,"string"))||(!strcmp(currDataType,"media")))
		{
			snprintf(buffer, sizeof(buffer), "\"%s\"", currValue);
		}

		else
		{
			snprintf(buffer, sizeof(buffer), "%s", currValue);
		}

		fputs(buffer, fptr2);



		/* For non-last value, inserting comma. */

		if (i!=totalArg-1) {fputc(',', fptr2);}
	}



	/* Final insertions. */

	fputs("\n\t\t}\n\t]\n}", fptr2);



	/* Closing file descriptor & clear queues. */

	fclose(fptr2);
	
	attributeQueue.clear(&attributeQueue);
	dataTypeQueue.clear(&dataTypeQueue);
	valueQueue.clear(&dataTypeQueue);



	printf("OK: Row pushed successfully!\n\n");
}