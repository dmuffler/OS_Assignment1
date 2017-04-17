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

// builds the command array (fixed)!
void buildCommands(char* commandHolder[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1], 
					int actualArgCount[COMMAND_COUNT]) {
	
	char string[MAX_INPUT + 1];
	char *token;

	int commandNumber;
	for (commandNumber = 0; commandNumber < COMMAND_COUNT; commandNumber++) {
		int argumentNumber = 0;
		
		printf("mash-%d>", commandNumber + 1);
		fgets(string, MAX_INPUT, stdin);
		string[strlen(string) - 1] = '\0';
		token = strtok(string, " ");

		do {
			commandHolder[commandNumber][argumentNumber] = strdup(token);
			token = strtok(NULL, " ");
			argumentNumber++;
		} while(token != NULL);

		actualArgCount[commandNumber] = argumentNumber;
		commandHolder[commandNumber][argumentNumber] = NULL;
	}
}

// gets the file path from the user(unfinished).
void getFilePath(char* fileHolder[1]) {

}

// frees allocated memory.
void freeFileMemory(char* fileHolder[1]) {

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

int main(int argc, char *argv[]) {

	// 2d array to hold the commands. 2nd dimension a to save room for NULL terminator.
	char* commands[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1];
	int actualArgCount[COMMAND_COUNT];
	char* filePath[1];
	
	buildCommands(commands, actualArgCount);
	getFilePath(filePath);

	// forks, execs, and waits here.

	freeCommandMemory(commands, actualArgCount);
}