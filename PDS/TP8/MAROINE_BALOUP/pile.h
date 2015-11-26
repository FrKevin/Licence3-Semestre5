#ifndef _PILE_H_
#define _PILE_H_

#include <stdint.h>

typedef int32_t pos_t;          /* type des positions dans le tableau */

/* Pile */
/* Implémentation simple d’une pile de taille bornée */

/* Les noms des valeurs dans la pile indique que cette implémentation
 * est destinée à contenir des intervalles de positions dans un
 * tableau */

#define TAILLE_PILE 128

typedef struct bloc_s {
    pos_t debut, fin;
}   bloc_t;

typedef struct pile_s {
    unsigned int dessus;
    bloc_t contenu[TAILLE_PILE];
}   pile;

void   init_pile (pile *);
int    pile_vide (pile *);
void   empile    (pile *, bloc_t);
bloc_t depile    (pile *);
#endif
