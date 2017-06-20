#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sys/wait.h" /* n´ecessaire pour la macro WEXITSTATUS */
#include "../lib/graphe.h"


void graphe2visu(tGraphe graphe, char *outfile) {
  FILE *fic;
  char commande[80];
  char dotfile[80]; /* le fichier dot pour cr´eer le ps */
  int ret;
  int nArcs = grapheNbArcs(graphe);
  int nSommets = grapheNbSommets (graphe);
  int estOriente = grapheEstOriente(graphe);
  char *delimiter;
  tNomSommet orig ;
  tNomSommet dest;

  tArc arc;
  /* on va créer un fichier pour graphviz, dans le fichier "outfile".dot */
  strcpy(dotfile, outfile);
  strcat(dotfile, ".dot");
  strcat(outfile, ".ps");

  fic = fopen(dotfile, "w");
  if (fic==NULL) {
    halt ("Ouverture du fichier %s en ´ecriture impossible\n", dotfile);
  }

  estOriente ? fprintf(fic, "digraph {\n"): fprintf(fic, "graph {\n");
  delimiter = estOriente ? "->" : "--";

  /* Ecrit tous les sommets du graphe */
  for (int i = 0; i < nSommets; i++) {
    grapheRecupNomSommet(graphe, i, orig);
    fprintf(fic, "%s;\n", orig);
  }

  /* Ajoute les liaisons du graphe */
  for(int i = 0; i< nArcs; i++){
    arc = grapheRecupArcNumero(graphe, i);
    grapheRecupNomSommet(graphe, arc.orig, orig);
    grapheRecupNomSommet(graphe, arc.dest, dest);
    fprintf(fic, "%s %s %s;\n", orig,delimiter, dest);
  }
  /* On ferme le graphe */
  fprintf(fic, "}\n");

  fclose(fic);
  sprintf(commande, "dot -Tps %s -o %s ", dotfile, outfile);
  ret = system(commande);
  if (WEXITSTATUS(ret)){
    halt("La commande suivante a ´echou´e\n%s\n", commande);
  }
}


int main(int argc, char *argv[]) {
  tGraphe graphe;

  if (argc<3) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }

  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  argv[1]);
  graphe2visu(graphe, argv[2]);

  grapheLibere(graphe);
  exit(EXIT_SUCCESS);
}
