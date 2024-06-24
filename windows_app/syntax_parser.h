#ifndef SYNTAX_PARSER_H
	#define SYNTAX_PARSER_H

#define COMMAND_LENGTH 256
#define STRING_MAX_LENGTH 33
#define MAX_STRINGS 9





// Variables & arrays

char command_buffer[STRING_MAX_LENGTH][MAX_STRINGS];



// Functions

void string_tokenizer(char command[COMMAND_LENGTH]);





#endif