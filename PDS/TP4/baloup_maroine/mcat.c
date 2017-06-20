/*
 * Par Marc Baloup et Maxime Maroine 
 * 
 * Licence 3 Informatique - Université Lille 1
 * 
 * 2015-2016
 */
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

typedef enum { false, true } bool;

/* déclaration des fonctions */
long cat(char* pathname, int buffsize);


/* Main */
int main(int argc, char** argv) {
	char* bufSizeEnv;
	int buffsize;
	
	if (argc == 0) {
		fprintf(stderr, "Spécifiez le chemin d'accès du fichier.\n");
		return EXIT_FAILURE;
	}
	
	bufSizeEnv = getenv("MCAT_BUFSIZ");
	
	if (bufSizeEnv == NULL) {
		fprintf(stderr, "Nécessite la variable d'environnement MCAT_BUFSIZ pour fonctionner.\n");
		return EXIT_FAILURE;
	}
	
	buffsize = atoi(bufSizeEnv);
	if (buffsize <= 0) {
		fprintf(stderr, "La variable d'environnement MCAT_BUFSIZ n'est pas valide.\n");
		return EXIT_FAILURE;
	}
	
	
	return cat(argv[1], buffsize);
}






long cat(char* pathname, int buffsize) {
	int fd, nbCharRead;
	char* buffer = malloc(sizeof(char)*buffsize);
	
	fd = open(pathname, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	
	/* lire tout le fichier */
	while((nbCharRead = read(fd, buffer, buffsize)) > 0) {
		assert(write(STDOUT_FILENO, buffer, nbCharRead)>=0);
	}
	
	free(buffer);
	
	
	if (nbCharRead == -1) {
		fprintf(stderr, "Erreur de lecture du fichier : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	close(fd);
	
	return EXIT_SUCCESS;
}
