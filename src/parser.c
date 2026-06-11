#include <stdlib.h>
#include <string.h>

char **parse(char *line) {
    line[strcspn(line, "\n")] = '\0';

    int size = 5;
    int argc = 0;
    char **argv = malloc(size * sizeof(char*));

    char *token = strtok(line, " ");

    if(token == NULL) {
        return NULL;
    }

    while(token != NULL) {
        if(argc >= size - 1) {
            size *= 2;
            argv = realloc(argv, size * sizeof(char*));
        }

        argv[argc++] = token; 
        
        token = strtok(NULL, " ");
    }

    argv[argc++] = NULL; 

    return argv;
}
