#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#define BSIZE 1048576

/* Le dernier exemple montré en cours, avec l’argument 100000, était
 * effectué avec un tableau buf de taille 1024, donc un débordement.
 * Le comportement sans débordement n’a pas de raison d’être
 * identique... */

int main (int argc, char *argv[]) {
    int fds[2];
    char buf[BSIZE];
    int n;
    n = atol(argv[1]);
    assert(n<=BSIZE);
    assert(pipe(fds) != -1);

    for(;;) {
        printf("w%ld ", write(fds[1], buf, n));
        fflush(stdout);
        printf("r%ld ", read(fds[0], buf, 256));
        fflush(stdout);
    }

    exit(EXIT_SUCCESS);
}
