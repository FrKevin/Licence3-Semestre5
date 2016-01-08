#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void ecoute(int fd) {
    char donnee;
    int res, cptr;

    while((res=read(fd, &donnee, 1)) > 0) {
        putchar(donnee);
        cptr = (cptr+1) % 50;
        if(cptr == 0) {
            putchar('\n');
        }
        fflush(stdout);
    }
    printf("père sort avec le résultat : %d\n", res);
    exit(EXIT_FAILURE);
}

void parle(int fd, char c, int nb) {
    char * tampon;
    int res;

    assert(nb >= 2);
    assert((tampon = malloc(nb)) != NULL);
    if(nb>2)
        memset(tampon+1, c, nb-2);
    tampon[0] = '(';
    tampon[nb-1] = ')';

    while(1) {
        res = write(fd, tampon, nb);
        assert(res != -1);
        if(res < nb)
            fprintf(stderr, "écriture partielle : %d/%d\n", res, nb);
        usleep(10000);
    }
}

int main(int argc, char *argv[]) {
    int fd[2];
    int nb;

    nb = strtol(argv[1], NULL, 10);

    assert(pipe(fd) != -1);

    switch(fork()) {
        case -1: abort();
        case 0:
                 parle(fd[1], '-', nb);
                 exit(EXIT_FAILURE);
    }

    switch(fork()) {
        case -1: abort();
        case 0:
                 parle(fd[1], '+', nb);
                 exit(EXIT_FAILURE);
    }

    ecoute(fd[0]);
    return 0;
}


