#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <regex.h>

#include "graphe.h"

/* pour rand() */
#define _POSIX_SOURCE

/* Parser */
#define LONG_MAX_TOKEN 255
#define LONG_MAX_LIGNE 1000
#define TOKEN_ORIENTE "oriente"
#define TOKEN_NON_ORIENTE "non-oriente"

/* Opérations d'ajout pour les tableaux */
static void tableauEntiersAjoute(tTableauEntiers *tab, int i) {
  if (tab->nb==MAX_SOMMETS) {
    halt("Tableau d'entiers plein\n"); 
  }
  tab->tab[tab->nb] = i;
  tab->nb++;
}

static void tableauArcsAjoute(tTableauArcs *tab, tArc arc) {
  if (tab->nb==MAX_ARCS) {
    halt("Tableau d'arcs plein\n"); 
  }
  tab->tab[tab->nb] = arc;
  tab->nb++;
}

/* Remet à zéro un graphe, sans le désallouer */

static void auxResetGraphe(tGraphe graphe) {
  tNumeroSommet i,j;  
  /* matrice d'adjacence mise à zéro */
  graphe->nbSommets = 0;
  for(i=0;i<MAX_SOMMETS;i++) 
    for(j=0;j<MAX_SOMMETS;j++) 
      graphe->matriceAdjacence[i][j]=0;

  /* table des successeurs, prédécesseurs et voisins mise à zéro */
  for(i=0;i<MAX_SOMMETS;i++) {
    graphe->tableSuccesseurs[i].nb = 0;
    graphe->tablePredecesseurs[i].nb = 0;
    graphe->tableVoisins[i].nb = 0;
  }

  /* table des arcs mise à zéro */
  graphe->tableArcs.nb = 0;
}

/* Création */
tGraphe grapheAlloue() {
  tGraphe graphe;

  graphe = (tGraphe)malloc(sizeof(struct tGraphe));
  if (graphe==NULL) 
    halt("Erreur d'allocation mémoire dans grapheAlloue\n");

  auxResetGraphe(graphe);
  return graphe;
}

void grapheLibere(tGraphe graphe) {
  free(graphe);
}

void grapheChangeType(tGraphe graphe, int oriente) {
  if (grapheNbSommets(graphe)>0)
    halt("On ne peut changer le type d'un graphe que s'il est vide");
  if ( (oriente!=0) && (oriente!=1) )
    halt("Orientation incorrecte");
  graphe->estOriente = oriente;
}

void grapheAleatoire(tGraphe graphe, 
		     int nbSommets,
		     int estOriente,
		     double probaArc) {
  tNumeroSommet i,j,debut;
  double prob;
  tNomSommet nom;
  tArc arc;
  
  /* On vide le graphe */
  auxResetGraphe(graphe);

  if ( (nbSommets<=0) || (nbSommets>MAX_SOMMETS) )
    halt("nombre de sommets incorrect : %d\n", nbSommets);

  if ( (estOriente!=0)&&(estOriente!=1))
    halt("estOriente doit valoir 0 ou 1");

  if ( (probaArc<0.0) || (probaArc>1.0) )
    halt("La probabilité doit être entre 0.0 et 1.0");

  graphe->estOriente = estOriente;
  /* on ajoute les sommets */
  for(i=0;i<nbSommets;i++) {
    sprintf(nom, "S%d", i);
    grapheAjouteSommet(graphe, nom);
  }

  /* on ajoute les arcs */
  for(i=0;i<nbSommets;i++) {
    if (grapheEstOriente(graphe))
      debut=0;
    else
      debut=i;

    for(j=debut;j<nbSommets;j++) {
      /* on tire une proba */
      prob = ((float)rand()) / RAND_MAX;
      if (prob<=probaArc) {
	arc.orig = i;
	arc.dest = j;
	arc.val = 0.5 + (10-0.5) * (float)(rand()) / RAND_MAX;
	grapheAjouteArc(graphe, arc);
      }
    }
  }
}

/* fonctions pour le parser */
static int estBlanc(char c) {

  return (c==' ') || (c=='\t') || (c=='\n') || (c=='\r');
}


static int estSpecial(char c) {

  return (c=='=') || (c==';')  || (c=='#');
}
/* Lecture d'un token
*/
static int lireToken(FILE* fic, char token[LONG_MAX_TOKEN]) {
  int tokenCommence=0;
  int nbCarToken=0;
  int termine=0;
  int c;
  char ligne[LONG_MAX_LIGNE];
  
  c = fgetc(fic);
  while ( !termine && (c != EOF)) {
   
    // si c'est un blanc ou un car spécial
    if ( estBlanc(c) || estSpecial(c) ) {
      // si c'est un commentaire, on vide le reste de la ligne
      if (c == '#') { 
	fgets(ligne, LONG_MAX_LIGNE, fic); 
	c = ' '; //fgetc(fic);
      } 
      else {
	// si on avait commencé le token
	if (tokenCommence) {
	  // alors on a fini de lire le token, que ce soit
	  // un espace ou un caractere special
	  termine = 1;
	} else {
	  // le token n'est pas commencé
	  if (estSpecial(c) ) {
	    termine = 1;
	    token[0]=c;
	    nbCarToken=1;
	  }
	  // sinon, c'est un blanc et on l'ignore
	  c = fgetc(fic);
	}
      }
    } else {
      // ce n'est pas un blanc, on l'ajoute au token
      tokenCommence = 1;
      token[nbCarToken] = c;
      nbCarToken++;
      c = fgetc(fic);
    }
  }

  ungetc(c, fic);

  token[nbCarToken] = '\0';
  // si aucun token n'a été lu, on renvoie -1

#ifdef DEBUG
  printf("Token lu : [%s]\n", token);
#endif

  if (nbCarToken==0) { return -1; }
  else { return 0; };
}

/* idem lire token mais arrête le programme si aucun token ne peut
   être lu */
static void lireTokenGaranti(FILE* fic, char token[LONG_MAX_TOKEN]) {
  if (-1 == lireToken(fic, token)) {
    halt("Aucun token n'a pu etre lu, fichier non termine ?");
  };
}

static void lireTokenAttendu(FILE* fic, char token[LONG_MAX_TOKEN], char *attendu) {
  lireTokenGaranti(fic, token);
  if (strcmp(token, attendu)) {
    halt("Token [%s] attendu, mais token [%s] trouv'e `a la place",
	 attendu, token);
  }
}

static double tokenToDouble(char *token) {
  char *p ;
  double res;

  res = strtod(token, &p);
  if (*p != '\0') {
    halt("La valeur de l'arc doit ^etre un double : %s trouv'e",
	 token);
  }
  return res;
}


static void grapheAjouteArcNoms(tGraphe graphe, tNomSommet orig,
				  tNomSommet dest, tValeurArc val);

int grapheChargeFichier(tGraphe graphe, char *fichier) {
  FILE* fic;
  char token[LONG_MAX_TOKEN];
  char orig[LONG_MAX_TOKEN];
  char dest[LONG_MAX_TOKEN];
  tValeurArc valeurArc;
  //int n;
  /* ouverture */
  fic = fopen(fichier, "r");
  if (fic==NULL) {
    halt("Le fichier %s n'a pas pu etre ouvert\n", fichier);
  }
  
  /* vérification du type de fichier */
  lireTokenAttendu(fic, token, "type");
  lireTokenAttendu(fic, token, "=");

  /* détermination du type de l'arbre */
  lireTokenGaranti(fic, token);
  if (!strcmp(token,TOKEN_ORIENTE)) {
    // le graphe est oriente
    graphe->estOriente = 1;
  } else if (!strcmp(token,TOKEN_NON_ORIENTE)) {
    graphe->estOriente = 0; }
  else {
    halt("Le type du graphe doit ^etre [%s] ou [%s]",
	 TOKEN_ORIENTE, TOKEN_NON_ORIENTE);
  }

  lireTokenAttendu(fic, token, ";");

  lireTokenAttendu(fic, token, "sommets");
  lireTokenAttendu(fic, token, "=");

  /* on lit tous les sommets */
  lireTokenGaranti(fic, token);
  while (strcmp(token,";")) {

#ifdef DEBUG
    printf("Sommet : %s\n", token);
#endif

    /* ajout du sommet */
    grapheAjouteSommet(graphe, token);

    lireTokenGaranti(fic, token);
  }

  /* les arcs */
  lireTokenAttendu(fic, token, "arcs");
  lireTokenAttendu(fic, token, "=");
  
  lireTokenGaranti(fic, token);
  while (strcmp(token,";")) {
    /* token est le sommet de départ */
    strcpy(orig, token);
    lireTokenGaranti(fic, dest);
    lireTokenGaranti(fic, token);
    valeurArc = tokenToDouble(token);
#ifdef DEBUG
    printf("Arc :  %s - %f -> %s\n", orig, valeurArc, dest);
#endif
    
    grapheAjouteArcNoms(graphe, orig, dest, valeurArc);
    lireTokenGaranti(fic, token);
  }
  fclose(fic);
  return -1;
 }


/* Modification */
void grapheAjouteSommet(tGraphe graphe, tNomSommet sommet) {
    if (graphe->nbSommets==MAX_SOMMETS) {
      halt("Nombre de sommet maximum (=%d) atteint", MAX_SOMMETS);
    };
    if (grapheChercheSommetParNom(graphe, sommet)>=0)
      halt("Sommet d'ej`a existant %s", sommet);

    strcpy(graphe->nomSommets[graphe->nbSommets], sommet);
    graphe->nbSommets ++ ;
}



void grapheAjouteArc(tGraphe graphe, tArc arc) {
  tNumeroSommet orig, dest;
  tNomSommet nom_orig, nom_dest;
  
  orig = arc.orig;
  dest = arc.dest;

  /* On teste si l'arc existe déjà ou pas */
  if (grapheExisteArcEntre(graphe, orig, dest)) {
    grapheRecupNomSommet(graphe, orig, nom_orig);
    grapheRecupNomSommet(graphe, dest, nom_dest);
    halt("Un arc existe déjà entre les sommets %s (numéro %d) "
	 "et %s (numéro %d)\n",
	 nom_orig, orig, nom_dest, dest);
  }


  /* la matrice d'adjacence */
  graphe->matriceAdjacence[orig][dest] = arc.val;
  if (!grapheEstOriente(graphe)) {
    graphe->matriceAdjacence[dest][orig] = arc.val;
  }

  if (grapheEstOriente(graphe)) {
    /* ajout dans les successeurs */
    tableauEntiersAjoute(& (graphe->tableSuccesseurs[orig]), dest);
    /* ajout dans les prédécesseurs */
    tableauEntiersAjoute(& (graphe->tablePredecesseurs[dest]), orig);
  } 

  /* Même si l'arbre est orienté, on remplit la table des voisins.
     Toutefois, si l'arc est orienté, on vérifie que l'arc
     inverse n'existe pas déjà, car dans ce cas les voisins sont
     déjà placés. */
  
  if ( ! ( grapheEstOriente(graphe) && 
	   grapheExisteArcEntre(graphe,dest,orig) ) ) {
      tableauEntiersAjoute(& (graphe->tableVoisins[orig]), dest);
      /* si l'arc va du sommet vers lui même, on n'ajoute pas de voisin */
      if (orig!=dest)
	tableauEntiersAjoute(& (graphe->tableVoisins[dest]), orig);
    }
  /* Mise à jour de la table des arcs */
  tableauArcsAjoute(& (graphe->tableArcs), arc);
}

static void grapheAjouteArcNoms(tGraphe graphe, tNomSommet orig,
				  tNomSommet dest, tValeurArc val) {
  tNumeroSommet i_orig, i_dest;
  tArc arc;
  
  i_orig = grapheChercheSommetParNom(graphe, orig);
  
  if ((i_orig==-1)) 
    halt("Sommet inexistant : %s\n", orig);

  i_dest = grapheChercheSommetParNom(graphe, dest);
  
  if ((i_dest==-1)) 
    halt("Sommet inexistant : %s\n", dest);

  arc.orig = i_orig;
  arc.dest = i_dest;
  arc.val = val;
  grapheAjouteArc(graphe, arc);
}



/* Affichage */
void grapheAffiche(tGraphe graphe) {
  tNomSommet nom;
  tNumeroSommet i, j, successeur, predecesseur;
  tValeurArc val;
  tArc arc;
  /* Affiche la liste des sommets et leur nom */
  printf("Type de l'arbre : ");
  if (grapheEstOriente(graphe))  printf("orient'e"); 
  else printf("non orient'e");
  printf("\n\n");

  printf("Nombre de sommets : %d\n\n", grapheNbSommets(graphe));

  printf("Liste des sommets avec leurs num'eros:\n");
  for(i=0; i < grapheNbSommets(graphe);i++) {
    grapheRecupNomSommet(graphe, i, nom);
    printf("- %d : %s\n", i, nom);
  }
  printf("\n");

  /* Matrice d'adjacence */
  printf("Matrice d'adjacence :\n");
  printf("%2s", "");
  for(i=0; i < grapheNbSommets(graphe);i++) {
    printf("%7d", i);
  }
  printf("\n");
  
  for(i=0; i < grapheNbSommets(graphe);i++) {
    printf("%3d ", i);
    for(j=0; j < grapheNbSommets(graphe);j++) {
      if (grapheExisteArcEntre(graphe,i,j)) {
	val = grapheRecupValeurArc(graphe,i,j);
	printf("%6.2f ", val);}
      else
	printf("       ");
    }
    printf("\n");
  }
  printf("\n");

  /* Affiche les voisins, successeurs, prédecesseurs */
  if (grapheEstOriente(graphe)) {
    /* affichage des successeurs */
    printf("Liste des successeurs :\n");
    for(i=0; i < grapheNbSommets(graphe);i++) {
      grapheRecupNomSommet(graphe, i, nom);
      printf("%s : ", nom);
      for(j=0; j<grapheNbSuccesseursSommet(graphe, i); j++) {
	successeur = grapheSuccesseurSommetNumero(graphe, i, j);
	grapheRecupNomSommet(graphe, successeur, nom);
	printf("%s=%.2f ", nom, 
	       grapheRecupValeurArc(graphe, i, successeur));
      }
      printf("\n");
    }
    /* affichage des prédécesseurs */
    printf("\nListe des prédécesseurs :\n");
    for(i=0; i < grapheNbSommets(graphe);i++) {
      grapheRecupNomSommet(graphe, i, nom);
      printf("%s : ", nom);
      for(j=0; j<grapheNbPredecesseursSommet(graphe, i); j++) {
	predecesseur = graphePredecesseurSommetNumero(graphe, i, j);
	grapheRecupNomSommet(graphe, predecesseur, nom);
	printf("%s=%.2f ", nom, 
	       grapheRecupValeurArc(graphe, predecesseur, i));
      }
      printf("\n");
    }

  } else {
    /* le graphe n'est pas orienté */
    printf("Liste des voisins :\n");
    for(i=0; i < grapheNbSommets(graphe);i++) {
      grapheRecupNomSommet(graphe, i, nom);
      printf("%s : ", nom);
      for(j=0; j<grapheNbVoisinsSommet(graphe, i); j++) {
	successeur = grapheVoisinSommetNumero(graphe, i, j);
	grapheRecupNomSommet(graphe, successeur, nom);
	printf("%s=%.2f ", nom, 
	       grapheRecupValeurArc(graphe, i, successeur));
      }
      printf("\n");
    }
  }
  printf("\n");
  
/* Affiche la liste des arcs */
  printf("Liste des arcs :\n");
  for(i=0; i < grapheNbArcs(graphe); i++) {
    arc = grapheRecupArcNumero(graphe, i);
    grapheRecupNomSommet(graphe, arc.orig, nom);
    printf("%s", nom);
    if (grapheEstOriente(graphe))
      printf(" -> ");
    else
      printf(" -- ");
    grapheRecupNomSommet(graphe, arc.dest, nom);
    printf("%s ",nom);
    printf("  = %.2f\n", arc.val);
  }
  
}

/* Consultation */

/* Vérifie que le numéro de sommet est correct */
void auxVerifieNumeroSommet(tGraphe graphe, 
		       tNumeroSommet numero) {
  if ( (numero<0) || (numero>=graphe->nbSommets) ) {
    halt("Numero de sommet incorrect %d\n", numero);
  }
}

int grapheEstOriente(tGraphe graphe) {
  return (graphe->estOriente != 0);
}

int grapheNbSommets(tGraphe graphe){
  return graphe->nbSommets;
}

void grapheRecupNomSommet(tGraphe graphe, tNumeroSommet numero, 
			  tNomSommet nomSommet){
  auxVerifieNumeroSommet(graphe, numero);
  strcpy(nomSommet, graphe->nomSommets[numero]);
}

tNumeroSommet grapheChercheSommetParNom(tGraphe graphe, tNomSommet nomSommet){
  tNumeroSommet i;
  for(i=0;i<graphe->nbSommets;i++) {
    if (! (strcmp(graphe->nomSommets[i], nomSommet) ) )
      return i;
  }
  return -1;
} 


int grapheNbSuccesseursSommet(tGraphe graphe, tNumeroSommet sommet){
  auxVerifieNumeroSommet(graphe, sommet);
  if (!grapheEstOriente(graphe)) 
    halt("Fonction réservée aux graphes orientés");
  return graphe->tableSuccesseurs[sommet].nb;
}

tNumeroSommet grapheSuccesseurSommetNumero(tGraphe graphe, 
					   tNumeroSommet sommet, 
					   int numero){
  int nbSuccesseurs;
  auxVerifieNumeroSommet(graphe, sommet);
  if (!grapheEstOriente(graphe)) 
    halt("Fonction réservée aux graphes orientés");

  nbSuccesseurs = graphe->tableSuccesseurs[sommet].nb;  
  if ( (numero<0) || (numero>=nbSuccesseurs) ) {
    halt("Numero de successeur incorrect (%d) pour le sommet numéro %d", 
	 numero, sommet);
  }
  return graphe->tableSuccesseurs[sommet].tab[numero];
}

int grapheNbPredecesseursSommet(tGraphe graphe, tNumeroSommet sommet) {
  auxVerifieNumeroSommet(graphe, sommet);
  if (!grapheEstOriente(graphe)) 
    halt("Fonction réservée aux graphes orientés");
  return graphe->tablePredecesseurs[sommet].nb;
}

tNumeroSommet graphePredecesseurSommetNumero(tGraphe graphe, 
					     tNumeroSommet sommet, 
					     int numero) {
  int nbPredecesseurs;
  auxVerifieNumeroSommet(graphe, sommet);
  if (!grapheEstOriente(graphe)) 
    halt("Fonction réservée aux graphes orientés");

  nbPredecesseurs = graphe->tablePredecesseurs[sommet].nb;  
  if ( (numero<0) || (numero>=nbPredecesseurs) ) {
    halt("Numero de successeur incorrect (%d) pour le sommet numéro %d", 
	 numero, sommet);
  }
  return graphe->tablePredecesseurs[sommet].tab[numero];
}

int grapheNbVoisinsSommet(tGraphe graphe, tNumeroSommet sommet) {
  auxVerifieNumeroSommet(graphe, sommet);
  /*if (grapheEstOriente(graphe)) 
    halt("Fonction réservée aux graphes non orientés");*/
  return graphe->tableVoisins[sommet].nb;
}

tNumeroSommet grapheVoisinSommetNumero(tGraphe graphe, 
				       tNumeroSommet sommet, 
				       int numero) {
  int nbVoisins;
  auxVerifieNumeroSommet(graphe, sommet);
  /*if (grapheEstOriente(graphe)) 
    halt("Fonction réservée aux graphes non orientés");*/

  nbVoisins = graphe->tableVoisins[sommet].nb;  
  if ( (numero<0) || (numero>=nbVoisins) ) {
    halt("Numero de successeur incorrect (%d) pour le sommet numéro %d", 
	 numero, sommet);
  }
  return graphe->tableVoisins[sommet].tab[numero];
}


int grapheNbArcs(tGraphe graphe) {
  return graphe->tableArcs.nb;
}


tArc grapheRecupArcNumero(tGraphe graphe, int numero) {
  if ( (numero<0) || (numero>grapheNbArcs(graphe)) )
    halt("Numéro d'arc incorrect : %d\n", numero);

  return graphe->tableArcs.tab[numero];
}

tValeurArc grapheRecupValeurArc(tGraphe graphe,
			 tNumeroSommet depart,
			 tNumeroSommet arrivee){

  if ( (depart<0) || (depart>=graphe->nbSommets) ) {
    halt("Numero de sommet d'origine incorrect %d\n", depart);
  }

  if ( (arrivee<0) || (arrivee>=graphe->nbSommets) ) {
    halt("Numero de sommet de destination incorrect %d\n", arrivee);
  }

  if ( !grapheExisteArcEntre(graphe, depart, arrivee) ) {
    halt("Il n'y pas d'arc entre le sommet %d et le sommet arrivee %d",
	 depart, arrivee);
  }
  return graphe->matriceAdjacence[depart][arrivee];
}

int grapheExisteArcEntre(tGraphe graphe,
			 tNumeroSommet depart,
			 tNumeroSommet arrivee) {

  return ( 0.0 != graphe->matriceAdjacence[depart][arrivee] );
}



/* opérations sur les files */

tFileSommets fileSommetsAlloue() {
  tFileSommets file;

  file = (tFileSommets)malloc( sizeof(struct tFileSommets) );
  if (file==NULL) 
    halt("Erreur d'allocation mémoire dans fileSommetsAlloue\n");
  file -> debut = 0;
  file -> fin = 0;
  return file;
}

static tNumeroSommet auxFileNumeroSuivant(tFileSommets file, 
					  tNumeroSommet numero) {
  return ( (numero+1) % (MAX_SOMMETS+1) );
}

void fileSommetsLibere(tFileSommets file) {
  free(file);
}

int fileSommetsEstVide(tFileSommets file) {
  return (file->debut == file->fin);
}

int fileSommetsEstPleine(tFileSommets file) {
  return ( auxFileNumeroSuivant(file, file->fin) == file->debut );
}

void fileSommetsEnfile(tFileSommets file, int val) {
  if (fileSommetsEstPleine(file))
    halt("File pleine\n");
  file->tab[file->fin] = val;
  file->fin = auxFileNumeroSuivant(file, file->fin);
}

int fileSommetsDefile(tFileSommets file) {
  tNumeroSommet res;
  if (fileSommetsEstVide(file))
    halt("File vide\n");
  res = file->tab[file->debut];
  file->debut = auxFileNumeroSuivant(file, file->debut);
  return res;
}


/* opérations sur les piles */


tPileSommets pileSommetsAlloue() {
  tPileSommets pile;

  pile = (tPileSommets)malloc( sizeof(struct tPileSommets) );
  if (pile==NULL) 
    halt("Erreur d'allocation mémoire dans fileSommetsAlloue\n");
  return pile;
}

int pileSommetsEstVide(tPileSommets pile) {
  return pile->tete == 0;
}

int pileSommetsEstPleine(tPileSommets pile) {
  return pile->tete == MAX_SOMMETS;
}

void pileSommetsLibere(tPileSommets pile) {
  free(pile);
}

void pileSommetsAffiche(tPileSommets pile) {
  int i;
  for (i=0;i<pile->tete;i++)
    printf("%d ", pile->tab[i]);
  printf("<- tete");
}

tNumeroSommet pileSommetsTete(tPileSommets pile) {
  if (pileSommetsEstVide(pile))
    halt("Ne peut renvoyer la tête d'une pile vide");
  return pile->tab[pile->tete-1];
}

void pileSommetsEmpile(tPileSommets pile, tNumeroSommet numero) {
  if (pileSommetsEstPleine(pile))
    halt("Ne peut empiler dans la pile pleine\n");
  pile->tab[pile->tete] = numero;
  (pile->tete)++;
}

tNumeroSommet pileSommetsDepile(tPileSommets pile) {
  tNumeroSommet res;
  if (pileSommetsEstVide(pile))
    halt("Ne peut dépiler d'une pile vide");
  res = pile->tab[pile->tete-1];
  (pile->tete)--;
  
  return res;
}

void halt(char * format, ...) {
  va_list ap;

  va_start(ap, format);
  fprintf(stderr, "\n\n**************\n");
  vfprintf(stderr, format, ap);
  fprintf(stderr, "\n\n**************\n");
  va_end(ap);
  exit(EXIT_FAILURE);
}
