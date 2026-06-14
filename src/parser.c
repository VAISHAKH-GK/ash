#include <stdlib.h>
#include <string.h>

char **parse(char *line) {
    line[strcspn(line, "\n")] = '\0';

    int size = 10;
    int token_size = 100;
    int argc = 0;
    int pos = 0;

    char **argv = malloc(size * sizeof(char*));
    char *token = malloc(token_size * sizeof(char));

    char *c = line;
    int in_quotes = 0;

    while(*c != '\0') {
        if (in_quotes != 0 ) {
            if(in_quotes == *c) {
                in_quotes = 0;
                c++;
                continue;
            }

            if(pos >= token_size - 1) {
                token_size *= 2;
                token = realloc(token, token_size * sizeof(char));
            }

            token[pos++] = *c;
            c++;
            continue;
        }

        if(*c == '\'' || *c == '\"') {
            in_quotes = *c;
            c++;
            continue;
        }

        if(*c == ' ') {
            if(pos > 0) {
                token[pos++] = '\0';

                if(argc >= size - 1) {
                    size *= 2;
                    argv = realloc(argv, size * sizeof(char*));
                }

                argv[argc++] = strdup(token);
                pos = 0;
            }

            c++;
            continue;
        }

        if(pos >= token_size - 1) {
            token_size *= 2;
            token = realloc(token, token_size * sizeof(char));
        }

        token[pos++] = *c;
        c++;
    }

    if (pos > 0) {
        token[pos] = '\0';
        argv[argc++] = strdup(token);
    }

    argv[argc++] = NULL; 
    free(token);

    return argv;
}
