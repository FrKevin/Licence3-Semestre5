#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    char tampon[10];
    int lus;

    while((lus = read(STDIN_FILENO, tampon, 10)) > 0) {
        assert(write(STDOUT_FILENO, tampon, lus) == lus);
    }

    if(lus == -1) {
        perror("lecture");
        exit(EXIT_FAILURE);
    }

    return 0;
}
