#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>


#define VERBOSE 0

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
  tharg_t *t_th_arg;
  unsigned long segment_size =  taille/nthread;
  unsigned long result = 0;

  /* Allocation variables */
  /* Tableau de threads */
  t_pthread = (pthread_t*)malloc(sizeof(pthread_t) * nthread);
  assert(t_pthread != NULL);

  /* Tableau de pointeur d'argument de threads */
  t_th_arg = (tharg_t *)malloc(sizeof(tharg_t) * nthread);
  assert(t_th_arg != NULL);

  for (i = 0 ; i < nthread; i++) {
    #if VERBOSE == 1
      printf("Threads %ld\n", i);
    #endif
    t_th_arg[i].result = 0;
    t_th_arg[i].bloc = &(tampon[i * segment_size]);
    t_th_arg[i].taille = (i != nthread -1) ? segment_size : taille - segment_size * i;
    #if VERBOSE == 1
      printf("Args->begin : %ld, Args->taille %ld\n", i * segment_size, t_th_arg[i].taille);
    #endif
    pthread_create(&(t_pthread[i]), NULL, wrapper, &(t_th_arg[i]) );
  }

  /* Boucle d'attente d */
  for(i = 0; i < nthread; i++){
    pthread_join(t_pthread[i], NULL);
    result += t_th_arg[i].result;
  }

  free(t_pthread);
  free(t_th_arg);
  return result;
}

int main(int argc, char *argv[]) {
    struct stat st;
    int fd;
    char *tampon;
    int lus;
    int nthread;
    int compact_result = 0;
    unsigned long cptr = 0;
    off_t taille = 0;
    struct timespec debut, fin;

    if (argc <= 2) {
      printf("Nécessite au moins 2 arguments.\n");
      printf("Utilisation : %s <NbThread> <Path>\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    nthread = atoi(argv[1]);
    if (nthread < 0) {
      printf("Nombre de thread invalide : %s\n", argv[1]);
  		printf("Valeur autorisé : nombre entier > 0");
      exit(EXIT_FAILURE);
    }

    if (argc > 3 && (argv[3][0] == 'c' || argv[3][0] == 'C')) {
      compact_result = 1;
    }

    /* Quelle taille ? */
    assert(stat(argv[2], &st) != -1);
    tampon = malloc(st.st_size);
    assert(tampon != NULL);

    /* Chargement en mémoire */
    fd = open(argv[2], O_RDONLY);
    assert(fd != -1);
    while ((lus = read(fd, tampon + taille, st.st_size - taille)) > 0){
        taille += lus;
    }
    assert(lus != -1);
    assert(taille == st.st_size);
    close(fd);

    /* Calcul proprement dit */
    assert(clock_gettime(CLOCK_MONOTONIC, &debut) != -1);
    cptr = mtcompteur_gc(tampon, taille, nthread);
    assert(clock_gettime(CLOCK_MONOTONIC, &fin) != -1);

    /* Affichage des résultats */
    if (!compact_result) {
      printf("Nombres de GC:   %ld\n", cptr);
      printf("Taux de GC:      %lf\n", ((double) cptr) / ((double) taille));
    }
    fin.tv_sec  -= debut.tv_sec;
    fin.tv_nsec -= debut.tv_nsec;
    if (fin.tv_nsec < 0) {
        fin.tv_sec--;
        fin.tv_nsec += 1000000000;
    }
    if (!compact_result) {
      printf("Durée de calcul: %ld.%09ld\n", fin.tv_sec, fin.tv_nsec);
      printf("(Attention: très peu de chiffres après la virgule sont réellement significatifs !)\n");
    }
    else {
      printf("%ld.%09ld", fin.tv_sec, fin.tv_nsec);
    }
    exit(EXIT_SUCCESS);
}
