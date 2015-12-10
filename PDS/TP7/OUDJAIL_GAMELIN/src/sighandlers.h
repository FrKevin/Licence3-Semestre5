/*!
  \file sighandlers.h
  \brief gestion des signaux
*/
#ifndef _SIGHANDLERS_H_
#define _SIGHANDLERS_H_


/**
 * \defgroup Sighandler, gestionnaire des signaux systeme
 *
 * Pour que l'utilisateur puisse interagir avec l'interpreteur, nous avons recours à des signaux (evenement)

 Ce module s'occupe de la gestion de ces derniers, il regroupe plusieur methode pour ce faire

 */
/*@{*/



typedef void handler_t(int);

/**
    \fn int sigaction_wrapper(int signum, handler_t * handler)
    \brief Cette fonction associe à un signaux une fonction de traitement
    \param signum : (int) signum represente le signal que l'ont veut associer
    \param handler : (handler_t) handler represente la fonction de traitement de ce signal
    \brief Pour ce faire on utilise l'appel systeme sigaction
*/
extern int sigaction_wrapper(int signum, handler_t * handler);

/**
    \fn void sigchld_handler(int sig)
     \brief Cette fonction est un handler qui permet de traiter le signal SIG_CHILD
    Il permet d'attendre le fils (mais ne bloque pas) et met à jour la liste de job
    \param sig : (int) sig represente le signal que l'ont veut associer, en l'occurence SIG_CHILD
*/
extern void sigchld_handler(int sig);

/**
    \fn void sigint_handler(int sig)
    \brief Cette fonction est un handler qui permet de traiter le signal SIG_INT
    Il permet d'envoyer le signal intteruption au proccessus courant (fg)
    \param sig : (int) sig represente le signal que l'ont veut associer, en l'occurence SIG_INT
*/
extern void sigint_handler(int sig);

/**
    \fn void sigtstp_handler(int sig)
    \brief Cette fonction est un handler qui permet de traiter le signal SIG_STP
    Il permet d'envoyer le signal stop au proccessus courant (fg)
    \param sig : (int) sigrepresente le signal que l'ont veut associer, en l'occurence SIG_STP
*/
extern void sigtstp_handler(int sig);

/** Non implementer
*/
extern void sigquit_handler(int sig);

/**
  \fn void lock_signal(sigset_t *mask)
  \brief Cette fonction permet de blocker les signaux SIG_CHILD, SIG_INT, SIG_STP
   \param mask : represente un mask, la fonction va l'initialiser avant de lui ajouter les differents signaux et de l'appliquer
 */
extern void lock_signal(sigset_t *mask);

/**
  \fn void unlock_signal(sigset_t *mask)
  \brief Cette fonction permet de debloquer les signaux qui sont dans le mask
  \param mask : represente le mask initialiser par lock_signal(sigset_t *)
 */
extern void unlock_signal(sigset_t *mask);

/*@}*/

#endif
