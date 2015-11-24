/* mshell - a job manager */

#define _GNU_SOURCE 

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pipe.h"
#include "sighandlers.h"
#include "jobs.h"
#include "cmd.h"

void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
	int **tube;
	pid_t *pids;
	/*pid_t pid;
	int status;*/
	int i;
	sigset_t mask;

	if(nbcmd <2) {
		perror("De commande insuffisante");
		exit(EXIT_FAILURE);
	}
	/* tableau des PID */
	pids = malloc(sizeof(pid_t)*nbcmd);
	
	/* initialisation des tubes */
	tube = malloc(sizeof(int*)*(nbcmd-1));
	for (i=0; i<nbcmd-1; i++) {
		tube[i] = malloc(sizeof(int)*2);
		if(pipe2(tube[i], O_CLOEXEC) != 0) {
			perror("Erreur création de pipe");
			exit(EXIT_FAILURE);
		}
	}
	
	locksignal(&mask);
	
	
	/* premier processus */
	switch((pids[0] = fork())) {
		case 0 :
			close(tube[0][0]);
			dup2(tube[0][1], STDOUT_FILENO);
			close(tube[0][1]);
			execvp(cmds[0][0], cmds[0]);
			perror("Erreur exécution processus");
			exit(EXIT_FAILURE);

		case -1:
			perror("Erreur création processus");
			exit(EXIT_FAILURE);
		
		default:
			jobs_addjob(pids[0], (bg == 1 ? BG : FG), cmds[0][0]);
    }
	
	/* processus intermédiaires */
	for (i=1; i<nbcmd-1; i++) {
		switch((pids[i] = fork())) {
			case 0 :
				/* pipe vers le suivant */
				close(tube[i][0]);
				dup2(tube[i][1], STDOUT_FILENO);
				close(tube[i][1]);
				/* pipe depuis le précédent */
				close(tube[i-1][1]);
				dup2(tube[i-1][0], STDIN_FILENO);
				close(tube[i-1][0]);
				
				execvp(cmds[i][0], cmds[i]);
				perror("Erreur exécution processus");
				exit(EXIT_FAILURE);

			case -1:
				perror("Erreur création processus");
				exit(EXIT_FAILURE);
		
			default:
				jobs_addjob(pids[i], (bg == 1 ? BG : FG), cmds[i][0]);
		}
	}
	
	/* dernier processus */
	switch(pids[nbcmd-1] = fork()) {
		case 0 :
			close(tube[nbcmd-2][1]);
			dup2(tube[nbcmd-2][0], STDIN_FILENO);
			close(tube[nbcmd-2][0]);
			execvp(cmds[nbcmd-1][0], cmds[nbcmd-1]);
			perror("Erreur exécution processus");
			exit(EXIT_FAILURE);
			
		case -1 :
			perror("Erreur création de processus");
			exit(EXIT_FAILURE);
		
		default:
			jobs_addjob(pids[nbcmd-1], (bg == 1 ? BG : FG), cmds[nbcmd-1][0]);
	}
	
	/* fermeture des pipes dans le processus père */
	for (i=0; i<nbcmd-1; i++) {
		close(tube[i][0]);
		close(tube[i][1]);
		free(tube[i]);
	}
	unlocksignal(&mask);
	
	printf(BOLD "\nWaiting for jobs ending ..." NORM "\n");
	
	/*
	while((pid = wait(&status)) > 0) {
		handle_job_ending(pid, status);
	}*/
	
	for (i=0; i<nbcmd; i++)
		waitfg(pids[i]);
	
	fflush(stdout);
	
	free(pids);
	
	
	
}
