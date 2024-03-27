#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/parsing.h"

/*
    Function to break up a line (or any arbitrary string) into a memory allocated
    tokenized array of strings separated by the given delimiter or set of 
    delimiters (see strtok_r for more information about delim parameter). 
    
    Note: The array will be memory allocated, therefore they must be freed later. 
    
    Warning: LINE MUST BE MEMORY ALLOCATED!

    @param line : An arbitrary string
    @param delim : The delimiter or set of delimiters for separating 
        the line (see strtok_r for more information)
    
    @return array : array of pointers to strings in line.
*/
char** parse_helper(char* line, const char delim[]){

    char** array = (char**)malloc(sizeof(char*));
    *array=NULL;
    int n = 0;

    char* buf = strtok(line,delim);

    if (buf == NULL){
        free(array);
        array=NULL;
        return array;
    }

    while (buf != NULL){
        array = (char**)realloc(array,(n+2)*sizeof(char*));

        if(array==NULL){
            free(array);
            array=NULL;
            return array;
        }

        array[n]=buf;
        n++;
        array[n]=NULL;

        buf = strtok(NULL,delim);
    }

    return array;
}

// part c, added new parse 

char*** parse(char** commands) {
    int num_commands = 0;
    while (commands[num_commands]) {
        num_commands++;
    }
    char*** args = malloc((num_commands+1) * sizeof(char**));

    if (!args) {
        perror("error: malloc failed when parsing command arguments");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_commands; ++i) {
        args[i] = parse_helper(commands[i], " ");
    }

    args[num_commands] = NULL;
    return args;
}



/*
  Demonstration main()

int main(){
    char _line[1000] = "a line of text\n";
    char *line = strdup(_line);
    char **array = parse(line," \n");

    if (array == NULL) {
        exit(1);
    }

    int i = 0;
    while (array[i]!=NULL) {
        printf("%s\n",array[i++]);
    }

    free(array);
    free(line);
}
*/
