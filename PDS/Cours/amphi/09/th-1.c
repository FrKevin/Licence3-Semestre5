#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

/* cf. 05/fork2 */

typedef void *th_func(void *);

void *modifie(void *p_int) {
    *(int *)p_int = 1234;

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    int i = 42;

    printf("%d\n", i);

    assert(pthread_create(&tid, NULL, &modifie, &i) == 0);

    usleep(10000);
    printf("%d\n", i);

    return 0;
}
