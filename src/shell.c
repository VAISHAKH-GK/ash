#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void shell_loop() {
    char *line = NULL;
    size_t size = 0;

    printf("ash$ ");
    while((getline(&line, &size, stdin)) != -1) {
        if(strcmp(line, "exit\n") == 0) {
            exit(0);
        }

        line[strcspn(line, "\n")] = '\0';

        pid_t pid = fork();
        int status;

        if(pid == -1) {
            perror("Fork failed");
            exit(1);
        }

        if(pid == 0) {
            char *exec_argv[] = {line, NULL};
            execvp(line, exec_argv);

            perror(line);
            exit(1);
        }

        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            printf("Killed by signal: %d\n", WTERMSIG(status));
        }

        printf("ash$ ");
    }

    free(line);
}
