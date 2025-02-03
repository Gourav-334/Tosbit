#include "../include/shell_piping.h"










/* Variables */

char loc[LOC_MAX_LENGTH] = {0};










/* Records log. */

void recordLog(char username[], char command[])
{
	/* Declarations. */

	FILE *logger = NULL;

	char c = '$';
	char time[30] = {0}, tempBuff[1025] = {0};



	/* Storing time */

	logger = popen("date -u", "r");
	fgets(time, sizeof(time), logger); newline_remover(time);
	pclose(logger);



	/* Modifying logs.json file. */

	logger = fopen("data/logs.json", "r+");

	if (logger==NULL) {printf("ERROR: logs.json file not found!\n\n"); return;}

	fseek(logger, -6, SEEK_END);
	c = fgetc(logger);

	if (c=='[') {fputs("\n\t\t", logger);}
	else if (c=='}') {fputs(",\n\n\t\t", logger);}
	else {printf("ERROR: logs.json is corrupted!\n\n"); return;}


	newline_remover(command);

	snprintf(
		tempBuff, sizeof(tempBuff),
		"{\n\t\t\t\"time\": \"%s\",\n\t\t\t\"location\": \"%s\",\n\t\t\t\"author\": \"%s\",\n\t\t\t\"command\": \"%s\"\n\t\t}\n\t]\n}",
		time, loc, username, command
	);

	fputs(tempBuff, logger);


	fclose(logger);
}





/* Fetches latitude & longitude. */

void getLocation()
{
	FILE *fetcher = NULL;


	printf("STAT: Fetching location...");					// Why is it not displayed before fetch?

	fetcher = popen("curl -s ipinfo.io/loc", "r");				// -s stands for "silent mode".
	fgets(loc, sizeof(loc), fetcher); newline_remover(loc);
	pclose(fetcher);

	printf("(FETCHED)\n\n");
}
