#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"

// the amount of commands(1 for initial testing).
int const COMMAND_COUNT = 3;

// the max amount of arguments supplied by the user.
int const MAX_ARGUMENT_COUNT = 4;

// max input from the user.
int const MAX_INPUT = 255;

// builds the command array.
void buildCommands(char* commandHolder[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1], 
					int actualArgCount[COMMAND_COUNT]) {
	
	// add 2 for '\n' and '\O'.
	char userInput[MAX_INPUT + 2];
	char *token;

	int commandNumber;
	for (commandNumber = 0; commandNumber < COMMAND_COUNT; commandNumber++) {
		int argumentNumber = 0;
		
		printf("mash-%d>", commandNumber + 1);
		fgets(userInput, MAX_INPUT + 1, stdin);
		userInput[strlen(userInput) - 1] = '\0';
		token = strtok(userInput, " ");

		do {
			commandHolder[commandNumber][argumentNumber] = strdup(token);
			token = strtok(NULL, " ");
			argumentNumber++;
		} while(token != NULL);

		actualArgCount[commandNumber] = argumentNumber;
		commandHolder[commandNumber][argumentNumber] = NULL;
	}
}

// gets the file path from the user.
void getFilePath(char fileHolder[MAX_ARGUMENT_COUNT + 2]) {

	printf("file>");
	fgets(fileHolder, MAX_INPUT + 1, stdin);
	fileHolder[strlen(fileHolder) - 1] = '\0';
}

// frees allocated memory.
void freeCommandMemory(char* commandHolder[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1],
						int actualArgCount[COMMAND_COUNT]) {
	
	int i;
	int j;
	for (i = 0; i < COMMAND_COUNT; i++) {
		for (j = 0; j < actualArgCount[i]; j++) {
			free(commandHolder[i][j]);
		}
	}
}

// main entry of the Mash shell (command line not used.
int main(int argc, char *argv[]) {

	// 2d array to hold the commands. 2nd dimension adds 1 to add room for 'NULL'.
	char* commands[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1];
	int actualArgCount[COMMAND_COUNT];

	// add 2 for '\n' and '\O'.
	char filePath[MAX_ARGUMENT_COUNT + 2];
	
	// function calls to populate arrays with user input
	buildCommands(commands, actualArgCount);
	getFilePath(filePath);

	/* forks, execs, and waits here, possibly their own function(s).
	
	Here is an example of execvp for syntax. commands[0][0] is the start
	location of the first command. commands[0] holds the entirety of the
	first command. There are 3 commands total.
	
	execvp(commands[0][0], commands[0]);
	*/
	freeCommandMemory(commands, actualArgCount);
}