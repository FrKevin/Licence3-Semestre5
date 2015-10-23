/* mshell - a job manager */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void unix_error(char *msg) {
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(EXIT_FAILURE);
}
