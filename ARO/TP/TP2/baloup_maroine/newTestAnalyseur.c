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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "include/graphe.h"
#include "include/graphe2visu.h"
#include "include/parcoursLargeur.h"

int main(int argc, char *argv[]) {

  tGraphe graphe;
  int depart = atoi(argv[2]);
  tTabCouleurs tabCouleurs;
  if (argc<4) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }

  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  argv[1]);

  parcoursLargeur(graphe, depart, tabCouleurs);

  graphe2visuCouleurs(graphe, argv[3], tabCouleurs);

  return 0;
}
