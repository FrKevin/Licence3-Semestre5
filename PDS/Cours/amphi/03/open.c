#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int fd;
    char tampon[10];
    int lus;

    fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror("ouverture");
        exit(EXIT_FAILURE);
    }

    while((lus = read(fd, tampon, 10)) > 0) {
        /* utiliser tampon[0] .. tampon[lus-1] */
        /* BUG! printf("%s", tampon); */
        assert(write(STDOUT_FILENO, tampon, lus) == lus);
    }

    if(lus == -1) {
        perror("lecture");
        exit(EXIT_FAILURE);
    }

    assert(close(fd) == 0);

    return 0;
}
