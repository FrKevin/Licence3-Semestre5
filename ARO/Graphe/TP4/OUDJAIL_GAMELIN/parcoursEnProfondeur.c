#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sys/wait.h" /* n´ecessaire pour la macro WEXITSTATUS */
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

/*
* Initialise le graphe
*/
tGraphe init(int argc, char * file){
  tGraphe graphe;
  if (argc<2) {
    halt("Usage : %s FichierGraphe\n", file);
  }
  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  file);
  return graphe;
}

/*
* Pour les sommets du graphe, on Initialise leurs couleur
*/
void init_parcours(tGraphe graphe, tTabCouleurs couleurs, int i[MAX_SOMMETS], int nSommets) {
  for (size_t y = 0; y < nSommets; y++) {
    couleurs[y] = BLEU;
    i[y] = 0;
  }
}

/*
* Vide la file
*/
void nettoyer_file(tFileSommets file){
  while (!fileSommetsEstVide(file)) {
    fileSommetsDefile(file);
  }
}

/*
* Boucle principal
*/
void traitement_pile(tFileSommets file, tNumeroSommet xSommet, int i[MAX_SOMMETS], tGraphe graphe, tTabCouleurs couleurs){
  tNumeroSommet iSucc;
  int trouver = 0;
  int nSucc =0;

  i[xSommet] = i[xSommet] + 1;
  nSucc = grapheNbSuccesseursSommet(graphe, xSommet);
  while(i[xSommet] <= nSucc && trouver == 0){
    iSucc = grapheSuccesseurSommetNumero(graphe, xSommet, i[xSommet]);
    if(couleurs[iSucc] == BLEU){
      trouver = 1;
    }
    else{
      i[xSommet] = i[xSommet] +1;
    }
  }
  if(trouver == 1){
    couleurs[iSucc] = VERT;
    fileSommetsEnfile(file, iSucc);
  }
  else{
    couleurs[xSommet] = ROUGE;
    fileSommetsDefile(file);
  }
}

/*
* Affiche les indices trouver
*/
void print_i(tGraphe graphe, int i[MAX_SOMMETS], int nSommet){
  tNomSommet nomSommet;

  for (size_t y = 0; y < nSommet; y++) {
    grapheRecupNomSommet(graphe, y, nomSommet);
    printf("%s: %d\n", nomSommet, i[y]);
  }
}
/*
* Parcours en parcours_en_profondeur
*/
void parcours_en_profondeur(tGraphe graphe, tNumeroSommet sommet){
  tTabCouleurs couleurs;
  tFileSommets file;
  tNumeroSommet xSommet;

  int i[MAX_SOMMETS];
  int nSommet = grapheNbSommets(graphe);

  /* On Initialise les couleurs et l'indice i*/
  init_parcours(graphe, couleurs, i, nSommet);
  /* On vide la file */
  nettoyer_file(file);
  /* On colorie le promier sommet en vert et on l'enfile */
  couleurs[sommet] = VERT;
  fileSommetsEnfile(file, sommet);

  while (!fileSommetsEstVide(file)) {
    xSommet =  fileSommetsDefile(file);
    traitement_pile(file, xSommet, i, graphe, couleurs);
  }

  printf("resultat du parcours en profondeur: ---------------------------------------\n");
  print_i(graphe, i, nSommet);
}

int main(int argc, char *argv[]) {
  if (argc<3) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }
  tGraphe graphe;
  char * file = argv[1];
  graphe = init(argc, file);
  parcours_en_profondeur(graphe, atoi(argv[2]));
  exit(EXIT_SUCCESS);
}
