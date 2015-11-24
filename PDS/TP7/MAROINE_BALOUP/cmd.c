/* mshell - a job manager */

#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jobs.h"


void do_help() {
    printf("available commands are:\n");
    printf(" exit - cause the shell to exit\n");
    printf(BOLD "\t exit" NORM " or " BOLD "Ctrl+D\n" NORM);
    printf(" jobs - display status of jobs in the current session\n");
    printf(BOLD "\t jobs\n" NORM);
    printf(" fg   - run a job identified by its pid or job id in the foreground\n");
    printf(BOLD "\t fg " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" bg   - run a job identified by its pid or job id in the background\n");
    printf(BOLD "\t bg " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" stop - stop a job identified by its pid or job id\n");
    printf(BOLD "\t stop " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" kill - kill a job identified by its pid or job id\n");
    printf(BOLD "\t kill " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" help - print this message\n");
    printf(BOLD "\t help\n" NORM);
    printf("\n");
    printf("ctrl-z and ctrl-c can be used to send a SIGTSTP and a SIGINT, respectively\n\n");
}

/* treat_argv - Determine pid or jobid and return the associated job structure */
struct job_t *treat_argv(char **argv) {
    struct job_t *jobp = NULL;

    /* Ignore command if no argument */
    if (argv[1] == NULL) {
        printf("%s command requires PID or %%jobid argument\n", argv[0]);
        return NULL;
    }

    /* Parse the required PID or %JID arg */
    if (isdigit((int) argv[1][0])) {
        pid_t pid = atoi(argv[1]);
        if (!(jobp = jobs_getjobpid(pid))) {
            printf("(%d): No such process\n", (int) pid);
            return NULL;
        }
    } else if (argv[1][0] == '%') {
        int jid = atoi(&argv[1][1]);
        if (!(jobp = jobs_getjobjid(jid))) {
            printf("%s: No such job\n", argv[1]);
            return NULL;
        }
    } else {
        printf("%s: argument must be a PID or %%jobid\n", argv[0]);
        return NULL;
    }

    return jobp;
}

/* waitfg - Block until process pid is no longer the foreground process */
void waitfg(pid_t pid) {
   struct job_t *j;
   sigset_t maskchld;
   sigset_t masknormal;

   j = jobs_getjobpid(pid);

   if (!j)
      return;

   /* maskchld initialization (no signal) */
   sigemptyset(&maskchld);
   /* Adding SIGCHLD signal to maskchld */
   sigaddset(&maskchld, SIGCHLD);
   /* Initialize masknormal with previous blocked signals, then block */
   /* all previous blocked signals and all signals in maskchld signals. */
   /* This call ensures that a SIGCHLD isn't caught by a sighandler */
   sigprocmask(SIG_BLOCK, &maskchld, &masknormal);

   while (j->jb_pid == pid && j->jb_state == FG) {
      /* Wait for a signal which isn't blocked in masknormal set, */
      /* ignoring mask previously sets by sigprocmask calls, */
      /* potentially catching some previous blocked signals */
      /* (i.e. blocked SIGCHLD) */
      sigsuspend(&masknormal);
   }

   /* Back to previous blocked signals only */
   sigprocmask(SIG_SETMASK, &masknormal, NULL);

   return;
}

/* do_fg - Execute the builtin fg command */
void do_fg(char **argv) {
	struct job_t* job;
	job = treat_argv(argv);
	if (job == NULL) return;
	kill(job->jb_pid, SIGCONT);
	job->jb_state = FG;
	waitfg(job->jb_pid);
    return;
}

/* do_bg - Execute the builtin bg command */
void do_bg(char **argv) {
	struct job_t* job;
	job = treat_argv(argv);
	if (job == NULL) return;
	
	if (job->jb_state == ST) {
		kill(job->jb_pid, SIGCONT);
		job->jb_state = BG;
	}
	
    return;
}

/* do_stop - Execute the builtin stop command */
void do_stop(char **argv) {
	struct job_t* job;
	job = treat_argv(argv);
	if (job == NULL) return;
	
    kill(job->jb_pid, SIGTSTP);
    /* The sighandler will set this current job state to ST */
    
    return;
}

/* do_kill - Execute the builtin kill command */
void do_kill(char **argv) {
	struct job_t* job;
	job = treat_argv(argv);
	if (job == NULL) return;
	kill(job->jb_pid, SIGCONT);
	kill(job->jb_pid, SIGINT);
	/* The sighandler will remove this current job from our job list */
    return;
}

/* do_exit - Execute the builtin exit command */
void do_exit() {
    
    kill(getpid(), 15);
    
    return;
}

/* do_jobs - Execute the builtin fg command */
void do_jobs() {
    
    jobs_listjobs();
    
    return;
}
