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
#include <assert.h>

#include "pipe.h"
#include "jobs.h"
#include "cmd.h"

static void general_work(char *cmds[MAXCMDS][MAXARGS], int fd[MAXCMDS][2], pid_t *t_pid, int nbcmd, int bg) {
	size_t i;
	for(i = 0; i < nbcmd -1; i++){
	  assert(pipe2(fd[i], O_CLOEXEC) != -1); if (verbose) printf("Create pipe (%d)\n", (int)i);
	  switch (t_pid[i] = fork()) {
	    case -1:
	      exit(EXIT_FAILURE);
	    break;
	    case 0:
	      if (i > 0) {
	        if(verbose) {
	          printf("Child : Close pipe (i -1) : %d in WRITE \n", (int)i-1);
	          printf("Child : Close pipe (i -1) : %d in READ \n", (int)i-1);
	        }
	        close(fd[i-1][WRITE]);
	        dup2(fd[i-1][READ], STDIN_FILENO);
	        close(fd[i-1][READ]);
	      }
	      if(verbose) {
	        printf("Child : Close pipe i : %d in READ \n", (int)i);
	        printf("Child : Close pipe i : %d in WRITE \n", (int)i);
	      }
	      close(fd[i][READ]);
	      dup2(fd[i][WRITE], STDOUT_FILENO);
	      close(fd[i][WRITE]);
	      execvp(cmds[i][0], cmds[i]);
	      exit(EXIT_FAILURE);
	    break;
	    default :

	      close(fd[i][WRITE]);
	      if (i > 0) {
	        close(fd[i-1][READ]); if (verbose) printf("Father : Close pipe (i -1) : %d in READ \n", (int)i-1);

	      }
	      if(verbose) {
	        printf("Father : Close pipe i : %d in WRITE \n", (int)i);
	      }
	      jobs_addjob(t_pid[i], (bg == 1 ? BG : FG), cmds[i][0]);
	  }
	}
}

static void end_work(char *cmds[MAXCMDS][MAXARGS], int fd[MAXCMDS][2], pid_t *t_pid, int nbcmd, int bg) {
	size_t last_pipe = nbcmd - 2;
	size_t last_cmd = nbcmd - 1;
	switch (t_pid[last_cmd] = fork()) {
	  case -1:
	    exit(EXIT_FAILURE);
	  break;
	  case 0:
	    if (verbose) {
	      printf("End Work Child : Close last pipe (%d) in WRITE \n", (int)last_pipe);
	      printf("End Work Child : Close last pipe (%d) in READ \n", (int)last_pipe);
	    }
	    close(fd[last_pipe][WRITE]);
	    dup2(fd[last_pipe][READ], STDIN_FILENO);
	    close(fd[last_pipe][READ]);

	    execvp(cmds[last_cmd][0], cmds[last_cmd]);
	    exit(EXIT_FAILURE);
	  break;
	  default :
	    if (verbose) {
	      printf("End Work Father : Close last pipe (%d) in READ \n", (int)last_pipe);
	    }
	    close(fd[last_pipe][READ]);
	    jobs_addjob(t_pid[last_cmd], (bg == 1 ? BG : FG), cmds[last_cmd][0]);
	}
}

static void wait_all_child(pid_t *t_pid, int nbcmd){
	size_t i;
	for(i = 0; i < nbcmd; i++) {
	  waitfg(t_pid[i]);
	}
}

void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
	int fd[MAXCMDS][2];
	pid_t t_pid[MAXCMDS];
	if (nbcmd > MAXCMDS) {
	  fprintf(stderr, "%s%d\n", "Nb de commande <= ", MAXCMDS);
	}

	general_work(cmds, fd, t_pid, nbcmd, bg);
	end_work(cmds, fd, t_pid, nbcmd, bg);
	wait_all_child(t_pid, nbcmd);
}
