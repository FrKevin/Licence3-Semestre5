#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

/* t_arg => thread_arg */
typedef struct {
  char* bloc;
  unsigned long taille;
  unsigned long result;
} t_arg;

void* wrapper(void* arg){
  t_arg* struct_compteur = (t_arg*) arg;
  struct_compteur->result = compteur_gc(struct_compteur->bloc, struct_compteur->taille);
  return NULL;
}

void compteur_gc_thrad(char* tampon, unsigned long taille, int nthread){
  unsigned long i;
  pthread_t* t_pthread;
  unsigned long taille_segment;
  unsigned long result = 0;

  /* Exemple un buffer de 2 pour 4 thread */
  if( taille < nthread){
    return;
  }

  /* Creation du tablean de n thread */
  t_pthread = (pthread_t*)malloc(sizeof(pthread_t)*nthread);
  assert(t_pthread != NULL);

  taille_segment = taille/nthread;
  for(i=0 ; i<nthread-1; i++){
    t_arg* struct_compteur_gc = (t_arg*)malloc(sizeof(t_arg));
    assert(struct_compteur_gc != NULL);

    struct_compteur_gc->result = 0;
    struct_compteur_gc->bloc = tampon+i * nthread;
    struct_compteur_gc->taille = taille_segment;
    pthread_create(t_pthread[i], NULL, wrapper, struct_compteur_gc);
  }
  
  pthread_create(t_pthread[nthread-1], NULL, wrapper, struct_compteur_gc);
  for(i = 0; i < nthread; i++){
    pthread_join(t_pthread[i], NULL);

  }
}

unsigned long compteur_gc(char *bloc, unsigned long taille) {
    unsigned long i, cptr = 0;

    for (i = 0; i < taille; i++)
        if (bloc[i] == 'G' || bloc[i] == 'C')
            cptr++;

    return cptr;
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
