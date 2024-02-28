#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/resolve_path.h"
#include "../include/run_program.h"

int run_program(char** args) {
    char* path = resolve_path(args[0]);
    if (!path) {
        printf("Command not found, update PATH with program binary\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        execv(path, args);
        perror("execv failed\n");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else 
            exit(EXIT_FAILURE);
    } else {
        perror("fork failed\n");
        exit(EXIT_FAILURE);
    }
    
    free(path);

    return 1;
}
