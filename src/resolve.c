#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/resolve.h"

char* resolve_path(char* command) {
    if (command[0] == '/' || (command[0] == '.' && command[1] == '/')) {
        if (!access(command, X_OK))
            return command;
    }
   
    char* path = getenv("PATH");
    char* pathcpy = strdup(path);
    char* token = strtok(pathcpy, ":");

    while (token != NULL) {
        char* fullpath = malloc(strlen(token) + strlen(command)+2);
        sprintf(fullpath, "%s/%s", token, command);
        if (!access(fullpath, X_OK)) {
            free(pathcpy);
            return fullpath;
        } else {
            free(fullpath);
            token = strtok(NULL, ":");
        }
    }

    free(pathcpy);
    return NULL;
}

char** resolve_args(char** args) {
    int num_args = 0;
    while (args[num_args]) {
        num_args++;
    }
    char** new_args = malloc((num_args+1) * sizeof(char*));
    
    int i = 0;
    while (args[i] && (strcmp(args[i], "<")) && (strcmp(args[i], ">"))) {
        new_args[i] = args[i];
        i++;
    }

    new_args[i] = NULL;

    return new_args;
    
}

