/*!
  \file common.h
  \brief define et méthode de debug
*/

#ifndef _COMMON_H_
#define _COMMON_H_

/*!
  \def MAXLINE
  \brief le nombre de lignes max
*/
#define MAXLINE    1024

/*!
  \def MAXARGS
  \brief Le nombre d'args max
*/
#define MAXARGS    20

/*!
  \def MAXCMDS
  \brief le nombre max de commandes possibles pour les pipes
*/
#define MAXCMDS    10

/*!
  \def ANSI_COLOR_BLACK
  \brief couleur: noir
*/
#define ANSI_COLOR_BLACK        "\033[30m"

/*!
  \def ANSI_COLOR_RED
  \brief couleur: rouge
*/
#define ANSI_COLOR_RED          "\033[31m"

/*!
  \def ANSI_COLOR_GREEN
  \brief couleur: vert
*/
#define ANSI_COLOR_GREEN        "\033[32m"

/*!
  \def ANSI_COLOR_YELLOW
  \brief couleur: jaune
*/
#define ANSI_COLOR_YELLOW       "\033[33m"

/*!
  \def ANSI_COLOR_BLUE
  \brief couleur: bleu
*/
#define ANSI_COLOR_BLUE         "\033[34m"

/*!
  \def ANSI_COLOR_MAGENTA
  \brief couleur: magentas
*/
#define ANSI_COLOR_MAGENTA      "\033[35m"

/*!
  \def ANSI_COLOR_CYAN
  \brief couleur: cyan
*/
#define ANSI_COLOR_CYAN         "\033[36m"

/*!
  \def ANSI_COLOR_WHITE
  \brief couleur: blanc
*/
#define ANSI_COLOR_WHITE        "\033[37m"

/*!
  \def ANSI_COLOR_BOLDBLACK
  \brief text en gras et text en noir
*/
#define ANSI_COLOR_BOLDBLACK    "\033[1m\033[30m"

/*!
  \def ANSI_COLOR_BOLDRED
  \brief  text en gras et text en rouge
*/
#define ANSI_COLOR_BOLDRED      "\033[1m\033[31m"

/*!
  \def ANSI_COLOR_BOLDGREEN
  \brief  text en gras et text en vert
*/
#define ANSI_COLOR_BOLDGREEN    "\033[1m\033[32m"

/*!
  \def ANSI_COLOR_BOLDYELLOW
  \brief text en gras et text en jaune
*/
#define ANSI_COLOR_BOLDYELLOW   "\033[1m\033[33m"

/*!
  \def ANSI_COLOR_BOLDBLUE
  \brief  text en gras et text en bleu
*/
#define ANSI_COLOR_BOLDBLUE     "\033[1m\033[34m"

/*!
  \def ANSI_COLOR_BOLDMAGENTA
  \brief  text en gras et text en magenta
*/
#define ANSI_COLOR_BOLDMAGENTA  "\033[1m\033[35m"

/*!
  \def ANSI_COLOR_BOLDCYAN
  \brief  text en gras et text en cyan
*/
#define ANSI_COLOR_BOLDCYAN     "\033[1m\033[36m"

/*!
  \def ANSI_COLOR_BOLDWHITE
  \brief text en gras et text en blanc
*/
#define ANSI_COLOR_BOLDWHITE    "\033[1m\033[37m"

/*!
  \def BOLD
  \brief text en gras
*/
#define BOLD "\033[00;01m"

/*!
  \def NORM
  \brief texte normal
*/
#define NORM "\033[00;00m"

/*!
  \brief permet de savoir si le mode verbose est activé
*/
int verbose;

/*!
  \brief affiche le chemin absolue du répertoire courant
*/
char* print_path;

/*!
  \fn unix_error(char *msg)
  \brief  affiche les message d'erreur unix
  \param msg
*/
extern void unix_error(char *msg);

/*!
  \fn send_verbose_message (const char* message)
  \brief si verbose = 1, affiche un message
  \param message
*/
extern void send_verbose_message(const char* message);

#endif
