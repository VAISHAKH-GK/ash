#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <libgen.h>

int main(int argc, char **argv) {
    char *buff = NULL;
    size_t size = 0;

    printf("ash$ ");
    while((getline(&buff, &size, stdin)) != -1) {
        printf("%s", buff);

        if(strcmp(buff, "exit\n") == 0) {
            break;
        }

        buff[strcspn(buff, "\n")] = '\0';

        pid_t pid = fork();
        int status;

        if(pid == -1) {
            perror("Fork failed");
            exit(1);
        }

        if(pid == 0) {
            printf("Child process\n");

            char *program = basename(buff);
            char *exec_argv[] = {program, NULL};
            int status_code = execvp(buff, exec_argv);

            exit(0);
        }

        pid_t wpid = waitpid(pid, &status, 0);
        if(wpid != -1) {
            printf("Child pid - %d - status %d \n", wpid, WEXITSTATUS(status));
        }

        printf("ash$ ");
    }

    free(buff);
}
