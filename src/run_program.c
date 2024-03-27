#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/resolve.h"
#include "../include/run_program.h"

// part c, bg processes

int run_program(char** args, int bg) {
    char* path = resolve_path(args[0]);

    if (!path) {
        printf("error: command not found\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        execv(path, args);
        perror("execv failed\n");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        if (bg) {
            printf("[Running in background] PID: %d\n", pid);
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                return WEXITSTATUS(status);
            else {
                free(path);
                exit(EXIT_FAILURE);
            }    
        }
        
    } else {
        perror("fork failed\n");
        free(path);
        exit(EXIT_FAILURE);
    }
    
    free(path);

    return 1;
}
