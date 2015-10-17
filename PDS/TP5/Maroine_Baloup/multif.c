/*
 * Par Maxime MAROINE et Marc BALOUP
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
#include <wait.h>

typedef enum { false, true } bool;
typedef int(*func_t)(int);

pid_t create_process(func_t func, int arg) {
	pid_t pid;
	
	pid = fork();
	if (pid == -1) {        /* Erreur */
		perror("Erreur fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {  /* Fils */
		exit(func(arg));
	} else {                /* Pere */
		return pid;
	}
}

/* déclaration des fonctions */
int multif(func_t functions[], int args[], int n);
int test(int val);
int wait_for_all_child(int n);


/* Main */
int main(int argc, char** argv) {
	int nb_values = argc-1;
	int* values = malloc(sizeof(int)*nb_values);
	func_t* functions = malloc(sizeof(func_t)*nb_values);
	int i;

	for(i = 1; i<nb_values+1; ++i) {
		functions[i-1] = test;
		values[i-1] = atoi(argv[i]);
	}

	printf("Résultat final : %i\n", multif(functions, values, nb_values));
	fflush(stdout);
	free(values);
	free(functions);
	return EXIT_SUCCESS;
}

/* Multif */
int multif(func_t functions[], int args[], int n) {
	int i;

	for(i = 0; i<n; ++i) {
		create_process(functions[i], args[i]);
	}
	
	return wait_for_all_child(n);
}

/* Comparer les valeurs */
int test(int val) {
	return (val > 10);
}

int wait_for_all_child(int n) {
	int status;
	int res = 1;
	int i;

	for(i = 0; i<n; ++i) {
		wait(&status);
		res &= WEXITSTATUS(status);
	}

	return res;
}