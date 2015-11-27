#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

















unsigned long compteur_gc(char *bloc, unsigned long taille) {
    unsigned long i, cptr = 0;

    for (i = 0; i < taille; i++)
        if (bloc[i] == 'G' || bloc[i] == 'C')
            cptr++;

    return cptr;
}



/*
 * Wrapping
 */
typedef struct arg_s {
	char* bloc;
	unsigned long taille;
	
	
	unsigned long returnVal;
} arg_t;

void* wrapper(void* args) {
	arg_t* data = (arg_t*) args;
	data->returnVal = compteur_gc(data->bloc, data->taille);
	return NULL;
}
/*
 */




/*
 * Premier argument : le nombre de thread
 * Deuxième argument : le chemin du fichier
 */

int main(int argc, char *argv[]) {
    struct stat st;
    int fd, i, lastPos = 0, currentPos = 0, nbPerThread;
    int nbThread;
    char *tampon;
    int lus, compact_result = 0;
    unsigned long cptr = 0;
    off_t taille = 0;
    struct timespec debut, fin;
    pthread_t* threads;
    arg_t* threadsArgs;
    
    if (argc <= 2) {
		printf("Nécessite au moins 2 arguments.\n");
		printf("Utilisation : %s <NbThread> <Path>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	nbThread = atoi(argv[1]);
	if (nbThread <= 0) {
		printf("Nombre de thread invalide : %s\n", argv[1]);
		printf("Valeur autorisé : nombre entier > 0");
		return EXIT_FAILURE;
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
    while ((lus = read(fd, tampon + taille, st.st_size - taille)) > 0)
        taille += lus;
    assert(lus != -1);
    assert(taille == st.st_size);
    close(fd);
    
    /* Répartition du travail */
    threads = malloc(sizeof(pthread_t)*nbThread);
    threadsArgs = malloc(sizeof(arg_t)*nbThread);
    
    nbPerThread = (taille / nbThread) + 1;
    for (i=0; i<nbThread; i++) {
		threadsArgs[i].bloc = &(tampon[lastPos]);
		currentPos = lastPos + nbPerThread;
		if (currentPos > taille)
			currentPos = taille;
			
		threadsArgs[i].taille = currentPos-lastPos;
		if (!compact_result)
			printf("%i : %i -> %lu\n", i, lastPos, threadsArgs[i].taille);
		lastPos = currentPos;
	}
    
    

    /* Calcul proprement dit */
    assert(clock_gettime(CLOCK_MONOTONIC, &debut) != -1);
    
    
    /* création threads */
    for (i=0; i<nbThread; i++) {
		assert(pthread_create(&(threads[i]), NULL, wrapper, &(threadsArgs[i])) == 0);
	}
	/* attente threads */
    for (i=0; i<nbThread; i++) {
		assert(pthread_join(threads[i], NULL) == 0);
		cptr += threadsArgs[i].returnVal;
	}
	
    
    assert(clock_gettime(CLOCK_MONOTONIC, &fin) != -1);
	/* Fin des calculs */
	
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
    return EXIT_SUCCESS;
}
