#include "../include/msh_loop.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/helpers.h"
#include "../include/execute.h"


// core shell loop (part A)

void msh_loop() {
    
    char buffer[4096];
    char** array;
    int status;

    do {
        printf("msh-1.0$ ");
        fgets(buffer, sizeof(buffer), stdin);
        array = parse(buffer, " \n");

        if (!array)
            exit(EXIT_FAILURE);

        status = execute(array);       
        free(array);

    } while (status);

}
