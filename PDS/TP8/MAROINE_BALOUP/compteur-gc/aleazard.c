/* Produit le génome d’un aléazard... */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define TAILLE_TAMPON 4096

char bases[] = { 'A', 'C', 'G', 'T' };

void convertit_bases(const char *binaires, char *lettres, unsigned long taille) {
    unsigned long i, j;

    for (i = 0; i < taille; i++) {
        j = i << 2;             /* j = 4 * i */

        lettres[j]     = bases[(binaires[i] >> 6) & 3];
        lettres[j + 1] = bases[(binaires[i] >> 4) & 3];
        lettres[j + 2] = bases[(binaires[i] >> 2) & 3];
        lettres[j + 3] = bases[ binaires[i]       & 3];
    }
}

#define min(a,b) ((a<b)?(a):(b))

int main(int argc, char *argv[]) {
    int fd, total, nb_bases, lus, prev_nb_bases;
    char binaires[TAILLE_TAMPON];
    char lettres[TAILLE_TAMPON * 4];

    if (argc < 2) {
        printf("Usage: %s <nb bases>\n", argv[0]);
        printf("Produit le génome d’un aléazard de la taille indiquée\n");
        exit(EXIT_FAILURE);
    }

    total = nb_bases = strtol(argv[1], NULL, 10);

    fd = open("/dev/urandom", O_RDONLY);
    assert(fd != -1);
    while (nb_bases > 0) {
        lus = read(fd, binaires, TAILLE_TAMPON);
        assert(lus > 0);
        convertit_bases(binaires, lettres, lus);
        write(STDOUT_FILENO, lettres, min(4 * lus, nb_bases));
        prev_nb_bases = nb_bases;
        nb_bases -= 4 * lus;
        
        if (total > 4000000 && nb_bases % (total/100) > prev_nb_bases % (total/100)) {
			fprintf(stderr, ".");
			fflush(stderr);
		}
    }
    close(fd);

    return 0;
}
