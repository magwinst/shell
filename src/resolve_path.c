#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/resolve_path.h"

char* resolve_path(char* command) {
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

