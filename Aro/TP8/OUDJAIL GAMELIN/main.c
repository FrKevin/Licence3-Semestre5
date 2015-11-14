#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/graphe.h"

tGraphe init(char * const file){
  tGraphe graphe;
  if (argc<2) {
    halt("Usage : %s FichierGraphe\n", file);
  }
  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  argv[1]);
  return tGraphe
}

void parcousLargeur(tGraphe graphe){

}

int main(int argc, char const *argv[]) {
    tGraphe graphe;
    graphe = init();

  exit(EXIT_SUCCESS);
}
