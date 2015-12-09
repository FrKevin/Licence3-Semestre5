/*!
  \file common.h
*/

#ifndef _COMMON_H_
#define _COMMON_H_

/*!
  \def MAXLINE
  \brief Max line size
*/
#define MAXLINE    1024

/*!
  \def MAXARGS
  \brief Max args on a command line
*/
#define MAXARGS    20

/*!
  \def MAXCMDS
  \brief Max commands in a command pipeline
*/
#define MAXCMDS    10

/*!
  \def ANSI_COLOR_BLACK
  \brief Black color
*/
#define ANSI_COLOR_BLACK        "\033[30m"

/*!
  \def ANSI_COLOR_RED
  \brief Red color
*/
#define ANSI_COLOR_RED          "\033[31m"

/*!
  \def ANSI_COLOR_GREEN
  \brief Green color
*/
#define ANSI_COLOR_GREEN        "\033[32m"

/*!
  \def ANSI_COLOR_YELLOW
  \brief Yellow color
*/
#define ANSI_COLOR_YELLOW       "\033[33m"

/*!
  \def ANSI_COLOR_BLUE
  \brief Blue color
*/
#define ANSI_COLOR_BLUE         "\033[34m"

/*!
  \def ANSI_COLOR_MAGENTA
  \brief Magenta color
*/
#define ANSI_COLOR_MAGENTA      "\033[35m"

/*!
  \def ANSI_COLOR_CYAN
  \brief Cyan color
*/
#define ANSI_COLOR_CYAN         "\033[36m"

/*!
  \def ANSI_COLOR_WHITE
  \brief White color
*/
#define ANSI_COLOR_WHITE        "\033[37m"

/*!
  \def ANSI_COLOR_BOLDBLACK
  \brief Bold Text and Black color
*/
#define ANSI_COLOR_BOLDBLACK    "\033[1m\033[30m"

/*!
  \def ANSI_COLOR_BOLDRED
  \brief Bold Text and Rred color
*/
#define ANSI_COLOR_BOLDRED      "\033[1m\033[31m"

/*!
  \def ANSI_COLOR_BOLDGREEN
  \brief Bold Text and green color
*/
#define ANSI_COLOR_BOLDGREEN    "\033[1m\033[32m"

/*!
  \def ANSI_COLOR_BOLDYELLOW
  \brief Bold Text and yellow color
*/
#define ANSI_COLOR_BOLDYELLOW   "\033[1m\033[33m"

/*!
  \def ANSI_COLOR_BOLDBLUE
  \brief Bold Text and blue color
*/
#define ANSI_COLOR_BOLDBLUE     "\033[1m\033[34m"

/*!
  \def ANSI_COLOR_BOLDMAGENTA
  \brief Bold Text and magenta color
*/
#define ANSI_COLOR_BOLDMAGENTA  "\033[1m\033[35m"

/*!
  \def ANSI_COLOR_BOLDCYAN
  \brief Bold Text and cyan color
*/
#define ANSI_COLOR_BOLDCYAN     "\033[1m\033[36m"

/*!
  \def ANSI_COLOR_BOLDWHITE
  \brief Bold Text and white color
*/
#define ANSI_COLOR_BOLDWHITE    "\033[1m\033[37m"

/*!
  \def BOLD
  \brief Bold Text
*/
#define BOLD "\033[00;01m"

/*!
  \def NORM
  \brief Normal Text
*/
#define NORM "\033[00;00m"

/*!
  \brief If true, print additional output
*/
int verbose;

/*!
  \brief print the absolute pathname of the current working directory
*/
char* print_path;

/*!
  \fn unix_error (char *msg)
  \brief  print unix errno and the message
  \param message.
*/
extern void unix_error(char *msg);

/*!
  \fn send_verbose_message (const char* message)
  \brief if verbose = true, print additional output
  \param message.
*/
extern void send_verbose_message(const char* message);

#endif
