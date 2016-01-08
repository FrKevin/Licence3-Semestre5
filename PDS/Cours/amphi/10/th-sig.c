#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <signal.h>

#define NB_THREADS 4

pthread_t thread_ids[NB_THREADS];

void sigusr_handler(int sig) {
    int i;

    for(i = 0; i < NB_THREADS; i++) {
        if (pthread_equal(pthread_self(), thread_ids[i]))
            break;
    }

    fprintf(stderr, "Traitant de signal USR%c dans le thread %d\n", (sig==SIGUSR1)?'1':'2', i);
}

#define NUM (*((int *)num))
void *attente(void *num) {
    thread_ids[NUM] = pthread_self();
    pthread_detach(pthread_self());
    fprintf(stderr, "Thread %d prêt\n", NUM);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    if(NUM == 0)
        pthread_sigmask(SIG_BLOCK, &mask, NULL);

    while(1) {
        sleep(10);
        if (NUM == NB_THREADS - 1)
            /* pthread_kill(thread_ids[0], SIGUSR2); */
            /* pthread_kill(thread_ids[0], SIGUSR1); */
            /* pthread_kill(thread_ids[1], SIGKILL); */
            if (thread_ids[1]) {
                fprintf(stderr, "Annule le thread 1\n");
                assert(pthread_cancel(thread_ids[1]) == 0);
                thread_ids[1] = 0;
                usleep(100000);
                system("ps -Tm");
            }
    }

    free(num);

    return NULL;
}

int main(int argc, char *argv[]) {
    int i;
    int *num;
    pthread_t threadid;
    struct sigaction sa;

    sa.sa_handler = &sigusr_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    assert(sigaction(SIGUSR1, &sa, NULL) != -1);
    assert(sigaction(SIGUSR2, &sa, NULL) != -1);

    for(i = 1; i < NB_THREADS; i++) {
        num = malloc(sizeof(int));
        assert(num);
        *num = i;
        assert(pthread_create(&threadid, NULL, &attente, num) == 0);
    }

    system("ps -Tm");

    num = malloc(sizeof(int));
    *num = 0;
    attente(num);

    return 0;
}
