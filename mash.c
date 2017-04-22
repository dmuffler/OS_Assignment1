#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"

// the amount of commands(1 for initial testing).
int const COMMAND_COUNT = 3;

// the max amount of arguments supplied by the user.
int const MAX_ARGUMENT_COUNT = 5;

// max input from the user.
int const MAX_INPUT = 255;

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
	fgets(fileHolder, MAX_INPUT + 1, stdin);
	fileHolder[strlen(fileHolder) - 1] = '\0';
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
	int actualArgCount[COMMAND_COUNT];

	// add 2 for '\n' and '\O'.
	char filePath[MAX_ARGUMENT_COUNT + 2];
	
	// function calls to populate arrays with user input
	buildCommands(commands, actualArgCount);
	getFilePath(filePath);
	addFileToCommands(commands, filePath, actualArgCount);

	/* forks, execs, and waits here, possibly their own function(s).
	
	Here is an example of execvp for syntax. commands[0][0] is the start
	location of the first command. commands[0] holds the entirety of the
	first command. There are 3 commands total.
	
	execvp(commands[0][0], commands[0]);
	*/

	freeCommandMemory(commands, actualArgCount);
}


























































/*
// forks and executes three processes. (My practice at completing the assignment.
										Use as a reference if you cannot figure
										something out or don't). :)
void runShell(char* commandHolder[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1]) {
	  
	// container to hold pid in order of completion.
	int processes[3];
	
	int processCount = 0;
	int statusOne;
	int statusTwo;
	int statusThree;



	int processOne = fork();

	if (processOne == 0) {
		execvp(commandHolder[PROCESS_ONE][ARGUMENT_START], commandHolder[PROCESS_ONE]);
	}

	if (processOne > 0) {

		int processTwo = fork();
		processes[processCount++] = wait(&statusOne);


		if (processTwo == 0) {
			execvp(commandHolder[PROCESS_TWO][ARGUMENT_START], commandHolder[PROCESS_TWO]);
		}
		
		if (processTwo > 0) {

			int processThree = fork();
			processes[processCount++] = wait(&statusTwo);

			if (processThree == 0) {
				execvp(commandHolder[PROCESS_THREE][ARGUMENT_START], commandHolder[PROCESS_THREE]);
			}
			
			if (processThree > 0) {
				processes[processCount++] = wait(&statusThree);
			}
		}

		if (WEXITSTATUS(statusOne)) {
			printf("[SHELL 1] STATUS CODE=-1\n");
		}

		if (WEXITSTATUS(statusTwo)) {
			printf("[SHELL 2] STATUS CODE=-1\n");
		}

		if (WEXITSTATUS(statusThree)) {
			printf("[SHELL 3] STATUS CODE=-1\n");
		}		
	}

	printf("Done waiting on children: %d %d %d\n", processes[0], processes[1], processes[2]);
}*/