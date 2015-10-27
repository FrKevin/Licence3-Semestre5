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
#include "makeargv.h"

typedef enum { false, true } bool;


pid_t createProcess(char* command) {
	pid_t pid;
	char **cmdargv;
	
	pid = fork();
	if (pid == -1) {        /* erreur */
		perror("erreur fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {  /* fils */
		
		makeargv(command, " ", &cmdargv);
		
		execvp(cmdargv[0], cmdargv);
		
		perror("erreur execvp");
		
		exit(EXIT_FAILURE);
	} else {                /* pere */
		return pid;
	}
}




/* déclaration des fonctions */
int do_();






static bool opt_and = true;
static bool opt_or = false;
static bool opt_cc = false;
static bool opt_kill = false;

static char** opt_path_v;
static int opt_path_c;




/*
 * Analyse des arguments
 */
void analyseArgs(int argc, char** argv) {
	int optch;
	extern int opterr;
	
	/* chaine contenant les caractères des arguments */
	char format[] = "aock";

	opterr = 1;
	
	/* on parcours des arguments */
	while ((optch = getopt(argc, argv, format)) != -1)
		switch (optch) {
			case 'a':
				opt_and = true;
				opt_or = false;
				break;
			case 'o':
				opt_or = true;
				opt_and = false;
				break;
			case 'c':
				opt_cc = true;
				break;
			case 'k':
				opt_kill = true;
				break;
		}
	
	if (opt_cc == false)
		opt_kill = false; /* garde une cohérence dans les paramètres :
			-k n'est pas nécessaire si on utilise pas -c */
	
	if(optind >= argc) {
		fprintf(stderr, "Pas assez d'argument\n");
		exit(EXIT_FAILURE);
	}
	/* lis les derniers arguments, qui sont des lignes de commandes */
	opt_path_c = argc - optind;
	opt_path_v = &(argv[optind]);
	
}












/* Main */
int main(int argc, char** argv) {
	
	analyseArgs(argc, argv);
	
	return do_();
}











int do_() {
	int i;
	int result;
	int returnVal;
	pid_t* processes;
	
	processes = malloc(opt_path_c * sizeof(pid_t));
	
	
	for (i = 0; i < opt_path_c; i++) {
		processes[i] = createProcess(opt_path_v[i]);
	}
	
	
	/*
	 * Comportement selon AND et OR
	 */
	if (opt_and == true) {	/* AND */
		result = EXIT_SUCCESS;
		/* des qu'on en a un de FAILURE, on met en failure, et on sors */
		for (i = 0; i < opt_path_c; i++) {
			wait(&returnVal);
			if (WIFEXITED(returnVal))
				if (WEXITSTATUS(returnVal) == EXIT_FAILURE) {
					result = EXIT_FAILURE;
					break;
				}
		}
	}
	else { 					/* OR */
		result = EXIT_FAILURE;
		/* des qu'on en a un de SUCCESS, on met en succès, et on sors */
		for (i = 0; i < opt_path_c; i++) {
			wait(&returnVal);
			if (WIFEXITED(returnVal))
				if (WEXITSTATUS(returnVal) == EXIT_SUCCESS) {
					result = EXIT_SUCCESS;
					break;
				}
		}
	}
	/* ****************************** */
	
	/*
	 * Comportement selon KILL / CC ou rien
	 */
	if (opt_cc == true) {
		
		if (opt_kill == true) {
			for (i = 0; i < opt_path_c; i++) {
				kill(processes[i], 9); /* SIGKILL */
			}
		}
		else {
			/* rien, on retourne, juste (return en fin de fonction) */
		}
		
	}
	else {
		/* on attends tout, même si on est sûr de la réponse */
		for(; i < opt_path_c; i++) {
			wait(NULL);
		}
	}
	
	
	free(processes);
	return result;
}
