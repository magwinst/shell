#include <string.h>

#include "../include/builtins.h"
#include "../include/execute.h"
#include "../include/run_program.h"
#include "../include/redirection.h"

// part b, added to execute function

int execute(char** args) {
    if (!args[0])
        return 1;

    for (int i = 0; i < num_builtin_commands(); ++i) {
        if (strcmp(args[0], builtin_commands[i].name) == 0)
            return builtin_commands[i].function(args);
    }

    for (int i = 0; args[i] != NULL; ++i) {
        if (strcmp(args[i], "<")) {
                execute_input_redirection(args[i-1], args, i+1);
                return 1;
        }
        if (strcmp(args[i], ">")) {
                execute_output_redirection(args[i+1], args, i-1);       
                return 1;
        }
    }
    
    run_program(args);   

    return 1;
}
