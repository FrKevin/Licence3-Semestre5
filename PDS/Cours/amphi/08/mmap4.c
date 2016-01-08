#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

#define ITER 1000000

typedef struct mempartagee_s {
    int c1,c2,c3;
    sem_t sem;
} mempartagee;

int main(int argc, char *argv[]) {
    mempartagee* ptr;
    int i;

    ptr = mmap(NULL, sizeof(mempartagee),
               PROT_READ|PROT_WRITE,
               MAP_SHARED|MAP_ANONYMOUS,
               -1, 0);
    assert(ptr != MAP_FAILED);

    sem_init(&(ptr->sem), 1, 1);

    switch (fork()) {
        case -1: exit(EXIT_FAILURE);

        case 0: /* Fils */
            for (i = 0; i < ITER; i++) {
                assert(sem_wait(&(ptr->sem)) != -1);
                ptr->c1 ++;
                assert(sem_post(&(ptr->sem)) != -1);
                ptr->c2 ++;
            }
            exit(EXIT_SUCCESS);
    }

    for (i = 0; i < ITER; i++) {
        assert(sem_wait(&(ptr->sem)) != -1);
        ptr->c1 ++;
        assert(sem_post(&(ptr->sem)) != -1);
        ptr->c3 ++;
    }

    wait(NULL);

    printf("%d + %d = %d = %d\n",ptr->c2,ptr->c3,ptr->c2+ptr->c3,ptr->c1);

    return 0;
}
