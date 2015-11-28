#ifndef _PARCOURSLARGEUR_H_
#define _PARCOURSLARGEUR_H_

typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

void initCouleurs(tGraphe graphe, tTabCouleurs tabCouleurs);

void traitementSommet(tGraphe graphe, tNumeroSommet sommet, tFileSommets file, tTabCouleurs tabCouleurs);

void parcoursLargeur(tGraphe graphe, int noSommet, tTabCouleurs tabCouleurs);

#endif /* PARCOURSLARGEUR*/
