#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

char catmaps[1000];

void def_catmaps() {
    snprintf(catmaps, 1000,
        "cat /proc/%d/maps | "
            "sed 's/[ \t][ \t]*/ /g' | "
            "sed 's|/.*/||g' | "
            "cut -d ' ' -f 1,2,6",
        getpid());
}

void affiche_infos(unsigned int numero) {
    printf("Thread numéro %u\n", numero);
    fflush(stdout);
    system(catmaps);
    system("ps -Tm");
}

typedef struct th_arg_s {
    unsigned long attente;
    unsigned int  numero;
} th_arg;

#define ARG ((th_arg *) arg)
void *fonct(void* arg) {
    assert(pthread_detach(pthread_self()) == 0);
    if(ARG->attente > 0)
        usleep(ARG->attente);
    if(ARG->numero == 1)
        switch (fork()) {
            case -1: exit(EXIT_FAILURE);
            case 0: /* Fils */
                     sleep(1);
                     def_catmaps();
                     affiche_infos(getpid());
                     exit(EXIT_SUCCESS);
        }
    affiche_infos(ARG->numero);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t thread_id;
    th_arg * arg;

    def_catmaps();
    affiche_infos(0);

    printf("\nCréation du thread 1\n");
    arg = malloc(sizeof(th_arg));
    assert(arg != NULL);
    arg->attente = 2000000;
    arg->numero  = 1;
    assert(pthread_create(&thread_id, NULL, &fonct, arg) == 0);

    printf("\nCréation du thread 2\n");
    arg = malloc(sizeof(th_arg));
    assert(arg != NULL);
    arg->attente = 1000000;
    arg->numero  = 2;
    assert(pthread_create(&thread_id, NULL, &fonct, arg) == 0);

    arg = malloc(sizeof(th_arg));
    assert(arg != NULL);
    arg->attente = 0;
    arg->numero  = 0;
    fonct(arg);

    return 123;
}
