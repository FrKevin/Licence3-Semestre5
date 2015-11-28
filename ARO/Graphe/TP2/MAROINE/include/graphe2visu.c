#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "graphe.h"
#include "graphe2visu.h"

void graphe2visu(tGraphe graphe, char* outfile) {
  int file;
  char* c_arc;
  int nb_arcs;
  int nb_sommets;
  tArc g_arc;

  /* Sommet source et destination */
  char orig[LONG_NOM_SOMMET_MAX];
  char dest[LONG_NOM_SOMMET_MAX];
  char nom_sommet[LONG_NOM_SOMMET_MAX];

  /* Var used for the increment */
  int i;

  /* Buffer */
  char buffer[1024];
  int size_written;

  /* Orienté 1 ou non 0 */
  int oriente;

  /* Génération d"une image du graphe */
  file = open("./tmp.dot", O_CREAT | O_TRUNC | O_RDWR, 0666);

  oriente = graphe->estOriente;

  if(oriente == 1) {
    c_arc = " -> \0";
    if((size_written = write(file, "digraph {\n", 10))<0) {
      exit(EXIT_FAILURE);
    }
  }
  else {
    c_arc = " -- \0";
    if((size_written = write(file, "graph {\n", 8))<0) {
      exit(EXIT_FAILURE);
    }
  }

  nb_arcs = grapheNbArcs(graphe);
  nb_sommets = grapheNbSommets(graphe);


  for(i = 0; i<nb_sommets; ++i) {

    grapheRecupNomSommet(graphe, i, nom_sommet);

    if((size_written = snprintf(buffer, 1024, "%s;\n", nom_sommet))<0) {
      exit(EXIT_FAILURE);
    }

    write(file, buffer, size_written);
  }

  for(i = 0; i<nb_arcs; ++i) {
    g_arc = grapheRecupArcNumero(graphe, i);

    grapheRecupNomSommet(graphe, g_arc.orig, orig);
    grapheRecupNomSommet(graphe, g_arc.dest, dest);

    if((size_written = snprintf(buffer, 1024, "%s%s%s;\n", orig, c_arc, dest))<0) {
      exit(EXIT_FAILURE);
    }

    write(file, buffer, size_written);
  }

  if((size_written = write(file, "}", 1))<0) {
    exit(EXIT_FAILURE);
  }

  snprintf(buffer, 1024, "dot -Tps tmp.dot -o %s && rm tmp.dot", outfile);
  system(buffer);

  close(file);
  grapheLibere(graphe);
  return;
}

void graphe2visuCouleurs(tGraphe graphe, char* outfile, tTabCouleurs tabCouleurs) {
  int file;
  char* c_arc;
  int nb_arcs;
  int nb_sommets;
  tArc g_arc;

  /* Sommet source et destination */
  char orig[LONG_NOM_SOMMET_MAX];
  char dest[LONG_NOM_SOMMET_MAX];
  char nom_sommet[LONG_NOM_SOMMET_MAX];

  /* Var used for the increment */
  int i;

  /* Buffer */
  char buffer[1024];
  int size_written;

  /* Orienté 1 ou non 0 */
  int oriente;

  /* Génération d"une image du graphe */
  file = open("./tmpCol.dot", O_CREAT | O_TRUNC | O_RDWR, 0666);

  oriente = graphe->estOriente;

  if(oriente == 1) {
    c_arc = " -> \0";
    if((size_written = write(file, "digraph {\n", 10))<0) {
      exit(EXIT_FAILURE);
    }
  }
  else {
    c_arc = " -- \0";
    if((size_written = write(file, "graph {\n", 8))<0) {
      exit(EXIT_FAILURE);
    }
  }

  nb_arcs = grapheNbArcs(graphe);
  nb_sommets = grapheNbSommets(graphe);


  for(i = 0; i<nb_sommets; ++i) {

    grapheRecupNomSommet(graphe, i, nom_sommet);

    if((size_written = snprintf(buffer, 1024, "%s [color=%s];\n", nom_sommet, (tabCouleurs[i] == ROUGE) ? "red" : (tabCouleurs[i] == VERT) ? "green" : "blue"))<0) {
      exit(EXIT_FAILURE);
    }

    write(file, buffer, size_written);
  }

  for(i = 0; i<nb_arcs; ++i) {
    g_arc = grapheRecupArcNumero(graphe, i);

    grapheRecupNomSommet(graphe, g_arc.orig, orig);
    grapheRecupNomSommet(graphe, g_arc.dest, dest);

    if((size_written = snprintf(buffer, 1024, "%s%s%s;\n", orig, c_arc, dest))<0) {
      exit(EXIT_FAILURE);
    }

    write(file, buffer, size_written);
  }

  if((size_written = write(file, "}", 1))<0) {
    exit(EXIT_FAILURE);
  }

  snprintf(buffer, 1024, "dot -Tps tmpCol.dot -o %s && rm tmpCol.dot", outfile);
  system(buffer);

  close(file);
  grapheLibere(graphe);
  return;
}
