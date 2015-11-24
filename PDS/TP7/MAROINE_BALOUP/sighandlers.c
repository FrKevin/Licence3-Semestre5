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
    struct sigaction st_siga;
    int status;
    sigemptyset(&st_siga.sa_mask);
    
	st_siga.sa_flags = SA_RESTART;
    st_siga.sa_handler = handler;
    status = sigaction(signum, &st_siga, NULL);

    if(status < 0 ) {
      perror("Erreur sigaction !");
      exit(EXIT_FAILURE);
    }

    return status;
}

/*
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children
 */
void sigchld_handler(int sig) {
	int status;
	pid_t pid;
	struct job_t *job;
  
  
    if (verbose)
        printf("sigchld_handler: entering\n");

	pid = waitpid(-1, &status, WNOHANG|WUNTRACED);
	if(pid == -1){
		if (verbose)
			perror("sigchld_handler, wait");
		return;
	}

	if(WIFEXITED(status) || WIFSIGNALED(status)){
		jobs_deletejob(pid);
	}
	if(WIFSTOPPED(status)){
		job = jobs_getjobpid(pid);
		job->jb_state = ST;
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
	struct job_t* job;

	if (verbose){
		printf("sigtstp_handler: entering\n");
	}

	job_current = jobs_fgpid();
	if(sig == SIGTSTP && job_current > 0){
		kill(job_current, sig);
		job = jobs_getjobpid(job_current);
		job->jb_state = ST;
		if (verbose)
			printf("Send to %i the SIGTSTP signal.\n", job_current);
	}
	
    if (verbose)
        printf("sigtstp_handler: exiting\n");

    return;
}







void locksignal(sigset_t* mask) {
	/*
	 * This is a little tricky. Block SIGCHLD, SIGINT, and SIGTSTP
	 * signals until we can add the job to the job list. This
	 * eliminates some nasty races between adding a job to the job
	 * list and the arrival of SIGCHLD, SIGINT, and SIGTSTP signals.
	 */

	if (sigemptyset(mask) < 0)
		perror("sigemptyset error");
	if (sigaddset(mask, SIGCHLD))
		perror("sigaddset error");
	if (sigaddset(mask, SIGINT))
		perror("sigaddset error");
	if (sigaddset(mask, SIGTSTP))
		perror("sigaddset error");
	if (sigprocmask(SIG_BLOCK, mask, NULL) < 0)
		perror("sigprocmask error");
}



void unlocksignal(sigset_t* mask) {
	sigprocmask(SIG_UNBLOCK, mask, NULL);
}
