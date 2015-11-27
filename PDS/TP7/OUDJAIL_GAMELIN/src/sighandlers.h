/* mshell - a job manager */

#ifndef _SIGHANDLERS_H_
#define _SIGHANDLERS_H_

typedef void handler_t(int);

extern int sigaction_wrapper(int signum, handler_t * handler);
extern void sigchld_handler(int sig);
extern void sigint_handler(int sig);
extern void sigtstp_handler(int sig);
extern void sigquit_handler(int sig);

extern void lock_signal(sigset_t *mask);
extern void unlock_signal(sigset_t *mask);

#endif
