  /* mshell - a job manager */

#include <stdio.h>
#include <unistd.h>
#include "pipe.h"

void basiqueAlgo(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg){
  /* Impossible en c 98 int fd[nbcmd][2];*/
  int** fd;
  size_t i;
  pid_t * t_pid;

  /*
   * Initialisation de la matrice de pipe
   * 1 ) On allou nbcmd * sizeof(int*)
   * 2) Pour chaque commandes on allou 2 * sizeof(int)
   *  <=> fd[nbcmd][2];
   */
  fd = (int **)malloc(nbcmd * sizeof(int*));
  assert(fd != NULL)
  for(i = 0; i< nbcmd; i++){
    *fd = (int *) malloc(2 * sizeof(int));
    assert(*fd != NULL);
  }

  t_pid = (pid_t *) malloc(nbcmd * sizeof(pid_t));
  assert(t_pid != NULL );

  /* fils 1 -> cmd 1 */
  assert(pipe(fd[0]) != -1);
  switch ( t_pid[0] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
      close(fd[0][0]);
      dup2(STDOUT, fd[0][1]);
      close(fd[0][1])
      execvp(cmds[0][0], cmds[0]);
      exit(EXIT_FAILURE);
    break:
  }

  /* fils 2 -> cmd 2 */
  switch ( t_pid[1] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
      close(fd[0][1]);
      dup2(SDTIN, fd[0][0]);
      close(fd[0][0]);
      execvp(cmds[1][0], cmds[1]);
      exit(EXIT_FAILURE)
    break:
  }

  /* Algo du père */
  for( i = 0; i < nbcmd; i++){
    close(fd[i][0]);
    close(fd[i][1]);
  }


  for (i = 0; i < nbcmd; i++) {
    wait(NULL);
  }
  /* FREE */
  return;
}

/*
 * fd[0] lecture
 * fd[1] ecriture
 */
void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
    int fd[2];
    assert(pipe(fd) != -1);
    pid_t * t_pid;
    size_t i;
    t_pid = malloc(nbcmd);

    switch ( t_pid[0] == fork() ) {
      case -1:
        exit(EXIT_FAILURE);
      break;
      case 0: /* fils 1 -> cmd 1 */
        close(fd[0]);
        dup2(close(fd[1]));
        execvp(cmds[0], cmds[0]);
        exit(EXIT_FAILURE)
      break:
    }

    /* Algo du père */
    close(fd[0]);
    close(fd[1]);
    for (i = 0; i < nbcmd; i++) {
      wait(NULL);
    }
    return;
}
