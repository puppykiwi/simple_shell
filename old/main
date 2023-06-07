#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

bool prompt = true;
char *input;

int main(int argc, char **argv){
    input = malloc(sizeof(char)*100);
    if (input == NULL){printf("Error allocating memory\n");exit(1);}

    while(prompt){
        printf("\nmyshell> ");
        scanf("%s", input);
        if (strncmp("exit",input,4) == 0){prompt = 0;}
    }
    printf("%s", input);
}