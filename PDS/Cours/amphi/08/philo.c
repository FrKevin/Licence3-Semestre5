#include <sys/mman.h>
#include <semaphore.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NB_PHILOS 5

/* strace -f -e 'trace=!write' ./philo */

sem_t *sems;

void philo(int num) {
    while (1) {
        assert(sem_wait(&(sems[num])) != -1);
        assert(sem_wait(&(sems[(num+1)%NB_PHILOS])) != -1);
        printf("%d: mange\n", num);
        fflush(stdout);
        assert(sem_post(&(sems[(num+1)%NB_PHILOS])) != -1);
        assert(sem_post(&(sems[num])) != -1);
        printf("%d: pense\n", num);
        fflush(stdout);
    }
}

int main(int argc, char *argv[]) {
    int i;

    sems = (sem_t*)mmap(NULL, NB_PHILOS*sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    assert(sems != NULL);

    for (i = 0; i < NB_PHILOS; i++) {
        assert(sem_init(&(sems[i]), 1, 1) != -1);
    }

    for (i = 1; i < NB_PHILOS; i++) {
        switch (fork()) {
            case -1: exit(EXIT_FAILURE);

            case 0: /* Fils */
                philo(i);
                exit(EXIT_SUCCESS);
        }
    }

    philo(0);

    return 0;
}
