#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *ls_argv[3];

    ls_argv[0] = "ls";
    ls_argv[1] = "-al";
    ls_argv[2] = NULL;

    execv("/bin/ls", ls_argv);
    exit(EXIT_FAILURE);

    return 0;
}
