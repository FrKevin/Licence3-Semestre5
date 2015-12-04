// NOM : gamelin
// Prénom : kevin
// Nom de la machine : a14p24

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"

/* gestion des couleurs */
typedef enum {ROUGE=0, VERT=1, BLEU=2} tCouleur;
typedef tCouleur tTabCouleur[MAX_SOMMETS];


/* parcours en largeur d'abord (pour graphe orienté uniquement) */
//
// paramètres :
//
// graphe = graphe orienté
// s = sommet de départ
// result = tableau de sommets accessibles depuis s (result[i]=1 si i est accessible depuis s, -1 sinon)
//
void parcours_largeur(tGraphe graphe, tNumeroSommet s, int result[])
{
  // nombre de sommets du graphe
  unsigned int n = grapheNbSommets(graphe);
  // le tableau de couleurs
  tCouleur tabCouleurs[n];
  // la file
  tFileSommets file;
  // sommets x,y
  tNumeroSommet x, y;
  // variable de parcours
  unsigned int i;

  /* initialisation */

  // colorier tous les sommets en bleu
  for (i=0; i<n; i++)
    {
      tabCouleurs[i] = BLEU;
    }
  // initialiser la file
  file = fileSommetsAlloue();
  // colorier s en vert
  tabCouleurs[s] = VERT;
  // enfiler s
  fileSommetsEnfile(file, s);

  /* boucle principale */

  // tant que la file n'est pas vide
  while (!fileSommetsEstVide(file))
    {
      // x = tête de file
      x = fileSommetsDefile(file);
      // parcours de tous les successeurs
      for (i=0; i<grapheNbSuccesseursSommet(graphe,x); i++)
        {
	  // y est le nom du successeur courant
	  y = grapheSuccesseurSommetNumero(graphe, x, i);
	  if (tabCouleurs[y] == BLEU)
            {
	      // colorier y en vert et l’enfiler
	      tabCouleurs[y] = VERT;
	      fileSommetsEnfile(file, y);
	    }
        }
      tabCouleurs[x] = ROUGE;
    }

  // libérer la file
  fileSommetsLibere(file);

  // tous les sommets en rouge sont accessibles
  for (i=0; i<n; i++)
    {
      if (tabCouleurs[i] == ROUGE) result[i] = 1;
      else result[i] = -1;
    }
}


/* retourne tous les sommets à une distance inférieure ou égale à 2 du sommet s */
//
// paramètres :
//
// graphe = graphe orienté
// s = sommet de départ
// result = tableau de sommets à une distance inférieure ou égale à 2 du sommet s (result[i]=1 si distance(s,i)<=2, -1 sinon)
//
void distance_inf_2(tGraphe graphe, tNumeroSommet s, int result[])
{

  // nombre de sommets du graphe
  unsigned int n = grapheNbSommets(graphe);
  int nSuccesseur_de_s = grapheNbSuccesseursSommet(graphe,s);
  int nSuccesseur_de_y;
  tNumeroSommet x, y;

  // variable de parcours
  unsigned int i;

  /* Pour eviter des erreurs */
  for(i =0; i< n; i++){
    result[i] =-1;
  }
    /* boucle principale */
  for (i=0; i<nSuccesseur_de_s; i++){
    // y est le nom du successeur courant
    x = grapheSuccesseurSommetNumero(graphe, s, i);
    result[x] = 1;
    nSuccesseur_de_y = grapheNbSuccesseursSommet(graphe,x);
    for(int j =0; j< nSuccesseur_de_y; j++){
      y = grapheSuccesseurSommetNumero(graphe, x, j);
      //Si on ne la pas deja traité
        result[y] = 1;
      }
    }
}


/* retourne tous les sommets à une distance strictement égale à 2 du sommet s */
//
// paramètres :
//
// graphe = graphe orienté
// s = sommet de départ
// result = tableau de sommets à une distance strictement égale à 2 du sommet s (result[i]=1 si distance(s,i)==2, -1 sinon)
//
void distance_eq_2(tGraphe graphe, tNumeroSommet s, int result[])
{
  // nombre de sommets du graphe
  unsigned int n = grapheNbSommets(graphe);
  int nSuccesseur_de_s = grapheNbSuccesseursSommet(graphe,s);
  int nSuccesseur_de_y;
  tNumeroSommet x, y;

  // variable de parcours
  unsigned int i;

  /* Pour eviter des erreurs */
  for(i =0; i< n; i++){
    result[i] =-1;
  }
    /* boucle principale */
  for (i=0; i<nSuccesseur_de_s; i++){
    // y est le nom du successeur courant
    x = grapheSuccesseurSommetNumero(graphe, s, i);
    nSuccesseur_de_y = grapheNbSuccesseursSommet(graphe,x);
    for(int j =0; j< nSuccesseur_de_y; j++){
      y = grapheSuccesseurSommetNumero(graphe, x, j);
        result[y] = 1;
      }
    }
}


/* retourne tous les sommets à une distance strictement égale à k du sommet s */
//
// paramètres :
//
// graphe = graphe orienté
// s = sommet de départ
// k = distance minimale
// result = tableau de sommets à une distance strictement égale à k du sommet s (result[i]=1 si distance(s,i)==k, -1 sinon)
//
void get_succ(tGraphe graphe, tNumeroSommet s, int result[]){
   int nSuccesseur_de_s = grapheNbSuccesseursSommet(graphe,s);
    for (i=0; i<nSuccesseur_de_s; i++){
      x = grapheSuccesseurSommetNumero(graphe, s, i);
      result[x] = 1;
    }
}

void distance_eq_k(tGraphe graphe, tNumeroSommet s, unsigned int k, int result[])
{

  unsigned int n = grapheNbSommets(graphe);
  int nSuccesseur_de_s = grapheNbSuccesseursSommet(graphe,s);
  int nSuccesseur_de_y;
  tNumeroSommet x, y;
  int cpt =1;

  // variable de parcours
  unsigned int i;

  /* Pour eviter des erreurs */
  for(i =0; i< n; i++){
    result[i] =-1;
  }
  while (cpt <= k) {
      get_succ(graphe, s, result);
      
  }

    /* boucle principale */
  for (i=0; i<nSuccesseur_de_s; i++){
    // y est le nom du successeur courant
    x = grapheSuccesseurSommetNumero(graphe, s, i);
    nSuccesseur_de_y = grapheNbSuccesseursSommet(graphe,x);
    for(int j =0; j< nSuccesseur_de_y; j++){
      y = grapheSuccesseurSommetNumero(graphe, x, j);
        result[y] = 1;
      }
    }
}


/* programme principal */
int main(int argc, char *argv[])
{
  // graphe
  tGraphe graphe;
  // nom du ficher d'entree
  char *fic;

  // usage
  if (argc!=2)
    halt("Usage : %s <fichier_graphe>\n", argv[0]);

  // lecture du nom de fichier
  fic = argv[1];

  // chargement du graphe
  graphe = grapheAlloue();
  grapheChargeFichier(graphe, fic);

  // le nombre de sommets du graphe
  unsigned int n = grapheNbSommets(graphe);

  // initialisation du sommet de départ à 0 (le premier sommet du graphe)
  tNumeroSommet depart = 0;
  tNomSommet nom;
  grapheRecupNomSommet(graphe, depart, nom);
  printf("Sommet de depart : %s\n", nom);

  // tableau de résultat des différentes fonctionnalités
  int result[MAX_SOMMETS];

  // valeur de k
  unsigned int k = 3;

  /*** parcours en largeur ***/
  printf("*** Parcours largeur:\t");
  // appel procédure
  parcours_largeur(graphe, depart, result);
  // affichage
  for (unsigned int i=0; i<n; i++){
      if (result[i] == 1)
        {
	  // nom du sommet
	  grapheRecupNomSommet(graphe, i, nom);
	  printf("%s ", nom);
        }
    }
  printf("\n");

  /*** distance <= 2 ***/
  printf("*** Distance <= 2:\t");
  // appel procédure
  distance_inf_2(graphe, depart, result);
  // affichage
  for (unsigned int i=0; i<n; i++){
      if (result[i] == 1){
	       // nom du sommet
	        grapheRecupNomSommet(graphe, i, nom);
	         printf("%s ", nom);
      }
  }
  printf("\n");

  /*** distance == 2 ***/
  printf("*** Distance == 2:\t");
  // appel procédure
  distance_eq_2(graphe, depart, result);
  // affichage
  for (unsigned int i=0; i<n; i++)
    {
      if (result[i] == 1)
        {
	  // nom du sommet
	  grapheRecupNomSommet(graphe, i, nom);
	  printf("%s ", nom);
        }
    }
  printf("\n");

  /*** distance == k ***/
  printf("*** Distance == k (%d):\t", k);
  // appel procédure
  distance_eq_k(graphe, depart, k, result);
  // affichage
  for (unsigned int i=0; i<n; i++)
    {
      if (result[i] == 1)
        {
	  // nom du sommet
	  grapheRecupNomSommet(graphe, i, nom);
	  printf("%s ", nom);
        }
    }
  printf("\n");

  exit(EXIT_SUCCESS);
}
