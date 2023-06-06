#ifndef MWENDWA_H
#define MWENDWA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DEFAULT_BUFFER_SIZE 1000
#define MAX_NUM_ARGS 20
#define MAX_ARG_LEN 20
#define MAX_HISTORY_SIZE 10
#define MAX_COMMAND_LENGTH 100
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

typedef struct {
    char commands[MAX_HISTORY_SIZE][MAX_COMMAND_LENGTH];
    int start;
    int count;
} CommandHistory;

// global variables
char* inputBuffer; 
bool prompt = true;
char* args[MAX_NUM_ARGS];
bool validCommand = false;

// function prototypes
char* getInput(bool prompt,char* inputBuffer);
void parseInput(char* inputBuffer, char* args[]);
void execute(char* args[], CommandHistory history);
void cleanup(void);

//free memory
void cleanup(void){
    free(inputBuffer);
    for (int i = 0; i < MAX_NUM_ARGS; i++){
        free(args[i]);
    }
}

//clear the screen
void clearScreen() {
    printf("\033[2J\033[H"); // ANSI escape code
}

// COMMAND HISTORY
void initCommandHistory(CommandHistory* history) {
    memset(history->commands, 0, sizeof(history->commands));
    history->start = 0;
    history->count = 0;
}

void addCommand(CommandHistory* history, const char* command) {
    int index = (history->start + history->count) % MAX_HISTORY_SIZE;
    strncpy(history->commands[index], command, MAX_COMMAND_LENGTH - 1);
    history->commands[index][MAX_COMMAND_LENGTH - 1] = '\0';
    
    if (history->count < MAX_HISTORY_SIZE) {
        history->count++;
    } else {
        history->start = (history->start + 1) % MAX_HISTORY_SIZE;
    }
}

void printCommandHistory(const CommandHistory* history) {
    int index = history->start;
    for (int i = 0; i < history->count; i++) {
        printf("%s\n", history->commands[index]);
        index = (index + 1) % MAX_HISTORY_SIZE;
    }
}



#endif