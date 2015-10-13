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






int getNextLineBreak(char* s, int sLength, int startSearch) {
	int i;
	
	for (i = startSearch; i < sLength; i++)
		if (s[i] == '\n') return i;
	
	return -1;
}






long tail(char* pathname, int nbLines) {
	int fd, i, nbCharRead, lineBuffPos = 0, lineBreakPos, previousLineBreakPos = 0, sizeToCopy;
	char buff[4096];
	char curLineBuff[16384]; /* une ligne ne devrait probablement pas dépasser cette taille */
	LineBuffer lineBuffer;
	
	fd = open(pathname, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	
	/* lire tout le fichier */
	LineBuffer_init(&lineBuffer, nbLines);
	while((nbCharRead = read(fd, buff, 4096)) > 0) {
		previousLineBreakPos = 0;
		while((lineBreakPos = getNextLineBreak(buff, nbCharRead, previousLineBreakPos)) != -1) {
			if (lineBuffPos == 0) { /* on envoi directement la ligne dans le buffer circulaire */
				LineBuffer_addLine(&lineBuffer, &(buff[previousLineBreakPos]), lineBreakPos-previousLineBreakPos);
			}
			else { /* on ajoute à la suite du buffer de la ligne courante, qu'on vide ensuite */
				sizeToCopy = ((lineBreakPos - previousLineBreakPos) < (16384 - lineBuffPos))
					? (nbCharRead - previousLineBreakPos) : (16384 - lineBuffPos);
				memcpy(&(curLineBuff[lineBuffPos]), &(buff[previousLineBreakPos]), sizeToCopy);
				lineBuffPos += sizeToCopy;
				
				LineBuffer_addLine(&lineBuffer, curLineBuff, lineBuffPos);
				
				lineBuffPos = 0;
			}
			previousLineBreakPos = lineBreakPos + 1; /* +1 pour sauter le caractère \n */
		}
		/* il n'y a plus de retour à la ligne dans le buffer */
		if (previousLineBreakPos < nbCharRead && lineBuffPos < 16384) {
			sizeToCopy = ((nbCharRead - previousLineBreakPos) < (16384 - lineBuffPos))
					? (nbCharRead - previousLineBreakPos) : (16384 - lineBuffPos);
			memcpy(&(curLineBuff[lineBuffPos]), &(buff[previousLineBreakPos]), sizeToCopy);
			lineBuffPos += sizeToCopy;
		}
		
	}
	
	/* si il reste une ligne dans le buffer de ligne courante */
	if (lineBuffPos > 0) {
		LineBuffer_addLine(&lineBuffer, curLineBuff, lineBuffPos);
	}
	/* la ligne vide de fin de fichier ne devrait pas être envoyé au buffer */
	
	if (nbCharRead == -1) {
		fprintf(stderr, "Erreur de lecture du fichier : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	close(fd);
	
	
	
	/*
	 * Ici : affichage du buffer
	 */
	for (i = 0; i < lineBuffer.nbElement; i++) {
		LineBufferElement* lineElement;
		lineElement = LineBuffer_get(&lineBuffer, i);
		printf("%.*s\n", lineElement->line.length, lineElement->line.chars);
	}
	
	LineBuffer_clear(&lineBuffer);
	
	return EXIT_SUCCESS;
}
