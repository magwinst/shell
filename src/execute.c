#include "../include/builtins.h"
#include "../include/execute.h"
#include <string.h>

// execute function, responsible for calling built-in commands or creating new processes (part A)

int execute(char** args) {
    if (!args[0])
        return 1;

    for (int i = 0; i < num_builtin_commands(); ++i) {
        if (strcmp(args[0], builtin_commands[i].name) == 0)
            return builtin_commands[i].function(args);
    }

    return 1;

}
