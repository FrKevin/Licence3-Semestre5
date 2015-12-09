/*!
  \file jobs.h
  \brief jobs definition
*/
#ifndef _JOBS_H_
#define _JOBS_H_

#include <sys/types.h>
#include "common.h"

/*!
  \enum jstate
  \brief possible state
*/
enum jstate { UNDEF, BG, FG, ST };

/*!
  \struct job_t
  \brief The job struct
*/
struct job_t {
    pid_t jb_pid;               /*! \brief job PID */
    int jb_jid;                 /*! \brief job ID */
    int jb_state;               /*! \brief job state: UNDEF, BG, FG, or ST */
    char jb_cmdline[MAXLINE];   /*! \brief command line */
};


/*** Helper routines that manipulate the job list ***/

/*!
  \fn void jobs_clearjob(struct job_t *job)
  \brief Clear the entries in a job struct
  \param struct job_t *job.
*/
extern void jobs_clearjob(struct job_t *job);

/*!
  \fn void jobs_initjobs()
  \brief Initialize the job list
*/
extern void jobs_initjobs();

/*!
  \fn int jobs_maxjid()
  \brief Returns largest allocated job ID
*/
extern int jobs_maxjid();

/*!
  \fn int jobs_addjob(pid_t pid, int state, char *cmdline)
  \brief Add a job to the job list
  \return 1 if success and 0 if failure
*/
extern int jobs_addjob(pid_t pid, int state, char *cmdline);

/*!
  \fn int jobs_deletejob(pid_t pid)
  \brief Delete a job whose PID=pid from the job list
  \return 1 if success and 0 if failure
*/
extern int jobs_deletejob(pid_t pid);

/*!
  \fn pid_t jobs_fgpid()
  \brief Return PID of current foreground job, 0 if no such job
*/
extern pid_t jobs_fgpid();

/*!
  \fn struct job_t *jobs_getjobpid(pid_t pid)
  \brief Find a job (by PID) on the job list
*/
extern struct job_t *jobs_getjobpid(pid_t pid);

/*!
  \fn struct job_t *jobs_getjobjid(int jid)
  \brief Find a job (by JID) on the job list
*/
extern struct job_t *jobs_getjobjid(int jid);

/*!
  \fn send_signal_to_job(pid_t pid, int sig)
  \brief Send a sinal for job width pid or jid
*/
extern void send_signal_to_job(pid_t pid, int sig);

/*!
  \fn int jobs_pid2jid(pid_t pid)
  \brief Map process ID to job ID
  \return 0 if failure
*/
extern int jobs_pid2jid(pid_t pid);

/*!
  \fn struct job_t *jobs_getstoppedjob()
  \brief Return a stopped job
  \return NULL if any
*/
extern struct job_t *jobs_getstoppedjob();

/*!
  \fn void jobs_listjobs()
  \brief Print the job list
*/
extern void jobs_listjobs();

#endif
