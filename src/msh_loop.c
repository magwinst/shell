#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/helpers.h"
#include "../include/execute.h"
#include "../include/msh_loop.h"

// part b, fixed parsing to include spaces not new line

void msh_loop() {
    
    char buffer[4096];
    char** array;
    int status;

    do {
        printf("msh-1.0$ ");
        fgets(buffer, sizeof(buffer), stdin);
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n')
                buffer[len-1] = '\0';
        array = parse(buffer, " ");

        if (!array)
            continue;

        status = execute(array);       
        free(array);

    } while (status);

}
