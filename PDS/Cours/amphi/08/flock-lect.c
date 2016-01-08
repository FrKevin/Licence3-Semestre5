#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TAILLETAMPON 80

int main(int argc, char *argv[]) {
    int fd, lus;
    unsigned char tampon[TAILLETAMPON];

    fd = open(argv[1], O_RDONLY);
    assert(fd != -1);

    if(flock(fd, LOCK_SH) == -1) {
        perror("verrou");
        exit(EXIT_FAILURE);
    }

    printf("Verrou acquis\n");

    while((lus = read(fd, tampon, TAILLETAMPON)) > 0) {
        write(STDOUT_FILENO, tampon, lus);
    }

    sleep(10);
    assert(flock(fd, LOCK_UN) != -1);
    close(fd);

    return EXIT_SUCCESS;
}
