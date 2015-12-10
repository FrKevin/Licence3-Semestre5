/*!
  \file jobs.h
  \brief definition d'un job
*/
#ifndef _JOBS_H_
#define _JOBS_H_

#include <sys/types.h>
#include "common.h"

/*!
  \enum jstate
  \brief les etats possibles d'un job
*/
enum jstate { UNDEF, BG, FG, ST };

/*!
  \struct job_t
  \brief la structure d'un job
*/
struct job_t {
    pid_t jb_pid;               /*! \brief le PID du job */
    int jb_jid;                 /*! \brief l'ID du job */
    int jb_state;               /*! \brief l'etat du job: UNDEF, BG, FG, or ST */
    char jb_cmdline[MAXLINE];   /*! \brief la commande */
};

/*!
  \fn void jobs_clearjob(struct job_t *job)
  \brief Supprime un job
  \param struct job_t *job.
*/
extern void jobs_clearjob(struct job_t *job);

/*!
  \fn void jobs_initjobs()
  \brief Initialise la liste de jobs
*/
extern void jobs_initjobs();

/*!
  \fn int jobs_maxjid()
  \brief retourne l'id maximal des jobs alloués
*/
extern int jobs_maxjid();

/*!
  \fn int jobs_addjob(pid_t pid, int state, char *cmdline)
  \brief Ajoute un job dans la liste des jobs
  \return 1 => OK  et  0 => erreur
*/
extern int jobs_addjob(pid_t pid, int state, char *cmdline);

/*!
  \fn int jobs_deletejob(pid_t pid)
  \brief Détruis un job avec son PID dans la liste des jobs
  \return 1 => OK  et  0 => erreur
*/
extern int jobs_deletejob(pid_t pid);

/*!
  \fn pid_t jobs_fgpid()
  \brief Retourne le job lancer en arrière plan
  \return 0 => si aucun job trouver
*/
extern pid_t jobs_fgpid();

/*!
  \fn struct job_t *jobs_getjobpid(pid_t pid)
  \brief Trouve un job avec un pid dans la liste des jobs
  \return 0 => si aucun job trouver
*/
extern struct job_t *jobs_getjobpid(pid_t pid);

/*!
  \fn struct job_t *jobs_getjobjid(int jid)
  \brief Trouve un job avec un jid dans la liste des jobs
  return 0 => si aucun job trouver
*/
extern struct job_t *jobs_getjobjid(int jid);

/*!
  \fn send_signal_to_job(pid_t pid, int sig)
  \brief Envoie un signal sur un job
*/
extern void send_signal_to_job(pid_t pid, int sig);

/*!
  \fn int jobs_pid2jid(pid_t pid)
  \brief recupere le jid d'un job en focntion de sont pid
  \return 0 si non trouver
*/
extern int jobs_pid2jid(pid_t pid);

/*!
  \fn struct job_t *jobs_getstoppedjob()
  \brief retourne un job dans l'état stop
  \return NULL if any
*/
extern struct job_t *jobs_getstoppedjob();

/*!
  \fn void jobs_listjobs()
  \brief affiche la liste des jobs
*/
extern void jobs_listjobs();

#endif
