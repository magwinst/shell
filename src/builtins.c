#include <unistd.h>
#include <stdio.h>

#include "../include/builtins.h"

int msh_cd(char** args) {
    if (!args[1])
        fprintf(stderr, "error: expected argument to destination path");
    if (chdir(args[1]))
        perror("error: cd failed\n");
    return 1;
}

int msh_pwd(char** args) {
    char buffer[4096];
    getcwd(buffer, sizeof(buffer));
    printf("%s\n", buffer);
    return 1;
}

int msh_help(char** args) {
    printf("\nWelcome to msh (Matteo's shell)!\n\n");
    printf("msh supports the following: \n");
    printf("\n\n");
    printf("*** Functionality ***\n\n");
    printf("Command execution: shell will resolve path of any command specified in $PATH variable.\n");
    printf("I/O redirection: file input/output redirection.\n");
    printf("Piping: chaining of commands through connection of standard output of first command to standard input of second command.\n");
    printf("Background processes: run commands in the background.\n\n");

    return 1;
}

int msh_exit(char** args) {
    return 0;
}

int msh_wait(char** args) {
    return 1;
}

Command builtin_commands[] = {
    {"cd", &msh_cd},
    {"pwd", &msh_pwd},
    {"help", &msh_help},
    {"exit", &msh_exit},
    {"wait", &msh_wait}
};

int num_builtin_commands() {
    return sizeof(builtin_commands) / sizeof(Command);
}


