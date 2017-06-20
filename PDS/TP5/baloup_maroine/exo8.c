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
#include <sys/wait.h>
#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

typedef enum { false, true } bool;


typedef int (*func_t) (int);


pid_t createProcess(func_t func, int arg) {
	pid_t pid;
	
	pid = fork();
	if (pid == -1) {        /* erreur */
		perror("erreur fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {  /* fils */
		exit(func(arg));
	} else {                /* pere */
		return pid;
	}
}




/* déclaration des fonctions */
int exo8(int nbChild);


/* Main */
int main(int argc, char** argv) {
	int nbProc;
	if (argc <= 1) {
		fprintf(stderr, "Spécifiez le nombre de processus fils.\n");
		return EXIT_FAILURE;
	}
	
	nbProc = atoi(argv[1]);
	
	
	if (nbProc <= 0) {
		fprintf(stderr, "Le nombre de processus fils n'est pas valide.\n");
		return EXIT_FAILURE;
	}
	
	return exo8(nbProc);
}





int sonProcess(int order) {
	while(1) {
		printf("%i est toujours vivant avec le PID %i\n", order, getpid());
		fflush(stdout);
		sleep(5);
	}
	return EXIT_SUCCESS;
}






int exo8(int nbChild) {
	int i;
	pid_t terminatedProcess;
	
	/* lancement des n processus */
	for (i=0; i<nbChild; i++) {
		createProcess(sonProcess, i);
	}
	
	system("ps");
	
	
	/* attente des n processus */
	for (i=0; i<nbChild; i++) {
		printf("Appuyez sur une touche pour lancer le wait ...\n");
		fflush(stdout);
		getc(stdin);
		terminatedProcess = wait(NULL);
		printf("Processus fils terminé : %i\n", terminatedProcess);
		fflush(stdout);
	}
	
	return EXIT_SUCCESS;
}
