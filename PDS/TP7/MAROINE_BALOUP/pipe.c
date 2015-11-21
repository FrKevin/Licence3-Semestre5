/* mshell - a job manager */

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

void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
  int **tube;
  int *pid = malloc(sizeof(int)*nbcmd);

  printf("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
  if(nbcmd <2) {
    perror("Nombre d'arguments insufisant");
    exit(EXIT_FAILURE);
  }

  tube = malloc(sizeof(int*)*(nbcmd-1));

  /* Nombre de commandes = 2*/
  if(nbcmd == 2) {

    /* Premier processus */
    switch((pid[0] = fork())) {
      case 0 :
        tube[0] = malloc(sizeof(int)*2);
        if(pipe(tube[0]) == -1) {
          perror("Erreur création de pipe");
          exit(EXIT_FAILURE);
        }
        close(tube[0][1]);
        dup2(tube[0][0], STDIN_FILENO);
        close(tube[0][0]);
        execvp(cmds[0][0], cmds[0]);
        perror("Erreur exécution processus");
        exit(EXIT_FAILURE);

      case -1 :
        perror("Erreur création processus");
        exit(EXIT_FAILURE);

      default :
        break;
    }

    /* Second processus */
    switch(pid[1] = fork()) {
      case 0 :
        close(tube[0][0]);
        dup2(tube[0][1], STDOUT_FILENO);
        close(tube[0][1]);
        execvp(cmds[1][0], cmds[1]);
        perror("Erreur exécution processus");
        exit(EXIT_FAILURE);
      case -1 :
        perror("Erreur création de processus");
        exit(EXIT_FAILURE);
      default :
        break;
    }
    free(tube[0]);

    wait(NULL);
    wait(NULL);
  } /* Fin nombre de commandes = 2*/

  /* Nombre de commandes = 3*/
  else if(nbcmd == 3) {

    /* Premier processus */
    switch((pid[0] = fork())) {
      case 0 :

        /* Premier tube*/
        tube[0] = malloc(sizeof(int)*2);
        if(pipe(tube[0]) == -1) {
          perror("Erreur création de pipe");
          exit(EXIT_FAILURE);
        }
        close(tube[0][1]);
        dup2(tube[0][0], STDIN_FILENO);
        close(tube[0][0]);

        execvp(cmds[0][0], cmds[0]);
        perror("Erreur exécution processus");
        exit(EXIT_FAILURE);
      default :
        break;
    }

    /* Second processus */
    switch(pid[1] = fork()) {
      case 0 :
        /* Premier tube */
        close(tube[0][0]);

        /* Second tube */
        tube[1] = malloc(sizeof(int)*2);
        if(pipe(tube[1]) == -1) {
          perror("Erreur création de pipe");
          exit(EXIT_FAILURE);
        }
        close(tube[1][1]);

        dup2(tube[1][0], STDIN_FILENO);

        execvp(cmds[1][0], cmds[1]);
        perror("Erreur exécution processus");
        exit(EXIT_FAILURE);

      case -1 :
        perror("Erreur création de processus");
        exit(EXIT_FAILURE);

      default :
        break;
    }

    /* Troisième processus */
    switch(pid[2] = fork()) {
      case 0 :
        /* Premier tube */
        close(tube[0][0]);
        close(tube[0][1]);

        /* Second tube */
        close(tube[1][0]);
        dup2(tube[1][1], STDOUT_FILENO);

        close(tube[1][1]);

        execvp(cmds[2][0], cmds[2]);
        perror("Erreur exécution processus");
        exit(EXIT_FAILURE);

      case -1 :
        perror("Erreur création de processus");
        exit(EXIT_FAILURE);

      default :
        break;
    }


    free(tube[0]);
    free(tube[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);
  } /* Fin nombre de commandes = 3*/

  free(pid);
  free(tube);
  return;
}
