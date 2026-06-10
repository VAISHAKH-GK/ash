#include <string.h>

int parse(char *line) {
    line[strcspn(line, "\n")] = '\0';

    return 1;
}
