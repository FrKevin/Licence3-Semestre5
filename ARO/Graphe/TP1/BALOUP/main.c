

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"
#include "display.h"


int main(int argc, char *argv[]) {
	tGraphe graphe;
	char graphfile[1024];

	if (argc<2) {
		halt("Usage : %s FichierGraphe\n", argv[0]);
	}
	
	strcpy(graphfile, argv[1]);
	strcat(graphfile, ".ps");

	graphe = grapheAlloue();
	grapheChargeFichier(graphe,  argv[1]);
	graphe2visu(graphe, graphfile);
	
	/* traitement du graph */
	
	
	
	
	
	

	grapheLibere(graphe);

	exit(EXIT_SUCCESS);
}
