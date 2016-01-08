#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>

#define ITER 1000000

typedef struct mempartagee_s {
    int c1,c2,c3;
    sem_t sem;
} mempartagee;

mempartagee m;

void *th_compteur(void *arg) {
    int i;

    for (i = 0; i < ITER; i++) {
        assert(sem_wait(&(m.sem)) != -1);
        m.c1 ++;
        assert(sem_post(&(m.sem)) != -1);
        m.c2 ++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    int i;

    sem_init(&(m.sem), 0, 1);

    assert(pthread_create(&tid, NULL, th_compteur, NULL) == 0);

    for (i = 0; i < ITER; i++) {
        assert(sem_wait(&(m.sem)) != -1);
        m.c1 ++;
        assert(sem_post(&(m.sem)) != -1);
        m.c3 ++;
    }

    assert(pthread_join(tid, NULL) == 0);

    printf("%d + %d = %d = %d\n",m.c2,m.c3,m.c2+m.c3,m.c1);

    return 0;
}
