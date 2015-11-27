#ifndef _TRI_H_
#define _TRI_H_

#include "pile.h"

typedef int64_t base_t;         /* type des valeurs à trier */
#define FMT_BASE_T      "%ld"
#define CAST_BASE_T     long int
#define CAST_BASE_T_PTR long int *

void verifie_trie(base_t * tableau, pos_t taille);
base_t *charge_tableau_binaire(char *fichier, long longueur);
base_t *charge_tableau_textuel(char *fichier, long longueur);
void affiche_tableau_binaire(base_t *tableau, long longueur);
void affiche_tableau_textuel(base_t *tableau, long longueur);

#endif
