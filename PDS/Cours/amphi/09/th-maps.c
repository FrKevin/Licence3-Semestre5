#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

void *fonct(void* p_attente) {
    printf("[%ld] Adresse de l’argument: %p\n", pthread_self(), &p_attente);
    fflush(stdout);

    if(p_attente != NULL)
        usleep(*(unsigned long *)p_attente);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread_id;
    unsigned long attente = 300000;
    char catmaps[1000];

    snprintf(catmaps, 1000,
        "echo; "
        "cat /proc/%d/maps | "
            "sed 's/[ \t][ \t]*/ /g' | "
            "sed 's|/.*/||g' | "
            "cut -d ' ' -f 1,2,6",
        getpid());

    printf("Démarrage (thread main: %ld)\n", pthread_self());
    system(catmaps);

    printf("\nCréation d’un thread\n");
    assert(pthread_create(&thread_id, NULL, &fonct, &attente) == 0);
    fonct(NULL);

    system(catmaps);

    printf("\nps -Tm:\n");
    system("ps -Tm");

    assert(pthread_join(thread_id, NULL) == 0);

    printf("\nFin de main\n");

    return EXIT_SUCCESS;
}
