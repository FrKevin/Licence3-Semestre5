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
int race();


/* Main */
int main(int argc, char** argv) {
	
	
	return race();
}





int sonProcess(int order) {
	int count;
	printf("Lancement du processus %i\n", order);
	fflush(stdout);
	for (count = 0; count < 100000000; count++);
	printf("Processus %i arrivé jusqu'à 100 000 000\n", order);
	fflush(stdout);
	for (count = 0; count < 100000000; count++);
	return EXIT_SUCCESS;
}





int getPidIndex(pid_t table[], int tableSize, pid_t valueSearchFor) {
	int i;
	for (i=0; i<tableSize; i++)
		if (table[i] == valueSearchFor)
			return i;
	return -1;
}





int race() {
	pid_t pids[10]; /* liste des PID dans l'ordre de début d'exécution */
	int i;
	
	/* lancement des 10 processus */
	for (i=0; i<10; i++) {
		pids[i] = createProcess(sonProcess, i);
	}
	
	/* attente des10 processus */
	for (i=0; i<10; i++) {
		printf("Processus %i arrivé à la position %i\n", getPidIndex(pids, 10, wait(NULL)), i);
		fflush(stdout);
	}
	
	
	
	return EXIT_SUCCESS;
}
