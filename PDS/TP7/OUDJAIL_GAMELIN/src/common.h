/* mshell - a job manager */

#ifndef _COMMON_H_
#define _COMMON_H_

#define MAXLINE    1024         /* max line size                      */
#define MAXARGS    20           /* max args on a command line         */
#define MAXCMDS    10           /* max commands in a command pipeline */

#define ANSI_COLOR_BLACK        "\033[30m"          /* Black */
#define ANSI_COLOR_RED          "\033[31m"          /* Red */
#define ANSI_COLOR_GREEN        "\033[32m"          /* Green */
#define ANSI_COLOR_YELLOW       "\033[33m"          /* Yellow */
#define ANSI_COLOR_BLUE         "\033[34m"          /* Blue */
#define ANSI_COLOR_MAGENTA      "\033[35m"          /* Magenta */
#define ANSI_COLOR_CYAN         "\033[36m"          /* Cyan */
#define ANSI_COLOR_WHITE        "\033[37m"          /* White */
#define ANSI_COLOR_BOLDBLACK    "\033[1m\033[30m"   /* Bold Black */
#define ANSI_COLOR_BOLDRED      "\033[1m\033[31m"   /* Bold Red */
#define ANSI_COLOR_BOLDGREEN    "\033[1m\033[32m"   /* Bold Green */
#define ANSI_COLOR_BOLDYELLOW   "\033[1m\033[33m"   /* Bold Yellow */
#define ANSI_COLOR_BOLDBLUE     "\033[1m\033[34m"   /* Bold Blue */
#define ANSI_COLOR_BOLDMAGENTA  "\033[1m\033[35m"   /* Bold Magenta */
#define ANSI_COLOR_BOLDCYAN     "\033[1m\033[36m"   /* Bold Cyan */
#define ANSI_COLOR_BOLDWHITE    "\033[1m\033[37m"   /* Bold White */

#define BOLD "\033[00;01m"
#define NORM "\033[00;00m"

int verbose;                    /* if true, print additional output   */
char* print_path;                      /* = getcwd() */

extern void unix_error(char *msg);

/* Send message if verbose = 1*/
extern void send_verbose_message(const char* message);

#endif
