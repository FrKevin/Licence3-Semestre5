#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/graphe.h"
#include "color.h"
#include "graphe_visu_color.h"

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
tGraphe init(int argc, char * pile){
  tGraphe graphe;
  if (argc<2) {
    halt("Usage : %s FichierGraphe\n", pile);
  }
  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  pile);
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
* Vide la pile
*/
void nettoyer_pile(tPileSommets pile){
  while (!pileSommetsEstPleine(pile)) {
    pileSommetsDepile(pile);
  }
}

/*
* Boucle principal
*/
void traitement_pile(tPileSommets pile, tNumeroSommet xSommet, int i[MAX_SOMMETS], tGraphe graphe, tTabCouleurs couleurs){
  tNumeroSommet iSucc;
    tNomSommet nomSommet;
      tNomSommet nomSommet2;
  int trouver = 0;
  int nSucc =0;
  int j =0;
  i[xSommet] = i[xSommet] + 1;
  nSucc = grapheNbSuccesseursSommet(graphe, xSommet);
  while(i[xSommet] <= nSucc && trouver == 0){
    iSucc = grapheSuccesseurSommetNumero(graphe, xSommet, j);
      grapheRecupNomSommet(graphe, iSucc, nomSommet);
      grapheRecupNomSommet(graphe, xSommet, nomSommet2);
    printf("sommet x %s\n", nomSommet2);
      printf("succ du sommet x %s\n", nomSommet);
    printf("sommet %d\n", i[xSommet]);
    printf("couleur i %d\n",couleurs[iSucc] );
    printf("BLEU = %d\n", BLEU);
    printf("-----------------------------\n");
    if(couleurs[iSucc] == BLEU){
      trouver = 1;
    }
    else{
      i[xSommet] = i[xSommet] +1;
      j++;
    }
  }
  if(trouver == 1){
    couleurs[iSucc] = VERT;
    printf("empile \n");
    pileSommetsEmpile(pile, iSucc);
  }
  else{
    couleurs[xSommet] = ROUGE;
    printf("depile \n");
    pileSommetsDepile(pile);
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
void parcours_en_profondeur(tGraphe graphe, tNumeroSommet sommet, char *outfile){
  tTabCouleurs couleurs;
  tPileSommets pile;
  tNumeroSommet xSommet;

  int i[MAX_SOMMETS];
  int nSommet = grapheNbSommets(graphe);
  int entrer;

  /* On Initialise les couleurs et l'indice i*/
  init_parcours(graphe, couleurs, i, nSommet);
  /* On dépile tout en affichant */
  pile = pileSommetsAlloue();

  /* On colorie le promier sommet en vert et on l'enpile */
  couleurs[sommet] = VERT;
  pileSommetsEmpile(pile, sommet);

  while (!pileSommetsEstVide(pile)) {
    graphe_visu_color(graphe, couleurs, outfile);
    xSommet = pileSommetsTete(pile);
    traitement_pile(pile, xSommet, i, graphe, couleurs);
    scanf("%d", &entrer);
  }
  graphe_visu_color(graphe, couleurs, outfile);
  pileSommetsLibere(pile);
  printf("resultat du parcours en profondeur: ---------------------------------------\n");
  print_i(graphe, i, nSommet);
}

int main(int argc, char *argv[]) {
  if (argc<4) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }
  tGraphe graphe;
  char * pile = argv[1];
  graphe = init(argc, pile);
  parcours_en_profondeur(graphe, atoi(argv[2]), argv[3]);
  exit(EXIT_SUCCESS);
}
