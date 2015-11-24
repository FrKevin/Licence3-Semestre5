/* mshell - a job manager */

#ifndef _SIGHANDLERS_H_
#define _SIGHANDLERS_H_

typedef void handler_t(int);

extern int sigaction_wrapper(int signum, handler_t * handler);
extern void sigchld_handler(int sig);
extern void sigint_handler(int sig);
extern void sigtstp_handler(int sig);
extern void sigquit_handler(int sig);

extern void locksignal(sigset_t* mask);
extern void unlocksignal(sigset_t* mask);

#endif
