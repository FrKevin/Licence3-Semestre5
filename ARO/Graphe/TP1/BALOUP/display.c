

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "display.h"




void graphe2visu(tGraphe graphe, char *outfile) {
	
	FILE *fic;
	char commande[1024];
	char dotfile[1024]; /* le fichier dot pour créer le ps */
	int ret, i, j, nbSommets, estOriente;
	tNomSommet nomSommet1, nomSommet2;
	
	
	/* on va créer un fichier pour graphviz, dans le fichier "outfile".dot */
	strcpy(dotfile, outfile);
	strcat(dotfile, ".dot");
	fic = fopen(dotfile, "w");
	if (fic==NULL)
		halt ("Ouverture du fichier %s en écriture impossible\n", dotfile);
	/*
	on parcourt le graphe pour en tirer les informations
	nécessaires pour graphviz.
	Pour écrire dans le fichier, on utilise fprintf (qui s'utilise
	comme printf mais on mettant en plus fic comme premier paramètre).
	Ex :
	fprintf(fic, "graph {\n");
	ou
	fprintf(fic, "  %s -> %s\n", origine, destination);
	*/
	estOriente = grapheEstOriente(graphe);
	if (estOriente) {
		fprintf(fic, "di");
	}
	fprintf(fic, "graph {\n");
	
	/* on écrit ici les arcs */
	nbSommets = grapheNbSommets(graphe);
	for (i=0;i<nbSommets; i++) {
		grapheRecupNomSommet(graphe, i, nomSommet1);
		for (j= ((estOriente) ? 0 : i+1); j<nbSommets; j++) {
			grapheRecupNomSommet(graphe, j, nomSommet2);
			if (grapheExisteArcEntre(graphe, i, j)) {
				if (estOriente) {
					fprintf(fic, "%s -> %s;\n", nomSommet1, nomSommet2);
				}
				else {
					fprintf(fic, "%s -- %s;\n", nomSommet1, nomSommet2);
				}
			}
		}
	}
	
	
	
	
	fprintf(fic, "}\n");
	
	fclose(fic);
	sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
	ret = system(commande);
	if (WEXITSTATUS(ret))
		halt("La commande suivante a échoué\n%s\n", commande);
	else {
		sprintf(commande, "rm %s", dotfile);
		system(commande);
	}
	
	
}
