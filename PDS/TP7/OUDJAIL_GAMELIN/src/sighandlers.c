/* mshell - a job manager */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#include <sys/types.h>
#include <unistd.h>


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
  st_sigaction.sa_flags = SA_RESTART;
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
	struct job_t *job;

  send_verbose_message("sigchld_handler: entering");

  pid = waitpid(-1, &status, WNOHANG|WUNTRACED);
  if(pid == -1){
    perror("wait failure !");
    exit(EXIT_FAILURE);
  }

  if(WIFEXITED(status) || WIFSIGNALED(status)){
    	jobs_deletejob(pid);
  }

  if(WIFSTOPPED(status)){
    job = jobs_getjobpid(pid);
    if (job != NULL) {
      job->jb_state = ST;
    }
  }

  send_verbose_message("sigchld_handler: exiting");
}

/*
* sigint_handler - The kernel sends a SIGINT to the shell whenver the
*    user types ctrl-c at the keyboard.  Catch it and send it along
*    to the foreground job.
*/
void sigint_handler(int sig) {
  pid_t job_current;

  send_verbose_message("sigint_handler: entering");

  while ((job_current = jobs_fgpid()) > 0) {
    /* boucle prenant en charge toutes les commandes d'un pipe */
    kill(job_current, SIGTERM);
    if (verbose) {
      printf("Send to %i the SIGTERM signal.\n", job_current);
    }
  }

  send_verbose_message("sigint_handler: exiting");
}

/*
* sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
*     the user types ctrl-z at the keyboard. Catch it and suspend the
*     foreground job by sending it a SIGTSTP.
*/
void sigtstp_handler(int sig) {
  pid_t fg_job_pid;
  struct job_t *fg_job;
  send_verbose_message("sigtstp_handler: entering");

  while ((fg_job_pid = jobs_fgpid()) > 0) {
		/* boucle prenant en charge toutes les commandes d'un pipe */
		fg_job = jobs_getjobpid(fg_job_pid);
		if (fg_job->jb_state != ST) {
			fg_job->jb_state = ST;
			kill(fg_job_pid, SIGSTOP);
			if (verbose) {
				printf("Send to %i the SIGTSTP signal.\n", fg_job_pid);
      }
		}
	}
  send_verbose_message("sigtstp_handler: exiting");
}

/*
 * This is a little tricky. Block SIGCHLD, SIGINT, and SIGTSTP
 * signals until we can add the job to the job list. This
 * eliminates some nasty races between adding a job to the job
 * list and the arrival of SIGCHLD, SIGINT, and SIGTSTP signals.
 */
void lock_signal(sigset_t *mask) {
	if (sigemptyset(mask) < 0)
		perror("sigemptyset error");
	if (sigaddset(mask, SIGCHLD))
		perror("sigaddset error");
	if (sigaddset(mask, SIGINT))
		perror("sigaddset error");

	if (sigprocmask(SIG_BLOCK, mask, NULL) < 0)
		perror("sigprocmask error");
}

void unlock_signal(sigset_t *mask) {
	sigprocmask(SIG_UNBLOCK, mask, NULL);
}
