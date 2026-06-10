#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute(char *line) {
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
}
