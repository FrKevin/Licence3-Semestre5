#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "graphe.h"
#include "graphe2visu.h"
#include "parcoursLargeur.h"

void initCouleurs(tGraphe graphe, tTabCouleurs tabCouleurs) {
	int i;
	int nbSommets = grapheNbSommets(graphe);

	for(i=0; i<nbSommets; ++i) {
		tabCouleurs[i]= BLEU;
	}
}


void traitementSommet(tGraphe graphe, tNumeroSommet sommet, tFileSommets file, tTabCouleurs tabCouleurs) {
	int nbSommets;
	int i;
	tNumeroSommet sommetTmp;

	nbSommets = (graphe->estOriente) ? grapheNbSuccesseursSommet(graphe, sommet) : grapheNbVoisinsSommet(graphe, sommet);

	for(i = 0; i<nbSommets; ++i) {
		sommetTmp = (graphe->estOriente) ? grapheSuccesseurSommetNumero(graphe, sommet, i) : grapheVoisinSommetNumero(graphe, sommet, i);
		if(tabCouleurs[sommetTmp] == BLEU) {
			tabCouleurs[sommetTmp] = VERT;
			fileSommetsEnfile(file, sommetTmp);
		}
	}
}

void parcoursLargeur(tGraphe graphe, int noSommet, tTabCouleurs tabCouleurs) {
	tFileSommets file;
	tNumeroSommet sommetActuel = noSommet;

	file = fileSommetsAlloue();

	initCouleurs(graphe, tabCouleurs);

	printf("Sommet de départ : %i\n", noSommet);

	tabCouleurs[sommetActuel] = VERT;

	fileSommetsEnfile(file, sommetActuel);

	while(!fileSommetsEstVide(file)) {
		sommetActuel = fileSommetsDefile(file);
		traitementSommet(graphe, sommetActuel, file, tabCouleurs);
		tabCouleurs[sommetActuel] = ROUGE;
	}
}
