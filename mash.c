#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"

#define COMMAND_COUNT = 3;
#define MAX_ARGUMENT_COUNT = 5;
#define MAX_INPUT = 255;


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

/*

Garbage function at the moment
int countWords(char* theString){
	int i, count;

	count = 0;
	i = 1;
	while(theString[i++] != NULL){
		if(theString[i] == ' ' && theString[i - 1] != ' '){
			count++;
		}
	}
	return count;
}
*/

// main entry of the Mash shell (command line not used.
int main(int argc, char *argv[]) {

	// 2d array to hold the commands. 2nd dimension adds 1 to add room for 'NULL'.
	char* commands[COMMAND_COUNT][MAX_ARGUMENT_COUNT + 1];
	int p1, p2, p3,p1Status, p2Status, p3Status, actualArgCount[COMMAND_COUNT];
	

	// add 2 for '\n' and '\O'.
	char filePath[MAX_ARGUMENT_COUNT + 2];
	
	// function calls to populate arrays with user input
	buildCommands(commands, actualArgCount);
	getFilePath(filePath);
	addFileToCommands(commands, filePath, actualArgCount);
	runShell(commands);
/*
	p1 = fork();
	if(p1 == 0){
		//child 1
		execvp(commands[0][0], commands[0]);
	}
	if(p1 > 0){
		p2 = fork();
		if(p2 == 0){
			//child 2
			execvp(commands[1][0], commands[1]);
		}
		if(p2 > 0){
			p3 = fork();
			if(p3 == 0){
				//child 3
				execvp(commands[2][0], commands[2]);
			}
			if(p3 > 0){
				//parent
				//Wait for children to finish
				waitpid(p1, &p1Status, 0);
				waitpid(p2, &p2Status, 0);
				waitpid(p3, &p3Status, 0);
				fprintf(stdout, "children: %d %d %d\n", p1, p2, p3);
			}
		}
	}
*/

	freeCommandMemory(commands, actualArgCount);
}


























































/*
// forks and executes three processes. (My practice at completing the assignment.
//										Use as a reference if you cannot figure
//										something out or don't). :)
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