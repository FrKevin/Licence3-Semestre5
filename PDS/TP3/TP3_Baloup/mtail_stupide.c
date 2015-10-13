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
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

typedef enum { false, true } bool;






/* paramètres du programme */
static char* opt_path;
static int opt_nb_lines = 10;



/* déclaration des fonctions */
long tail(char* pathname, int nbLines);
void analyseArgs(int argc, char** argv);


/* Main */
int main(int argc, char** argv) {
	analyseArgs(argc, argv);
	
	return tail(opt_path, opt_nb_lines);
}

 

/*
 * Analyse des arguments
 */
void analyseArgs(int argc, char** argv) {
	int optch;
	extern int opterr;
	
	/* chaine contenant les caractères des arguments */
	char format[] = "n:";

	opterr = 1;
	
	/* on parcours des arguments */
	while ((optch = getopt(argc, argv, format)) != -1)
		switch (optch) {
			case 'n':
				opt_nb_lines = atoi(optarg);
				if (opt_nb_lines <= 0) {
					fprintf(stderr, "Nombre de ligne strictement positif\n");
					exit(EXIT_FAILURE);
				}
				break;
		}
	
	if(optind >= argc) {
		fprintf(stderr, "Pas assez d'argument\n");
		exit(EXIT_FAILURE);
	}
	/* lis le dernier argument, qui est un chemin d'accès */
	opt_path = argv[optind];
}






int countLineBreaks(char* s, int sLength) {
	int i, count = 0;
	
	for (i = 0; i < sLength; i++)
		if (s[i] == '\n') count++;
	
	return count;
}






long tail(char* pathname, int nbLines) {
	int fd, nbCharRead, nbNL = 0, nbNLBeforePrint;
	char buff[4096];
	bool hasTailNL;
	
	fd = open(pathname, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	
	/* lire tout le fichier, compter les \n */
	while((nbCharRead = read(fd, buff, 4096)) > 0) {
		nbNL += countLineBreaks(buff, nbCharRead);
	}
	/* on vérifie si la dernière ligne se termine par un \n */
	lseek(fd, -1, SEEK_END);
	nbCharRead = read(fd, buff, 1);
	if (nbCharRead > 0 && buff[0] == '\n') {
		hasTailNL = true;
		nbNL--;
	}
	else if (nbCharRead == 0) {
		/* dans le cas d'un fichier vide, il ne faut pas afficher de \n, sinon la sortie affiche une ligne vide */
		hasTailNL = true;
	}
	
	/* on se repotitionne en début de fichier */
	lseek(fd, 0, SEEK_SET);
	
	nbNLBeforePrint = nbNL - nbLines;
	
	/* on lit le fichier du début, et on affiche dès qu'on a apssé les retours à la ligne à ignorer */
	while (read(fd, buff, 1) > 0) {
		if (nbNLBeforePrint < 0) {
			printf("%c", buff[0]);
		}
		else if (buff[0] == '\n') {
			nbNLBeforePrint--;
		}
	}
	
	if (hasTailNL == false)
		printf("\n");
	
	close(fd);
	
	return EXIT_SUCCESS;
}
