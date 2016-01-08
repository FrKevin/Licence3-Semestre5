#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    void * ptr;
    char cmd[1000];

    snprintf(cmd, 1000, "less -S /proc/%d/maps\n", getpid());
    system(cmd);

    ptr = mmap(NULL, 123,
               PROT_READ|PROT_WRITE,
               MAP_SHARED|MAP_ANONYMOUS,
               -1, 0);
    assert(ptr != MAP_FAILED);

    printf("%p\n", ptr);

    system(cmd);

    return 0;
}
