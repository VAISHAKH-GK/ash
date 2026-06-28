#include <stdlib.h>
#include <string.h>

char **split_commands(char *input) {
    input[strcspn(input, "\n")] = '\0';

    int commands_count = 4;
    int command_length = 100;

    int count = 0;
    int pos = 0;

    char **commands = malloc(commands_count * sizeof(char*));
    char *line = malloc(command_length * sizeof(char));

    char *c = input;

    while(*c != '\0') {
        if((*c == '&' || *c == '|') && (*c == *(c+1))) {
            if(pos > 0) {
                line[pos]  = '\0';

                if(count >= commands_count - 2) {
                    commands_count *= 2;
                    commands = realloc(commands, commands_count * sizeof(char*));
                }

                commands[count++] = strdup(line);
                pos = 0;

                char op[3] = {*c, *c, '\0'};
                commands[count++] = strdup(op);
            }

            c+=2;
            continue;
        }

        if(*c == ';' || *c == '&') {
            if(pos > 0) {
                line[pos]  = '\0';

                if(count >= commands_count - 2) {
                    commands_count *= 2;
                    commands = realloc(commands, commands_count * sizeof(char*));
                }

                commands[count++] = strdup(line);
                pos = 0;

                char op[2] = {*c, '\0'};
                commands[count++] = strdup(op);
            }

            c++;
            continue;
        }

        if(pos >= command_length - 1) {
            command_length *= 2;
            line = realloc(line, command_length * sizeof(char));
        }


        line[pos++] = *c;
        c++;
    }

    if (pos > 0) {
        line[pos] = '\0';
        commands[count++] = strdup(line);
    }

    commands[count++] = NULL;
    free(line);

    return commands;
}

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
