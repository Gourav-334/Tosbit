/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */



#include "../include/shell_piping.h"










/* Variables */

char loc[LOC_MAX_LENGTH] = {0};










/* Records log. */

void recordLog(char username[], char command[])
{
	/* Declarations. */

	FILE *logger = NULL;

	int folders, files, logs;

	char c = '$', c2 = '$';
	char time[30] = {0};
	char smallBuff[17] = {0};		// For fetching data from files.
	char writer[129] = {0};			// For writing data to files.
	char largeBuff[512] = {0};		// For storing path.



	/* Reading 'r' log statistics. */

	logger = fopen("logs/details.json", "r");


	memset(smallBuff, 0, sizeof(smallBuff));
	fseek(logger, 14, SEEK_SET);

	while (c!=',') {c2 = c; c = fgetc(logger); smallBuff[strlen(smallBuff)] = c;}
	folders = atoi(smallBuff);


	memset(smallBuff, 0, sizeof(smallBuff));
	fseek(logger, 11, SEEK_CUR);

	do {c2 = c; c = fgetc(logger); smallBuff[strlen(smallBuff)] = c;} while (c!=',');
	files = atoi(smallBuff);


	memset(smallBuff, 0, sizeof(smallBuff));
	fseek(logger, 10, SEEK_CUR);

	do {c2 = c; c = fgetc(logger); smallBuff[strlen(smallBuff)] = c;} while (c!='\n');
	logs = atoi(smallBuff);


	fclose(logger);



	/* Deciding action based on statistics (may use 'w'). */

	if (folders==0)
	{
		folders++; files++; logs++;

		snprintf(largeBuff, sizeof(largeBuff), "mkdir logs/log_folder%d", folders);
		system(largeBuff);


		memset(largeBuff, 0, sizeof(largeBuff));
		snprintf(largeBuff, sizeof(largeBuff), "logs/log_folder%d/log_file%d.json", folders, files);

		logger = fopen(largeBuff, "w");
		fputs("{\n\t\"logs\": [\n\t]\n}", logger);
		fclose(logger);
	}


	else if (files==100 && logs==1000)
	{
		folders++; files = 1; logs = 1;

		snprintf(largeBuff, sizeof(largeBuff), "mkdir logs/log_folder%d", folders);
		system(largeBuff);


		memset(largeBuff, 0, sizeof(largeBuff));
		snprintf(largeBuff, sizeof(largeBuff), "logs/log_folder%d/log_file%d.json", folders, files);

		logger = fopen(largeBuff, "w");
		fputs("{\n\t\"logs\": [\n\t]\n}", logger);
		fclose(logger);
	}


	else if (files==100 && logs<1000) {logs++;}


	else if (files<100 && logs==1000)
	{
		files++; logs = 1;

		snprintf(largeBuff, sizeof(largeBuff), "logs/log_folder%d/log_file%d.json", folders, files);

		logger = fopen(largeBuff, "w");
		fputs("{\n\t\"logs\": [\n\t]\n}", logger);
		fclose(logger);
	}


	else if (files<100 && logs<1000) {logs++;}


	else {printf("ERROR: Log system found corrupted!\n\n"); return;}



	/* Overwriting details.json */

	logger = fopen("logs/details.json", "w");

	snprintf(
		writer, sizeof(writer),
		"{\n\t\"folders\": %d,\n\t\"files\": %d,\n\t\"logs\": %d\n}",
		folders, files, logs
	);

	fputs(writer, logger);
	fclose(logger);



	/* Path for the current or next required log file. */

	memset(largeBuff, 0, sizeof(largeBuff));
	snprintf(largeBuff, sizeof(largeBuff), "logs/log_folder%d/log_file%d.json", folders, files);



	/* Storing time */

	logger = popen("date -u", "r");
	fgets(time, sizeof(time), logger); newline_remover(time);
	pclose(logger);



	/* Modifying logs.json file. */

	logger = fopen(largeBuff, "r+");

	if (logger==NULL) {printf("ERROR: Some user interruption to file mutex!\n\n"); return;}

	fseek(logger, -6, SEEK_END);
	c = fgetc(logger);

	if (c=='[') {fputs("\n\t\t", logger);}
	else if (c=='}') {fputs(",\n\n\t\t", logger);}
	else {printf("ERROR: Log file is corrupted!\n\n"); return;}


	newline_remover(command);

	memset(largeBuff, 0, sizeof(largeBuff));

	snprintf(
		largeBuff, sizeof(largeBuff),
		"{\n\t\t\t\"serial\": %d,\n\t\t\t\"time\": \"%s\",\n\t\t\t\"location\": \"%s\",\n\t\t\t\"author\": \"%s\",\n\t\t\t\"command\": \"%s\"\n\t\t}\n\t]\n}",
		logs, time, loc, username, command
	);

	fputs(largeBuff, logger);


	fclose(logger);
}





/* Fetches latitude & longitude. */

void getLocation()
{
	FILE *fetcher = NULL;


	printf("STAT: Fetching location...");					// Why is it not displayed before fetch?

	fetcher = popen("curl -s ipinfo.io/loc", "r");			// -s stands for "silent mode".
	fgets(loc, sizeof(loc), fetcher); newline_remover(loc);
	pclose(fetcher);

	printf("(FETCHED)\n");
}



/* Copyright (C) under Apache 2.0, Gourav Kumar Mallick */