#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int fd;

    /* fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); */
    fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
    if(fd == -1) {
        perror("ouverture");
        exit(EXIT_FAILURE);
    }

    assert(write(fd, "message", 8) == 8);

    assert(close(fd) == 0);

    return 0;
}
