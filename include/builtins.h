#pragma once

typedef int (*cmd_function)(char** args);

typedef struct {
    char* name;
    cmd_function function;
} Command;

int msh_cd(char** args);
int msh_pwd(char** args);
int msh_help(char** args);
int msh_exit(char** args);

extern Command builtin_commands[];

int num_builtin_commands();
