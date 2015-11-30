#include <stdint.h>
#include <assert.h>
#include "pile.h"

void init_pile(pile * p) {
    p->dessus = 0;
}

int pile_vide(pile * p) {
    return p->dessus == 0;
}

bloc_t depile(pile * p) {
    assert(p->dessus > 0);
    p->dessus--;
    return p->contenu[p->dessus];
}

void empile(pile * p, bloc_t e) {
    assert(p->dessus < TAILLE_PILE);
    p->contenu[p->dessus] = e;
    p->dessus++;
}
