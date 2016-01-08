#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int fd;

    printf("Début");
    fflush(stdout);

    fd = open("/tmp/log", O_WRONLY | O_CREAT, 0644);
    assert(fd != -1);
    assert(dup2(fd, STDOUT_FILENO) == STDOUT_FILENO);
    close(fd);

    printf("Fin\n");

    return 0;
}
