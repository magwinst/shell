#include <string.h>
#include <stdio.h>

#include "../include/builtins.h"
#include "../include/execute.h"
#include "../include/run_program.h"
#include "../include/redirection.h"

int execute(char** args, int bg) {
    if (!args[0])
        return 1;

    for (int i = 0; i < num_builtin_commands(); ++i) {
        if (strcmp(args[0], builtin_commands[i].name) == 0)
            return builtin_commands[i].function(args);
    }

    int i = 0;
    int redir_called = 0;
    while (args[i]) {
        if (!strcmp(args[i], "<")) {
            execute_input_redirection(args[i+1], args);
            redir_called = 1;
            break;
        } else if (!strcmp(args[i], ">")) {
            execute_output_redirection(args[i+1], args);
            redir_called = 1;
            break;
        }
        i++;
    }

    if (!redir_called)
        run_program(args, bg);   

    return 1;
}
