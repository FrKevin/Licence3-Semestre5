#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../lib/graphe.h"
#include "color.h"
#include "graphe_visu_color.h"

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

void parcoursLargeur(tGraphe graphe, int sommet, char *outfile){
  tTabCouleurs couleurs;
  tFileSommets file;
  tNumeroSommet  xSommet;
  int entrer;
  file = fileSommetsAlloue();

  initCouleurs(graphe, couleurs, sommet);

  /* On défile tout en affichant */
  nettoyerFile(file);

 /* On enfile le premièr sommet choisi */
 fileSommetsEnfile(file, sommet);

  /* PArcours du graphe en largeur */
  while (!fileSommetsEstVide(file)) {
    graphe_visu_color(graphe, couleurs, outfile);
    xSommet =  fileSommetsDefile(file);
    traitementGraphe(graphe, xSommet, couleurs, file);
    couleurs[xSommet] = ROUGE;
    printf("Enter number: ");
    scanf("%d", &entrer);
  }
  graphe_visu_color(graphe, couleurs, outfile);

  /* On libère la mémoire */
  fileSommetsLibere(file);
}

int main(int argc, char *argv[]) {
  if (argc<4) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }
  tGraphe graphe;
  char * file = argv[1];
  graphe = init(argc, file);
  parcoursLargeur(graphe, atoi(argv[2]), argv[3]);
  exit(EXIT_SUCCESS);
}
