/* ------------------------------
   $Id: makeargv-main.c,v 1.2 2006/04/11 12:01:25 marquet Exp $
   ------------------------------------------------------------

   Squelette d'utilisation de makeargv

   Philippe Marquet, Apr 2006

*/

#include <unistd.h>
#include <stdio.h>
#include "makeargv.h"

int main (int argc, char *argv[]){
  int i;
  for(i = 0; i< argc; i++){
    char **cmdargv;
    makeargv(argv[i], " ", &cmdargv);
    /*
     * cmdargv[0] contient la commade a éxcécuter
     * cmdazrgv les paramètres de la commande
     */
     execvp(cmdargv[0], cmdazrgv);
  }
}
