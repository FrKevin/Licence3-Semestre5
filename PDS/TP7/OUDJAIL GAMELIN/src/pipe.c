  /* mshell - a job manager */
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe.h"

void bas3iqueAlgoN(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg){
  int fd[MAXCMDS][2];
  size_t i;
  pid_t t_pid[MAXCMDS];

  /* fils 1 -> cmd 1 */
  assert(pipe(fd[0]) != -1);
  switch ( t_pid[0] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
      close(fd[0][0]);
      dup2(STDOUT_FILENO, fd[0][1]);
      close(fd[0][1]);
      execvp(cmds[0][0], cmds[0]);
      exit(EXIT_FAILURE);
    break;
  }

  for(i = 1; i < nbcmd -1; i++){
    assert(pipe(fd[i]) != -1);
    switch ( t_pid[i] == fork() ) {
      case -1:
        exit(EXIT_FAILURE);
      break;
      case 0:
        /* 0 => lecture 1 => ecriture */
        close(fd[i-1][1]);
        close(fd[i][0]);

        dup2(STDIN_FILENO, fd[i-1][0]);
        dup2(STDOUT_FILENO, fd[i][1]);

        close(fd[i-1][0]);
        close(fd[i][1]);

        execvp(cmds[0][0], cmds[0]);
        exit(EXIT_FAILURE);
      break;
    }
  }

  /* fils 3 -> cmd 3 */
  switch ( t_pid[nbcmd-1] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
    /* Ncmd - 3  for*/
      for( i = 0; i< nbcmd-3; i++){
        close(fd[i][0]);
        close(fd[i][1]);
      }


      /* Ncmd - 2 = 1*/
      close(fd[nbcmd-2][1]);
      dup2(STDIN_FILENO, fd[nbcmd-2][0]);
      close(fd[nbcmd-2][0]);

      execvp(cmds[1][0], cmds[1]);
      exit(EXIT_FAILURE);
    break;
  }

  for(i = 0; i< nbcmd-1; i++){
    close(fd[i][0]);
    close(fd[i][1]);
  }

  for(i = 0; i < nbcmd; i++){
    wait(NULL);
  }
}

void bas3iqueAlgoN3(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg){
  int fd[MAXCMDS][2];
  size_t i;
  pid_t t_pid[MAXCMDS];

  /* fils 1 -> cmd 1 */
  assert(pipe(fd[0]) != -1);
  switch ( t_pid[0] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
      close(fd[0][0]);
      dup2(STDOUT_FILENO, fd[0][1]);
      close(fd[0][1]);
      execvp(cmds[0][0], cmds[0]);
      exit(EXIT_FAILURE);
    break;
  }

  /* 2e */
  assert(pipe(fd[1]) != -1);
  switch ( t_pid[1] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
      /* 0 => lecture 1 => ecriture */
      close(fd[0][1]);
      close(fd[1][0]);

      dup2(STDIN_FILENO, fd[0][0]);
      dup2(STDOUT_FILENO, fd[1][1]);

      close(fd[0][0]);
      close(fd[1][1]);

      execvp(cmds[0][0], cmds[0]);
      exit(EXIT_FAILURE);
    break;
  }

  /* fils 3 -> cmd 3 */
  switch ( t_pid[2] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
    /* Ncmd - 3  for*/
      close(fd[0][0]);
      close(fd[0][1]);

      /* Ncmd - 2 = 1*/
      close(fd[1][1]);
      dup2(STDIN_FILENO, fd[1][0]);
      close(fd[1][0]);

      execvp(cmds[1][0], cmds[1]);
      exit(EXIT_FAILURE);
    break;
  }

  for(i = 0; i< 2; i++){
    close(fd[i][0]);
    close(fd[i][1]);
  }

  for(i = 0; i < nbcmd; i++){
    wait(NULL);
  }
}

void basiqueAlgo(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg){
  /* Impossible en c 98 int fd[nbcmd][2];*/
  int fd[MAXCMDS][2];
  size_t i;
  pid_t t_pid[MAXCMDS];

  /*
   * Initialisation de la matrice de pipe
   * 1 ) On allou nbcmd * sizeof(int*)
   * 2) Pour chaque commandes on allou 2 * sizeof(int)
   *  <=> fd[nbcmd][2];
   */

  /* fils 1 -> cmd 1 */
  assert(pipe(fd[0]) != -1);
  switch ( t_pid[0] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
      close(fd[0][0]);
      dup2(STDOUT_FILENO, fd[0][1]);
      close(fd[0][1]);
      execvp(cmds[0][0], cmds[0]);
      exit(EXIT_FAILURE);
    break;
  }

  /* fils 2 -> cmd 2 */
  switch ( t_pid[1] == fork() ) {
    case -1:
      exit(EXIT_FAILURE);
    break;
    case 0:
      close(fd[0][1]);
      dup2(STDIN_FILENO, fd[0][0]);
      close(fd[0][0]);
      execvp(cmds[1][0], cmds[1]);
      exit(EXIT_FAILURE);
    break;
  }

  /* Algo du père */
  for( i = 0; i < nbcmd; i++){
    close(fd[i][0]);
    close(fd[i][1]);
  }


  for (i = 0; i < nbcmd; i++) {
    wait(NULL);
  }

  return;
}

/*
 * fd[0] lecture
 * fd[1] ecriture
 */
void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
  basiqueAlgo(cmds, nbcmd, bg);
}
