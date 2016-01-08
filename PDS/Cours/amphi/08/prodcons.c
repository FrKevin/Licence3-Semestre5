#include <sys/mman.h>
#include <semaphore.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define TAILLE_DONNEE 32
#define TAILLE_FILE   250
#define ITER          1000000

typedef struct donnee_s {
    char ch[TAILLE_DONNEE];
} donnee;

typedef struct mempartagee_s {
    donnee file[TAILLE_FILE];
    int premier_libre;
    int premier_occupe;
    sem_t sem_libre;
    sem_t sem_occup;
} mempartagee;

int main(int argc, char *argv[]) {
    mempartagee *m;
    int i;

    m = (mempartagee*)mmap(NULL, sizeof(mempartagee), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    assert(m != MAP_FAILED);
    m->premier_libre = 0;
    m->premier_occupe = 0;

    assert(sem_init(&(m->sem_libre),1,TAILLE_FILE) != -1);
    assert(sem_init(&(m->sem_occup),1,0) != -1);

    switch (fork()) {
        case -1: exit(EXIT_FAILURE);

        case 0: /* Producteur */
            for (i = 0; i < ITER; i++) {
                assert(sem_wait(&(m->sem_libre)) != -1);
                snprintf(m->file[m->premier_libre].ch, TAILLE_DONNEE, "Donnée %d", i);
                printf("Éc: %s\n", m->file[m->premier_libre].ch);
                fflush(stdout);
                m->premier_libre = (m->premier_libre + 1) % TAILLE_FILE;
                assert(sem_post(&(m->sem_occup)) != -1);
            }
            exit(EXIT_SUCCESS);

        default: /* Consommateur */
            for (i = 0; i < ITER; i++) {
                assert(sem_wait(&(m->sem_occup)) != -1);
                printf("Lu: %s\n", m->file[m->premier_occupe].ch);
                fflush(stdout);
                m->premier_occupe = (m->premier_occupe + 1) % TAILLE_FILE;
                assert(sem_post(&(m->sem_libre)) != -1);
            }
    }

    return 0;
}
