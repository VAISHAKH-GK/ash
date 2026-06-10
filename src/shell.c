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
        if(strcmp(line, "exit\n") == 0) {
            exit(0);
        }

        parse(line);

        execute(line);

        printf("ash$ ");
    }

    free(line);
}
