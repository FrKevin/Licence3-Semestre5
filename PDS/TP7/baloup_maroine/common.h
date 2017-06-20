/* mshell - a job manager */

#ifndef _COMMON_H_
#define _COMMON_H_

#define MAXLINE    1024         /* max line size                      */
#define MAXARGS    20           /* max args on a command line         */
#define MAXCMDS    10           /* max commands in a command pipeline */


#define BOLD "\033[00;01m"
#define BOLD "\033[00;01m"
#define NORM "\033[00;00m"
#define YELLOW "\033[33;1m"
#define RED "\033[31;1m"
#define GREEN "\033[32;1m"
#define BLUE "\033[34;1m"
#define MAGENTA "\033[35;1m"
#define CYAN "\033[36;1m"

int verbose;                    /* if true, print additional output   */

extern void unix_error(char *msg);

#endif
