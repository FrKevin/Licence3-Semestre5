#include "sys/wait.h"
/* N´ecessaire pour la macro WEXITSTATUS */
void graphe2visu(tGraphe graphe, char *outfile) {
  FILE *fic;
  char commande[80];
  char dotfile[80]; /* le fichier dot pour cr´eer le ps */
  int ret;
  /* on va cr´eer un fichier pour graphviz, dans le fichier "outfile".dot */
  strcpy(dotfile, outfile);
  strcat(dotfile, ".dot");
  fic = fopen(dotfile, "w");
  if (fic==NULL)
    halt ("Ouverture du fichier %s en ´ecriture impossible\n", dotfile);
  /*
  on parcourt le graphe pour en tirer les informations
  n´ecessaires pour graphviz.
  Pour ´ecrire dans le fichier, on utilise fprintf (qui s’utilise
  comme printf mais on mettant en plus fic comme premier param`etre).
  Ex :
  fprintf(fic, "graph {\n");
  ou
  fprintf(fic, " %s -> %s\n", origine, destination);
  */
  fclose(fic);
  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if (WEXITSTATUS(ret))
  halt("La commande suivante a ´echou´e\n%s\n", commande);
}
