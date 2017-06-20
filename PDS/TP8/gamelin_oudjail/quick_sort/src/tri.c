#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "main.h"
#include "tri.h"

void verifie_trie(base_t * tableau, pos_t taille) {
    pos_t i;

    if (opt_verbeux)
        fprintf(stderr, "Vérification du tableau trié\n");

    for (i = 0; i < taille - 1; i++)
        if (tableau[i] > tableau[i + 1])
            fprintf(stderr, "Erreur de tri à la position %d !\n", i);

    if (opt_verbeux)
        fprintf(stderr, "Vérification du tableau effectuée avec succès\n");
}

base_t *charge_tableau_binaire(char *fichier, long longueur) {
    int fd;
    base_t *tableau;
    char *tab;
    long lus, pos;

    tableau = (base_t *) malloc(longueur * sizeof(base_t));
    assert(tableau != NULL);

    if (fichier == NULL)
        fd = STDIN_FILENO;
    else {
        fd = open(fichier, O_RDONLY);
        assert(fd != -1);
    }

    pos = longueur * sizeof(base_t);

    tab = (char *) tableau;
    while (pos > 0 && (lus = read(fd, tab, pos)) > 0) {
        tab += lus;
        pos -= lus;
    }
    assert(lus > 0);

    if (fichier != NULL)
        close(fd);

    return tableau;
}

base_t *charge_tableau_textuel(char *fichier, long longueur) {
    FILE *f;
    base_t *tableau;
    int i;

    tableau = (base_t *) malloc(longueur * sizeof(base_t));
    assert(tableau != NULL);

    if (fichier == NULL)
        f = stdin;
    else {
        f = fopen(fichier, "r");
        assert(f != NULL);
    }

    for (i = 0; i < longueur; ++i)
        assert(fscanf(f, FMT_BASE_T, (CAST_BASE_T_PTR) &tableau[i]) > 0);

    if (fichier != NULL)
        fclose(f);

    return tableau;
}

void affiche_tableau_binaire(base_t *tableau, long longueur) {
    write(STDOUT_FILENO, tableau, longueur);
}

void affiche_tableau_textuel(base_t *tableau, long longueur) {
    long i;

    if (longueur < 1)
        return;

    printf(FMT_BASE_T, (CAST_BASE_T) tableau[0]);
    for (i = 1; i < longueur; i++) {
        if (i % 10 == 0)
            printf("\n");
        else
            printf(" ");
        printf(FMT_BASE_T, (CAST_BASE_T) tableau[i]);
    }
    printf("\n");
}
