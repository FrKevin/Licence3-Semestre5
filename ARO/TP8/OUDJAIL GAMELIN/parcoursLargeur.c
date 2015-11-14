#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/graphe.h"

/* Couleurs */
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

tGraphe init(int argc, char * file){
  tGraphe graphe;
  if (argc<2) {
    halt("Usage : %s FichierGraphe\n", file);
  }
  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  file);
  return graphe;
}

void parcousLargeur(tGraphe graphe, int sommet){
  size_t i;
  tTabCouleurs couleurs;
  tFileSommets file;
  int nSommets;
  int xSommet;

  nSommets = grapheNbSommets(graphe);
  file = fileSommetsAlloue();

  for (i = 0; i < nSommets; i++) {
    if( i != sommet ){
        couleurs[i] = BLEU;
    }
  }
  couleurs[sommet] = VERT;

  /* On défile tout en affichant */
 while (!fileSommetsEstVide()) {
   fileSommetsDefile(file);
 }

 /* On enfile le premièr sommet choisi */
 fileSommetsEnfile(file, sommet);

  while (!fileSommetsEstVide()) {
    xSommet =  fileSommetsDefile(file);
  }

  /* On libère la mémoire */
  fileSommetsLibere(file);
}

int main(int argc, char *argv[]) {
    tGraphe graphe;
    char * file = argv[1];
    graphe = init(argc, file);
    parcousLargeur(graphe, 0);

  exit(EXIT_SUCCESS);
}
