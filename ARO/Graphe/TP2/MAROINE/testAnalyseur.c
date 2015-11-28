/**********************************************************************
 *testAnalyseur.c
 *
 *  (FranÃ§ois lemaire)  <Francois.Lemaire@lifl.fr>
 * Time-stamp: <2010-10-06 15:06:29 lemaire>
 ***********************************************************************/

/* Ce program prend un nom de graphe en entrÃ©e, le charge,
   et l'affiche de faÃ§on dÃ©taillÃ©e.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/graphe.h"

int main(int argc, char *argv[]) {

  tGraphe graphe;

  if (argc<2) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }


  graphe = grapheAlloue();

  grapheChargeFichier(graphe,  argv[1]);
  grapheAffiche(graphe);

  grapheLibere(graphe);

  exit(EXIT_SUCCESS);
}
