#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

/* Signature de fonction */
unsigned long compteur_gc(char *bloc, unsigned long taille);
void *wrapper(void *arg);
long mtcompteur_gc(char* tampon, unsigned long taille, int nthread);

/* tharg => thread_arg */
typedef struct {
  char *bloc;
  unsigned long taille;
  unsigned long result;
} tharg_t;

unsigned long compteur_gc(char *bloc, unsigned long taille) {
    unsigned long i, cptr = 0;

    for (i = 0; i < taille; i++) {
        if (bloc[i] == 'G' || bloc[i] == 'C') {
            cptr++;
        }
    }
    return cptr;
}

void *wrapper(void *arg) {
  tharg_t *th_arg = (tharg_t*) arg;
  th_arg->result = compteur_gc(th_arg->bloc, th_arg->taille);
  return NULL;
}

long mtcompteur_gc(char* tampon, unsigned long taille, int nthread) {
  unsigned long i;
  pthread_t *t_pthread;
  tharg_t **t_th_arg;
  unsigned long segment_size;
  unsigned long result = 0;

  /* Allocation variables */
  /* Tableau de threads */
  t_pthread = (pthread_t*)malloc(sizeof(pthread_t)*nthread);
  assert(t_pthread != NULL);
  /* Tableau de pointeur d'argument de threads */
  t_th_arg = (tharg_t **)malloc(sizeof(tharg_t *)*nthread);
  assert(t_th_arg != NULL);

  segment_size = taille/nthread;
  for (i = 0 ; i < nthread-1; i++) {
    t_th_arg[i] = (tharg_t *)malloc(sizeof(tharg_t));
    assert(t_th_arg[i] != NULL);

    t_th_arg[i]->result = 0;
    t_th_arg[i]->bloc = tampon + i * segment_size;
    t_th_arg[i]->taille = segment_size;
    pthread_create(&t_pthread[i], NULL, wrapper, t_th_arg[i]);
  }

  t_th_arg[i]->result = 0; /* i = n-1 */
  t_th_arg[i]->bloc = tampon + i * segment_size;
  t_th_arg[i]->taille = taille - segment_size * i;
  pthread_create(&t_pthread[i], NULL, wrapper, t_th_arg[i]);

  /* Boucle d'attente */
  for(i = 0; i < nthread; i++){
    pthread_join(t_pthread[i], NULL);
    result += t_th_arg[i]->result;
    free(t_th_arg[i]);
    t_th_arg[i] = NULL;
  }
  free(t_pthread);
  t_pthread = NULL;
  return result;
}

int main(int argc, char *argv[]) {
    struct stat st;
    int fd;
    char *tampon;
    int lus;
    unsigned long cptr = 0;
    off_t taille = 0;
    struct timespec debut, fin;

    assert(argv[1] != NULL);

    /* Quelle taille ? */
    assert(stat(argv[1], &st) != -1);
    tampon = malloc(st.st_size);
    assert(tampon != NULL);

    /* Chargement en mémoire */
    fd = open(argv[1], O_RDONLY);
    assert(fd != -1);
    while ((lus = read(fd, tampon + taille, st.st_size - taille)) > 0){
        taille += lus;
    }
    assert(lus != -1);
    assert(taille == st.st_size);
    close(fd);

    /* Calcul proprement dit */
    assert(clock_gettime(CLOCK_MONOTONIC, &debut) != -1);
    cptr = compteur_gc(tampon, taille);
    assert(clock_gettime(CLOCK_MONOTONIC, &fin) != -1);

    /* Affichage des résultats */
    printf("Nombres de GC:   %ld\n", cptr);
    printf("Taux de GC:      %lf\n", ((double) cptr) / ((double) taille));

    fin.tv_sec  -= debut.tv_sec;
    fin.tv_nsec -= debut.tv_nsec;
    if (fin.tv_nsec < 0) {
        fin.tv_sec--;
        fin.tv_nsec += 1000000000;
    }
    printf("Durée de calcul: %ld.%09ld\n", fin.tv_sec, fin.tv_nsec);
    printf("(Attention: très peu de chiffres après la virgule sont réellement significatifs !)\n");

    return 0;
}