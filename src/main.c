#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buff = NULL;
    size_t size = 0;

    printf("ash$ ");
    while((getline(&buff, &size, stdin)) != -1) {
        printf("%s", buff);

        if(strcmp(buff, "exit\n") == 0) {
            break;
        }

        printf("ash$ ");
    }

    free(buff);
}
