#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

// Part A

// built-in command function pointer type
typedef int (*cmd_function)(char** args);

// struct that contains names of built-in functions and pointer to built-in command functions
typedef struct {
    char* name;
    cmd_function function;
} Command;

// built-in commands
int msh_cd(char** args);
int msh_pwd(char** args);
int msh_help(char** args);
int msh_exit(char** args);

// externally defined array of Command structs
extern Command builtin_commands[];

// externally defined size function
extern int num_builtin_commands();

#endif
