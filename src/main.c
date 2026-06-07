#include <stdio.h>

int main() {
    char *buff;
    long unsigned int size = 0;

    printf("ash$ ");
    getline(&buff, &size, stdin);

    printf("%s", buff);
}
