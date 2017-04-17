#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"

// the amount of commands(1 for initial testing).
int const COMMAND_COUNT = 1;


int const MAX_INPUT = 255;

// builds the command array (fixed)!
void buildCommands(char* commandHolder[3][5]) {
	char string[MAX_INPUT + 1];
	char *token;

	int commandNumber;
	int argumentCount = 0;
	for (commandNumber = 0; commandNumber < COMMAND_COUNT; commandNumber++) {
		
		fgets(string, MAX_INPUT, stdin);
		string[strlen(string) - 1] = '\0';
		token = strtok(string, " ");

		do {
			commandHolder[commandNumber][argumentCount] = strdup(token);
			token = strtok(NULL, " ");
			argumentCount++;
		} while(token != NULL);
		
		commandHolder[commandNumber][argumentCount] = NULL;
	}
}

int main(int argc, char *argv[]) {

	char* commands[3][5];
	
	buildCommands(commands);

	execvp(commands[0][0], (char * const*) commands[0]);

	return 0;
}