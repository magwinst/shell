#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> 

#include "../include/redirection.h"
#include "../include/resolve.h"

int execute_output_redirection(char *output_file, char **args)
{
    char* path = resolve_path(args[0]);
    char** new_args = resolve_args(args);

    pid_t pid = fork();

    if (pid == 0) {
        if (output_file) {
            int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd == -1) {
                perror("error: can't open output file\n");
                return 1;
            }

            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        execv(path, new_args);
        perror("error: execv");
        exit(EXIT_FAILURE);

    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            free(new_args);
            return WEXITSTATUS(status);
        } else {
            free(new_args);
            exit(EXIT_FAILURE);
        }
    } else {
        perror("error: fork");
        free(new_args);
        return 1;
    }

    free(path);
    return 1;
}

int execute_input_redirection(char* input_file, char** args) {

    char* path = resolve_path(args[0]);
    char** new_args = resolve_args(args);

    pid_t pid = fork();

    if (pid == 0) {
        if (input_file) {
            int input_fd = open(input_file, O_RDONLY);
            if (input_fd == -1) {
                perror("error: Can't open input file\n");
                return 1;
            }
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        execv(path, new_args);
        perror("error: execv");

    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            free(new_args);
            return WEXITSTATUS(status);
        }
        else {
            free(new_args);
            exit(EXIT_FAILURE);
        }
    } else {
        perror("error: fork");
        free(new_args);
        return 1;
    }
    
    free(path);
    return 1;
}



