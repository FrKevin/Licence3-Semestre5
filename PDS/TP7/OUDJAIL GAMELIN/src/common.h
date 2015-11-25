/* mshell - a job manager */

#ifndef _COMMON_H_
#define _COMMON_H_

#define MAXLINE    1024         /* max line size                      */
#define MAXARGS    20           /* max args on a command line         */
#define MAXCMDS    10           /* max commands in a command pipeline */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BOLD "\033[00;01m"
#define NORM "\033[00;00m"

int verbose;                    /* if true, print additional output   */
char* print_path;                      /* = getcwd() */

extern void unix_error(char *msg);

/* Send message if verbose = 1*/
extern void send_verbose_message(const char* message);

#endif
