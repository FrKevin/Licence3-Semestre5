#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

typedef struct th_arg_s {
    char c;
    unsigned int nb;
    int res;
} th_arg;

int fonct(char c, unsigned int nb) {
    unsigned int i;

    for (i = 0; i < nb; i++) {
        putchar(c);
    }

    return 1234;
}

void *th_fonct(void *arg) {
    ((th_arg *)arg)->res =
        fonct(((th_arg *)arg)->c, ((th_arg *)arg)->nb);
    return arg;
}

int main(int argc, char *argv[]) {
    pthread_t tid, tid2;
    th_arg *arg;
    void * res2;

    arg = (th_arg *)malloc(sizeof(th_arg));
    assert(arg != NULL);
    arg->c = '|';
    arg->nb = 10000000;
    assert(pthread_create(&tid, NULL, th_fonct, arg) == 0);

    arg = (th_arg *)malloc(sizeof(th_arg));
    assert(arg != NULL);
    arg->c = '.';
    arg->nb = 10000000;
    assert(pthread_create(&tid2, NULL, th_fonct, arg) == 0);

    assert(pthread_join(tid, NULL) == 0);
    assert(pthread_join(tid2, &res2) == 0);

    /* pthread_exit(NULL); */

    return 0;
}
