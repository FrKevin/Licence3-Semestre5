/* mshell - a job manager */

#include <stdio.h>
#include <string.h>

#include "jobs.h"

#define MAXJOBS      16              /* max jobs at any point in time */
static struct job_t jobs[MAXJOBS];   /* the job list                  */

int nextjid = 1;                     /* next job ID to allocate       */


/*** Helper routines that manipulate the job list ***/

/* clearjob - Clear the entries in a job struct */
void jobs_clearjob(struct job_t *job) {
    job->jb_pid = 0;
    job->jb_jid = 0;
    job->jb_state = UNDEF;
    job->jb_cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void jobs_initjobs() {
    int i;

    for (i = 0; i < MAXJOBS; i++)
        jobs_clearjob(&jobs[i]);
}

/* maxjid - Returns largest allocated job ID */
int jobs_maxjid() {
    int i, max = 0;

    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jb_jid > max)
            max = jobs[i].jb_jid;
    return max;
}

/* addjob - Add a job to the job list */
int jobs_addjob(pid_t pid, int state, char *cmdline) {
    int i;

    if (pid < 1)
        return 0;

    for (i = 0; i < MAXJOBS; i++) {
        if (jobs[i].jb_pid == 0) {
            jobs[i].jb_pid = pid;
            jobs[i].jb_state = state;
            jobs[i].jb_jid = nextjid++;
            if (nextjid > MAXJOBS)
                nextjid = 1;
            strcpy(jobs[i].jb_cmdline, cmdline);
            if (verbose) {
                printf("Added job [%d] %d %s\n", jobs[i].jb_jid, (int) jobs[i].jb_pid,
                       jobs[i].jb_cmdline);
            }
            return 1;
        }
    }
    printf("Tried to create too many jobs\n");
    return 0;
}

/* deletejob - Delete a job whose PID=pid from the job list */
int jobs_deletejob(pid_t pid) {
    int i;

    if (pid < 1)
        return 0;

    for (i = 0; i < MAXJOBS; i++) {
        if (jobs[i].jb_pid == pid) {
            jobs_clearjob(&jobs[i]);
            nextjid = jobs_maxjid(jobs) + 1;
            return 1;
        }
    }
    return 0;
}

/* fgpid - Return PID of current foreground job, 0 if no such job */
pid_t jobs_fgpid() {
    int i;

    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jb_state == FG)
            return jobs[i].jb_pid;
    return 0;
}

/* getjobpid  - Find a job (by PID) on the job list */
struct job_t *jobs_getjobpid(pid_t pid) {
    int i;

    if (pid < 1)
        return NULL;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jb_pid == pid)
            return &jobs[i];
    return NULL;
}

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *jobs_getjobjid(int jid) {
    int i;

    if (jid < 1)
        return NULL;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jb_jid == jid)
            return jobs + i;
    return NULL;
}

/* pid2jid - Map process ID to job ID */
int jobs_pid2jid(pid_t pid) {
    int i;

    if (pid < 1)
        return 0;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jb_pid == pid) {
            return jobs[i].jb_jid;
        }
    return 0;
}


/*getstoppedjob - Return a stopped job if any  */
struct job_t *jobs_getstoppedjob() {
    int i;

    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jb_state == ST)
            return &jobs[i];
    return NULL;
}

/* listjobs - Print the job list */
void jobs_listjobs() {
    int i;

    for (i = 0; i < MAXJOBS; i++) {
        if (jobs[i].jb_pid != 0) {
            printf("[%d] (%d) ", jobs[i].jb_jid, (int) jobs[i].jb_pid);
            switch (jobs[i].jb_state) {
            case BG:
                printf("Running ");
                break;
            case FG:
                printf("Foreground ");
                break;
            case ST:
                printf("Stopped ");
                break;
            default:
                printf("listjobs: Internal error: job[%d].state=%d ", i, jobs[i].jb_state);
            }
            printf("%s", jobs[i].jb_cmdline);
        }
    }
}
