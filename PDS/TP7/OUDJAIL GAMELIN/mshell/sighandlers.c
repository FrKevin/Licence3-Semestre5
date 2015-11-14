/* mshell - a job manager */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


#include "jobs.h"
#include "common.h"
#include "sighandlers.h"

/*
* wrapper for the sigaction function
*/
int sigaction_wrapper(int signum, handler_t * handler) {
  struct sigaction st_sigaction;
  int status;
  sigemptyset(&st_sigaction.sa_mask);
  st_sigaction.sa_handler = handler;
  status = sigaction(signum, &st_sigaction, NULL);
  if( status == -1){
    perror("sigaction failure !");
    exit(EXIT_FAILURE);
  }
  return status;
}

/*
* sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
*     a child job terminates (becomes a zombie), or stops because it
*     received a SIGSTOP or SIGTSTP signal. The handler reaps all
*     available zombie children
ATENTION WAIT !!! a verifier argument jobs miltiple
*/
void sigchld_handler(int sig) {
  int status;
  pid_t pid;

  if (verbose)
    printf("sigchld_handler: entering\n");

  pid = waitpid(-1, &status, WNOHANG|WUNTRACED);
  if(pid == -1){
    perror("wait failure !");
    exit(EXIT_FAILURE);
  }

  if(WIFEXITED(status) || WIFSIGNALED(status)){

  }
  if(WIFSTOPPED(status)){

  }

  if (verbose)
    printf("sigchld_handler: exiting\n");

  return;
}

/*
* sigint_handler - The kernel sends a SIGINT to the shell whenver the
*    user types ctrl-c at the keyboard.  Catch it and send it along
*    to the foreground job.
*/
void sigint_handler(int sig) {
  pid_t job_current;

  if (verbose)
    printf("sigint_handler: entering\n");

  job_current = jobs_fgpid();
  if(sig == SIGINT && job_current > 0){
    kill(job_current, sig);
    if (verbose)
      printf("Send to %i the SIGINT signal.\n", job_current);
  }

  if (verbose)
    printf("sigint_handler: exiting\n");

  return;
}

/*
* sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
*     the user types ctrl-z at the keyboard. Catch it and suspend the
*     foreground job by sending it a SIGTSTP.
*/
void sigtstp_handler(int sig) {
  pid_t job_current;

  if (verbose){
    printf("sigtstp_handler: entering\n");
  }

  job_current = jobs_fgpid();
  if(sig == SIGINT && job_current > 0){
    kill(job_current, sig);
    if (verbose)
      printf("Send to %i the SIGINT signal.\n", job_current);
  }
  printf("sigtstp_handler : To be implemented\n");

  if (verbose)
    printf("sigtstp_handler: exiting\n");

  return;
}
