#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void f(int n) {
    int varlocale = 0x123456;

    if (n > 0) {
        printf("f(%d): &varlocale = %p\n", n, (void*)&varlocale);
        printf("      &n         = %p\n", (void*)&n);

        f(n-1);
    }
}

void affiche_pile_tas() {
    char commande[0x123];

    assert(snprintf(commande, 0x123,
                "cat /proc/%d/maps "
                "| sed 's/  */ /g' "
                "| grep -E '\\[heap\\]|\\[stack\\]'", getpid()) >= 0);
    printf("Exécution de la commande : %s\n", commande);
    assert(system(commande) != -1);
}

int globale = 10;

int main(int argc, char *argv[]) {
    char * buff;

    affiche_pile_tas();

    buff = (char*) malloc(0x456 * sizeof(char));

    printf("\n");
    affiche_pile_tas();

    printf("\n");
    printf("Adresse pointée par buff : %p\n", buff);
    printf("Adresse du pointeur buff : %p\n", (void*)&buff);
    printf("Adresse de la variable globale : %p\n", (void*)&globale);
    printf("\n");

    f(3);

    return 0;
}
