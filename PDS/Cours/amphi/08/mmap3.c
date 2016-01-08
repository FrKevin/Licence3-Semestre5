#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct mempartagee_s {
    int c;
} mempartagee;

int main(int argc, char *argv[]) {
    mempartagee* ptr;

    ptr = mmap(NULL, sizeof(mempartagee),
               PROT_READ|PROT_WRITE,
               MAP_SHARED|MAP_ANONYMOUS,
               -1, 0);
    assert(ptr != MAP_FAILED);

    printf("%d\n",ptr->c);

    switch (fork()) {
        case -1: exit(EXIT_FAILURE);

        case 0: /* Fils */
            ptr->c = 12;
            exit(EXIT_SUCCESS);
    }

    sleep(1);
    printf("%d\n",ptr->c);

    return 0;
}
