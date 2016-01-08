#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    /* write(STDERR_FILENO, "a", 1); */
    /* fprintf(stderr, "%c", 'b'); */
    /* write(STDERR_FILENO, "c", 1); */
    write(STDOUT_FILENO, "a", 1);
    fprintf(stdout, "%c", 'b');
    write(STDOUT_FILENO, "c", 1);

    return 0;
}
