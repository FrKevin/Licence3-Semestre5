#include <sys/mman.h>
#include <semaphore.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define TAILLE_DONNEE 32
#define TAILLE_FILE   250
#define ITER          1000000

typedef struct donnee_s {
    char ch[TAILLE_DONNEE];
} donnee;

donnee file[TAILLE_FILE];
int nb_occupes;
int premier_occupe;
pthread_mutex_t mutex            = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producteur   = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consommateur = PTHREAD_COND_INITIALIZER;

void *producteur(void *arg) {
    int i;

    for (i = 0; i < ITER; i++) {
        assert(pthread_mutex_lock(&mutex) == 0);
        while(nb_occupes == TAILLE_FILE)
            assert(pthread_cond_wait(&cond_producteur, &mutex) == 0);
        snprintf(file[(premier_occupe+nb_occupes)%TAILLE_FILE].ch, TAILLE_DONNEE, "Donnée %d", i);
        printf("Éc: %s\n", file[(premier_occupe+nb_occupes)%TAILLE_FILE].ch);
        fflush(stdout);
        nb_occupes++;
        assert(pthread_cond_signal(&cond_consommateur) == 0);
        assert(pthread_mutex_unlock(&mutex) == 0);
    }

    return NULL;
}

void *consommateur(void *arg) {
    int i;

    for (i = 0; i < ITER; i++) {
        assert(pthread_mutex_lock(&mutex) == 0);
        while (nb_occupes == 0)
            assert(pthread_cond_wait(&cond_consommateur, &mutex) == 0);
        printf("Lu: %s\n", file[premier_occupe].ch);
        fflush(stdout);
        premier_occupe = (premier_occupe + 1) % TAILLE_FILE;
        nb_occupes--;
        assert(pthread_cond_signal(&cond_producteur) == 0);
        assert(pthread_mutex_unlock(&mutex) == 0);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t tid;

    premier_occupe = 0;
    nb_occupes = 0;

    assert(pthread_create(&tid, NULL, &producteur, NULL) == 0);
    consommateur(NULL);
    assert(pthread_join(tid, NULL) == 0);

    return 0;
}
