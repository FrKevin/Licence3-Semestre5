#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char * ptr;
    int fd;
    int i;

    fd = open("mmap2.c", O_RDONLY);
    assert(fd != -1);

    ptr = mmap(NULL, 123, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(ptr != MAP_FAILED);

    for (i = 0; i < 123; i++) {
        printf("%c", ptr[i]);
    }

    munmap(ptr,123);
    close(fd);

    return 0;
}
