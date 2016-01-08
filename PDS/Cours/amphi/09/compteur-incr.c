#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int increment(int i) {
    static int c = 0;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    c += i;
    pthread_mutex_unlock(&mutex);

    return c;
}

#define ITER 1000000

void * boucle(void *a) {
    int i;

    for(i = 0; i < ITER; i ++)
        increment(1);

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t tid;

    assert(pthread_create(&tid, NULL, &boucle, NULL) == 0);
    boucle(NULL);
    assert(pthread_join(tid, NULL) == 0);

    printf("Bilan : %d\n", increment(0));

    return EXIT_SUCCESS;
}
