#include <stdint.h>
#include <assert.h>
#include "pile.h"

void init_pile(pile * p) {
    p->dessus = 0;
    pthread_mutex_init(&(p->mutex), NULL);
}

int pile_vide(pile * p) {
	int ret;
	pthread_mutex_lock(&(p->mutex));
    ret = p->dessus == 0;
	pthread_mutex_unlock(&(p->mutex));
	return ret;
}

bloc_t depile(pile * p) {
	bloc_t ret;
	pthread_mutex_lock(&(p->mutex));
	assert(p->dessus > 0);
    p->dessus--;
    ret = p->contenu[p->dessus];
	pthread_mutex_unlock(&(p->mutex));
    return ret;
}

void empile(pile * p, bloc_t e) {
	pthread_mutex_lock(&(p->mutex));
    assert(p->dessus < TAILLE_PILE);
    p->contenu[p->dessus] = e;
    p->dessus++;
	pthread_mutex_unlock(&(p->mutex));
}
