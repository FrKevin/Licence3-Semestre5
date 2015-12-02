#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/graphe.h"
#include "color.h"
/*
* Ecrit sur la sortie d'erreur
* @param : int cond: la condition d'assertion
* @param : char * message: le message a afficher
* @return
*/
void assert_message(int cond, char * message){
 if(!cond){
   fprintf(stderr, "%s\n", message);
   perror(NULL);
   exit(EXIT_FAILURE);
 }
}

tGraphe init(int argc, char * file){
  tGraphe graphe;
  if (argc<2) {
    halt("Usage : %s FichierGraphe\n", file);
  }
  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  file);
  return graphe;
}

void checkgraphe(tGraphe graphe){
  assert_message(grapheEstOriente(graphe) == 0, "This graphe is oriented.");
}

void initCouleurs(tGraphe graphe, tTabCouleurs couleurs, tNumeroSommet sommet) {
  int nSommets = grapheNbSommets(graphe);
  for (size_t i = 0; i < nSommets; i++) {
    if( i != sommet ){
      couleurs[i] = BLEU;
    }
  }
  couleurs[sommet] = VERT;
}

void nettoyerFile(tFileSommets file){
  while (!fileSommetsEstVide(file)) {
    fileSommetsDefile(file);
  }
}

void traitement_voisin(tGraphe graphe,tNumeroSommet xSommet, tTabCouleurs couleurs,  tFileSommets file, int d[MAX_SOMMETS], tNumeroSommet pred[MAX_SOMMETS]){
  size_t i;
  int nVoisins = grapheNbVoisinsSommet(graphe, xSommet);
  tNumeroSommet sommetVoisinI;
  for(i =0 ; i< nVoisins;i++){
    sommetVoisinI = grapheVoisinSommetNumero(graphe, xSommet, i) ;
    if(couleurs[sommetVoisinI] == BLEU){
      couleurs[sommetVoisinI] = VERT;
      fileSommetsEnfile(file, sommetVoisinI);
      d[sommetVoisinI] = d[xSommet] + 1;
      pred[sommetVoisinI] = xSommet;
    }
  }
}
void print_array_pred(tGraphe graphe, tNumeroSommet array[MAX_SOMMETS], int nSommet){
  tNomSommet nomSommet;
  tNomSommet nomSommetPred;
  for (size_t i = 0; i < nSommet; i++) {
    grapheRecupNomSommet(graphe, i,nomSommet);
    grapheRecupNomSommet(graphe, array[i] ,nomSommetPred);
    printf("%s -> %s\n", nomSommet, nomSommetPred);
  }
}

void print_array_d(tGraphe graphe, tNumeroSommet array[MAX_SOMMETS], int nSommet){
  tNomSommet nomSommet;
  for (size_t i = 0; i < nSommet; i++) {
    grapheRecupNomSommet(graphe, i,nomSommet);
    printf("%s -> %d\n", nomSommet, (int)array[i]);
  }
}
void plus_coute_chaine(tGraphe graphe, tNumeroSommet sommet){
  tTabCouleurs couleurs;
  tFileSommets file;
  tNumeroSommet  xSommet;
  tNumeroSommet pred[MAX_SOMMETS];
  int d[MAX_SOMMETS];
  int nSommet = 0;

  for(int i=0; i<MAX_SOMMETS; i++){
    pred[i] = 0;
    d[i] = 0;
  }
  checkgraphe(graphe);
  initCouleurs(graphe, couleurs, sommet);
  /* On défile tout en affichant */
  file = fileSommetsAlloue();
  nettoyerFile(file);
  /* On enfile le premièr sommet choisi */
  fileSommetsEnfile(file, sommet);
  /* PArcours du graphe en largeur */
  while (!fileSommetsEstVide(file)) {
      xSommet =  fileSommetsDefile(file);
      traitement_voisin(graphe, xSommet, couleurs, file, d, pred);
      couleurs[xSommet] = ROUGE;
      nSommet++;
  }

  printf("tab predecesseur -----------------------------------------------------\n");
  print_array_pred(graphe, pred, nSommet);
  printf("tab d -----------------------------------------------------\n");
  print_array_d(graphe, d, nSommet);
}

int main(int argc, char *argv[]) {
  if (argc<3) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }
  tGraphe graphe;
  char * file = argv[1];
  graphe = init(argc, file);
  plus_coute_chaine(graphe, atoi(argv[2]));
  exit(EXIT_SUCCESS);
}
