#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser.h>
#include <execute.h>

void shell_loop() {
    char *line = NULL;
    size_t size = 0;

    int cmd_fail = 0;
    int stop = 0;

    printf("ash$ ");
    while((getline(&line, &size, stdin)) != -1) {
        cmd_fail = 0;
        stop = 0;

        char **commands = split_commands(line);

        for(int i = 0; commands[i] != NULL; i++) {
            if(strcmp(commands[i], "exit") == 0) {
                exit(0);
            }

            if(strcmp(commands[i], ";") == 0) {
                continue;
            }

            if(strcmp(commands[i], "&&") == 0) {
                stop = cmd_fail;
                continue;
            }

            if(strcmp(commands[i], "||") == 0) {
                stop = !cmd_fail;
                continue;
            }

            if(stop) {
                break;
            }

            char **argv = parse(commands[i]);
            if(argv != NULL) {
                if(commands[i+1] != NULL && strcmp(commands[i+1], "&") == 0) {
                    execute_bg(argv);
                    i++;
                } else {
                    cmd_fail = execute(argv);
                }

                for(int i = 0; argv[i] != NULL; i++) {
                    free(argv[i]);
                }

                free(argv);
            }
        }

        printf("ash$ ");

        for(int i = 0; commands[i] != NULL; i++) {
            free(commands[i]);
        }

        free(commands);

    }

    free(line);
}
