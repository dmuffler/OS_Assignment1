/* 	Authors: Donald Muffler, Josiah Hopkins
	Date: 4/27/17
*/


#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"

// amount of commands in the shell.
static const int COMMAND_COUNT = 3;

// the arg count per command.
static const int MAX_ARGUMENT_COUNT = 5;

// max user input size for commands/arguments.
static const int MAX_INPUT = 255;

// the first command.
static const int COMMAND_ONE = 0;

// the second command.
static const int COMMAND_TWO = 1;

// the third command.
static const int COMMAND_THREE = 2;

// the start of command arguments.
static const int ARGUMENT_START = 0;


// builds the command array.
void buildCommands(char* commandHolder[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1], 
					int actualArgCount[COMMAND_COUNT]) {
	
	// add 2 for '\n' and '\O'.
	char userInput[MAX_INPUT + 2];
	char *token;

	int command;
	for (command = 0; command < COMMAND_COUNT; command++) {
		int argument = 0;
		
		printf("mash-%d>", command + 1);
		fgets(userInput, MAX_INPUT + 1, stdin);
		userInput[strlen(userInput) - 1] = '\0';
		token = strtok(userInput, " ");

		do {
			
			commandHolder[command][argument] = strdup(token);
			token = strtok(NULL, " ");
			argument++;
		
		} while(token != NULL);

		actualArgCount[command] = argument;
		commandHolder[command][argument] = NULL;
	}
}

// gets the file path from the user.
void getFilePath(char fileHolder[MAX_ARGUMENT_COUNT + 2]) {

	printf("file>");
	if(fgets(fileHolder, MAX_INPUT + 1, stdin)){
		fileHolder[strlen(fileHolder) - 1] = '\0';
	} else {
		fileHolder = NULL;
	}
}

// adds the file path to the array of commands
void addFileToCommands(char* commandHolder[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1],
						char fileHolder[MAX_ARGUMENT_COUNT + 2], 
						int actualArgCount[COMMAND_COUNT]) {
	
	int command;
	for (command = 0; command < COMMAND_COUNT; command++) {
		
		commandHolder[command][actualArgCount[command]] = strdup(fileHolder);
		actualArgCount[command] = actualArgCount[command] + 1;
		commandHolder[command][actualArgCount[command]] = NULL;
	
	}
}

// the shell that branches and runs 3 commands in parallel.
void runShell(char* commandHolder[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1]) {
	  
	// container to hold pid in order of completion.
	int processes[COMMAND_COUNT], processCount = 0, processOne, processTwo, processThree;

	processOne = fork();

	// child one
	if (processOne == 0) {
		int check = execvp(commandHolder[COMMAND_ONE][ARGUMENT_START],
							commandHolder[COMMAND_ONE]);
		printf("[SHELL 1] STATUS CODE=%d\n", check);
		exit(EXIT_FAILURE);
	}

	if (processOne > 0) {

		processTwo = fork();

		// child two
		if (processTwo == 0) {
			int check = execvp(commandHolder[COMMAND_TWO][ARGUMENT_START],
								commandHolder[COMMAND_TWO]);
			printf("[SHELL 2] STATUS CODE=%d\n", check);
			exit(EXIT_FAILURE);
		}
		
		if (processTwo > 0) {

			processThree = fork();

			// child three
			if (processThree == 0) {
				int check = execvp(commandHolder[COMMAND_THREE][ARGUMENT_START],
									commandHolder[COMMAND_THREE]);
				printf("[SHELL 3] STATUS CODE=%d\n", check);
				exit(EXIT_FAILURE);
			}
			
			if (processThree > 0) {
				processes[processCount++] = wait(NULL);
				processes[processCount++] = wait(NULL);
				processes[processCount] = wait(NULL);
			}
		}
	}
	printf("Done waiting on children: %d %d %d\n", processes[0], processes[1], processes[2]);
}


// frees allocated memory.
void freeCommandMemory(char* commandHolder[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1],
						int actualArgCount[COMMAND_COUNT]) {
	
	int command;
	int argument;
	for (command = 0; command < COMMAND_COUNT; command++) {
	
		for (argument = 0; argument < actualArgCount[command]; argument++) {
			free(commandHolder[command][argument]);
		}
	
	}
}

// main entry of the Mash shell (command line not used.
int main(int argc, char *argv[]) {

	// 2d array to hold the commands. 2nd dimension adds 1 to add room for 'NULL'.
	char* commands[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1];

	// holds the amount of arguments per command.
	int actualArgCount[COMMAND_COUNT];	

	// add 2 for '\n' and '\O'.
	char filePath[MAX_ARGUMENT_COUNT + 2];
	
	// function calls to populate arrays with user input.
	buildCommands(commands, actualArgCount);
	getFilePath(filePath);
	addFileToCommands(commands, filePath, actualArgCount);

	runShell(commands);

	freeCommandMemory(commands, actualArgCount);

	return 0;
}