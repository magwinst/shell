#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "../include/parsing.h"
#include "../include/piping.h"
#include "../include/execute.h"
#include "../include/msh_loop.h"

// part c, bg processes

void msh_loop() {
    
    char buffer[4096];
    char** args;
    char*** commands;
    int status;


    do {
        printf("msh-1.0$ ");
        fgets(buffer, sizeof(buffer), stdin);
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';

        char** pipe_segments = parse_helper(buffer, "|");

        if (pipe_segments[1]) { 
            commands = parse(pipe_segments);
            status = execute_piping(commands);

            free(pipe_segments);
            for (int i = 0; commands[i] != NULL; ++i)
                free(commands[i]);
            free(commands);

        } else {
            args = parse_helper(buffer, " ");
            if (!args)
                continue;

            int bg = 0;
            int num_args = 0; 

            while (args[num_args]) 
                num_args++;

            if (num_args > 0 && (!strcmp(args[num_args - 1], "&"))) {
                bg = 1;
                free(args[num_args - 1]);
                args[num_args - 1] = NULL; 
            }

            status = execute(args, bg);
            free(args);
        }

    } while (status);

}
