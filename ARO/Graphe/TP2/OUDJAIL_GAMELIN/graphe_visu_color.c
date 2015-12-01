#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sys/wait.h" /* n´ecessaire pour la macro WEXITSTATUS */
#include "../lib/graphe.h"
#include "graphe_visu_color.h"

void graphe_visu_color(tGraphe graphe,tTabCouleurs tab_couleur, char *outfile) {
  FILE *fic;
  char commande[80];
  char dotfile[80]; /* le fichier dot pour cr´eer le ps */
  char psfile[80];
  int ret;
  int nArcs = grapheNbArcs(graphe);
  int nSommets = grapheNbSommets (graphe);
  int estOriente = grapheEstOriente(graphe);
  char *delimiter;
  tNomSommet orig ;
  tNomSommet dest;
  static char* char_colors[3];
  tArc arc;

  char_colors[0] = "red";
  char_colors[1] = "blue";
  char_colors[2] = "green";

   /* on va créer un fichier pour graphviz, dans le fichier "outfile".dot */
  strcpy(dotfile, outfile);
  strcpy(psfile, outfile);
  strcat(dotfile, ".dot");
  strcat(psfile, ".ps");

  fic = fopen(dotfile, "w");
  if (fic==NULL) {
    halt ("Ouverture du fichier %s en ´ecriture impossible\n", dotfile);
  }

  estOriente ? fprintf(fic, "digraph {\n"): fprintf(fic, "graph {\n");
  delimiter = estOriente ? "->" : "--";

  /* Ecrit tous les sommets du graphe */
  for (int i = 0; i < nSommets; i++) {
    grapheRecupNomSommet(graphe, i, orig);
    fprintf(fic, "%s [color=%s];\n", orig, char_colors[tab_couleur[i]]);
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
  sprintf(commande, "dot -Tps %s -o %s ", dotfile, psfile);
  ret = system(commande);
  if (WEXITSTATUS(ret)){
    halt("La commande suivante a ´echou´e\n%s\n", commande);
  }
}
