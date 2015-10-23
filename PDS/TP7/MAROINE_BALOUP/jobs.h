/* mshell - a job manager */

#ifndef _JOBS_H_
#define _JOBS_H_

#include <sys/types.h>
#include "common.h"

enum jstate { UNDEF, BG, FG, ST };

struct job_t {                  /* The job struct */
    pid_t jb_pid;               /* job PID */
    int jb_jid;                 /* job ID [1, 2, ...] */
    int jb_state;               /* UNDEF, BG, FG, or ST */
    char jb_cmdline[MAXLINE];   /* command line */
};


/*** Helper routines that manipulate the job list ***/

/* clearjob - Clear the entries in a job struct */
extern void jobs_clearjob(struct job_t *job);

/* initjobs - Initialize the job list */
extern void jobs_initjobs();

/* maxjid - Returns largest allocated job ID */
extern int jobs_maxjid();

/* addjob - Add a job to the job list */
extern int jobs_addjob(pid_t pid, int state, char *cmdline);

/* deletejob - Delete a job whose PID=pid from the job list */
extern int jobs_deletejob(pid_t pid);

/* fgpid - Return PID of current foreground job, 0 if no such job */
extern pid_t jobs_fgpid();

/* getjobpid  - Find a job (by PID) on the job list */
extern struct job_t *jobs_getjobpid(pid_t pid);

/* getjobjid  - Find a job (by JID) on the job list */
extern struct job_t *jobs_getjobjid(int jid);

/* pid2jid - Map process ID to job ID */
extern int jobs_pid2jid(pid_t pid);

/*getstoppedjob - Return a stopped job if any  */
extern struct job_t *jobs_getstoppedjob();

/* listjobs - Print the job list */
extern void jobs_listjobs();

#endif
