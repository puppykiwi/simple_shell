#include "mwendwa.h"

// return shell input into the buffer
char* getInput(bool prompt,char* inputBuffer){
    
    printf(MAGENTA "\n joSH > "RESET);
    fgets(inputBuffer, DEFAULT_BUFFER_SIZE, stdin);
    
    //else{printf("You entered: %s", inputBuffer);} // for testing purposes
    if(inputBuffer != NULL){return inputBuffer;}
    else{printf(RED"Error: inputBuffer is NULL\n"RESET); return NULL;}
}

// parse the input buffer into args[]
void parseInput(char* inputBuffer, char* args[]) {
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

    char* token = strtok(inputBuffer, " ");
    int numArgs = 0;

    while (token != NULL && numArgs < MAX_NUM_ARGS - 1) {
        // Allocate memory for each argument
        args[numArgs] = malloc(MAX_ARG_LEN * sizeof(char));
        strncpy(args[numArgs], token, MAX_ARG_LEN - 1);
        args[numArgs][MAX_ARG_LEN - 1] = '\0';

        token = strtok(NULL, " ");
        numArgs++;
    }
    args[numArgs] = NULL;
    
    if (args == NULL) {
        printf(RED"Error: args is NULL\n"RESET);
    }
}

// execute the command in args[]
void execute(char* args[], CommandHistory history){
    
    if (strncmp(args[0],"exit",4) == 0){
            prompt = false;
            exit(1);
        }

    else if(strncmp(args[0],"history",7) == 0 || strncmp(args[0],"hst",3) == 0){
        printf("Command history: \n");
        printCommandHistory(&history);
    }

    int pid = fork();
    if (pid < 0){fprintf(stderr,RED"ERROR: Fork failed\n"RESET);}

    else if (pid == 0){
        //printf("** Child process created **\n"); // for testing purposes

        if(strncmp(args[0],"cd", 2) == 0){
            if (args[1] == NULL){fprintf(stderr,RED"ERROR: Dir not found\n"RESET);}
            else if(chdir(args[1]) != 0){fprintf(stderr,RED"ERROR: chdir failed\n"RESET);}
            printf("Directory changed to %s\n", args[1]);
        }

        else if(strncmp(args[0],"clear",5) == 0){
            clearScreen();
        }

        else{
            
            if (execvp(args[0], args) < 0){
                validCommand = false;
                fprintf(stderr,RED"ERROR: execvp failed\n"RESET);
                exit(1);
                }

            else{
                validCommand = true;
                }
        }
    }

    else {
        //printf("** Parent process waiting for completion **\n"); // for testing purposes
        wait(NULL);
        //printf("** Child process completed **\n"); // for testing purposes
    }
}

int main(int argc, char* argv[]){
    printf(CYAN"Welcome to joSH!\n"RESET); //banner

    inputBuffer = (char*)malloc(sizeof(char) * DEFAULT_BUFFER_SIZE);
    CommandHistory history;
    initCommandHistory(&history);

    while (prompt){
        inputBuffer = getInput(prompt, inputBuffer); // return input into the buffer
        printf("%s\n", inputBuffer); // for testing purposes

        parseInput(inputBuffer, args); // parse the input buffer into args[]
        
        for (int i=0; args[i] != NULL; i++)
            printf("%s\n", args[i]); // for testing purposes
        
        execute(args, history);
        if (validCommand = true){for (int i=0; args[i] != NULL; i++){addCommand(&history, args[i]);}}
    }
    

    cleanup();
    return 0;
}