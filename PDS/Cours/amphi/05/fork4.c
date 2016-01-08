#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int fd, lus, pos;
    char tampon[4];

    fd = open("alphabet", O_RDONLY);
    assert(fd != -1);

    printf("début\n");

    switch(pid = fork()) {
        case -1:
            exit(EXIT_FAILURE);

        case 0:
            /* fils */
            lus = read(fd, tampon, 3);
            assert(lus != -1);
            pos = lseek(fd, 10, SEEK_CUR);
            assert(pos != -1);
            tampon[lus] = '\0';
            printf("fils: \"%s\" (pos: %d)\n", tampon, pos);
            exit(EXIT_SUCCESS);

        default:
            /* père */
            lus = read(fd, tampon, 3);
            assert(lus != -1);
            pos = lseek(fd, 10, SEEK_CUR);
            assert(pos != -1);
            tampon[lus] = '\0';
            printf("père: \"%s\" (pos: %d)\n", tampon, pos);
    }

    return 0;
}
