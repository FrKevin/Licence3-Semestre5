  /* mshell - a job manager */
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe.h"

/*
 * UTILISER pipe2 ! voir Marc pour de plus ample informations
 */
void begin_work(int fd[MAXCMDS][2], pid_t* t_pid, char *cmds[MAXCMDS][MAXARGS]){
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
}

void midlle_work(int nbcmd, int fd[MAXCMDS][2], pid_t* t_pid, char *cmds[MAXCMDS][MAXARGS]){
  size_t i;
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
}

void end_work(pid_t* t_pid, int nbcmd, int fd[MAXCMDS][2], char *cmds[MAXCMDS][MAXARGS]){
  size_t i;
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
}

void close_all_pipe(int nbcmd, int fd[MAXCMDS][2]){
  size_t i;
  for(i = 0; i< nbcmd-1; i++){
    close(fd[i][0]);
    close(fd[i][1]);
  }
}

void wait_all_child(int nbcmd){
  size_t i;
  for(i = 0; i < nbcmd; i++){
    wait(NULL);
  }
}

/*
 * fd[0] lecture
 * fd[1] ecriture
 */
void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
  int fd[MAXCMDS][2];
  pid_t t_pid[MAXCMDS];

  begin_work(fd, t_pid, cmds);
  midlle_work(nbcmd, fd, t_pid, cmds);
  end_work(t_pid, nbcmd, fd, cmds);

  close_all_pipe(nbcmd, fd);
  wait_all_child(nbcmd);
}
