/*!
  \file pipe.h
  \brief definition d'un pipe
*/
#ifndef _PIPE_H_
#define _PIPE_H_

#include "common.h"

#define READ 0
#define WRITE 1


/**
 * \defgroup Pipe section, process communication
 *
 * This section talk about method to commicate between process
 */
/*@{*/


/**
  \fn void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg)
  \brief do_pipe est une methode qui permet de faire communiquer un ensemble de processus en redirigeant leurs sortit standart dans des tubes faisant le liens entre eux
   \param cmds : Liste de commandes avec leurs arguments
   \param nbcmd : Un entier representant le nombre de commande
   \param bg : Un arguments permettant de savoir si les commande sont en bg ou fg

   Les processus lancé sont gerer en parti par la boucle d'attente, et le sighandler avec SIG_CHILD

   \warning Cette fonctionnalité presente plusieurs bug, nottament dans l'attente des processus qui peut boucler (Ce bug a une frequence aleatoire)
 */
extern void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg);

/*@}*/
#endif
