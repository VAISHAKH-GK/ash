#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    char *buff = NULL;
    size_t size = 0;

    printf("ash$ ");
    while((getline(&buff, &size, stdin)) != -1) {
        if(strcmp(buff, "exit\n") == 0) {
            exit(0);
        }

        buff[strcspn(buff, "\n")] = '\0';

        pid_t pid = fork();
        int status;

        if(pid == -1) {
            perror("Fork failed");
            exit(1);
        }

        if(pid == 0) {
            char *exec_argv[] = {buff, NULL};
            execvp(buff, exec_argv);

            perror(buff);
            exit(1);
        }

        pid_t wpid = waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            printf("Killed by signal: %d\n", WTERMSIG(status));
        }

        printf("ash$ ");
    }

    free(buff);
}
