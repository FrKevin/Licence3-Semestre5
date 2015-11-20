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

void nettoyerFile(tFileSommets file){
  while (!fileSommetsEstVide(file)) {
    fileSommetsDefile(file);
  }
}

void initCouleurs(tGraphe graphe, tTabCouleurs couleurs, int sommet) {
  int nSommets = grapheNbSommets(graphe);
  for (size_t i = 0; i < nSommets; i++) {
    if( i != sommet ){
        couleurs[i] = BLEU;
    }
  }
  couleurs[sommet] = VERT;
}

void traitementGraphe(tGraphe graphe,tNumeroSommet  xSommet, tTabCouleurs couleurs,  tFileSommets file){
  size_t i;
  int estOriente = grapheEstOriente(graphe);
  int nVoisins = estOriente ? grapheNbSuccesseursSommet(graphe, xSommet) : 	grapheNbVoisinsSommet(graphe, xSommet);
  tNumeroSommet sommetVoisinI;
  for(i =0 ; i< nVoisins;i++){
    sommetVoisinI = estOriente ? grapheSuccesseurSommetNumero(graphe, xSommet, i) : grapheVoisinSommetNumero(graphe, xSommet, i) ;
    if(couleurs[sommetVoisinI] == BLEU){
      couleurs[sommetVoisinI] = VERT;
      fileSommetsEnfile(file, sommetVoisinI);
    }
  }
}

void parcoursLargeur(tGraphe graphe, int sommet){
  tTabCouleurs couleurs;
  tFileSommets file;
  tNumeroSommet  xSommet;

  file = fileSommetsAlloue();

  initCouleurs(graphe, couleurs, sommet);

  /* On défile tout en affichant */
  nettoyerFile(file);

 /* On enfile le premièr sommet choisi */
 fileSommetsEnfile(file, sommet);

  /* PArcours du graphe en largeur */
  while (!fileSommetsEstVide(file)) {
    xSommet =  fileSommetsDefile(file);
    traitementGraphe(graphe, xSommet, couleurs, file);
    couleurs[xSommet] = ROUGE;
  }

  /* On libère la mémoire */
  fileSommetsLibere(file);
}

int main(int argc, char *argv[]) {
    tGraphe graphe;
    char * file = argv[1];
    graphe = init(argc, file);
    parcoursLargeur(graphe, 0);

  exit(EXIT_SUCCESS);
}
