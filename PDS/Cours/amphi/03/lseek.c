#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int fd;

    fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
    if(fd == -1) {
        perror("ouverture");
        exit(EXIT_FAILURE);
    }

    if(lseek(fd, 1 << 30, SEEK_SET) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    };

    assert(write(fd, "message", 8) == 8);

    assert(close(fd) == 0);

    return 0;
}
