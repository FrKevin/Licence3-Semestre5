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

typedef enum { false, true } bool;
typedef int(*func_t)(int);

/* déclaration des fonctions */
int multif(func_t functions[], int args[], int n);
int test(int val);


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

	multif(functions, values, nb_values);
	return EXIT_SUCCESS;
}

/* Multif */
int multif(func_t functions[], int args[], int n) {
	int i;
	for(i = 0; i<n; ++i) {
		printf("Résultat pour test(%i) : %i\n", args[i], functions[i](args[i]));
		fflush(stdout);
	}

	return EXIT_SUCCESS;
}

/* Test */
int test(int val) {
	return (val<=10?0:1);
}