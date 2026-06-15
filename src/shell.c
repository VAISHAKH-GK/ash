#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser.h>
#include <execute.h>

void shell_loop() {
    char *line = NULL;
    size_t size = 0;

    printf("ash$ ");
    while((getline(&line, &size, stdin)) != -1) {
        char **commands = split_commands(line);

        for(int i = 0; commands[i] != NULL; i++) {
            if(strcmp(commands[i], "exit") == 0) {
                exit(0);
            }

            if(strcmp(commands[i], ";") != 0) {
                char **argv = parse(commands[i]);
                if(argv != NULL) {
                    execute(argv);
                    free(argv);
                }
            }
        }

        printf("ash$ ");

        free(commands);

    }

    free(line);
}
