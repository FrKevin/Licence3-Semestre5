#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TAILLE_TAMPON 1024

int main() {
    int sv[2];
    int lus;
    char tampon[TAILLE_TAMPON];

    assert(socketpair(AF_UNIX, SOCK_STREAM, 0, sv) != -1);

    switch (fork()) {
        case -1: exit(EXIT_FAILURE);

        case 0: /* Fils */
            close(sv[1]);
            printf("Fils: écrit « abc »\n");
            assert(write(sv[0], "abc", 3) == 3);
            /* close(sv[0]); */
            lus = read(sv[0], tampon, TAILLE_TAMPON-1);
            switch (lus) {
                case -1:
                    perror("Fils: Erreur de lecture");
                    exit(EXIT_FAILURE);
                case 0:
                    printf("Fils: fin de fichier\n");
                default:
                    tampon[lus] = '\0';
                    printf("Fils: lit « %s »\n", tampon);
            }
            exit(EXIT_SUCCESS);

        default: /* Père */
            close(sv[0]);
            sleep(2);
            /* close(sv[1]); */
            printf("Père: écrit « xyz »\n");
            assert(write(sv[1], "xyz", 3) == 3);
            lus = read(sv[1], tampon, TAILLE_TAMPON-1);
            assert(lus != -1);
            tampon[lus] = '\0';
            printf("Père: lit « %s »\n", tampon);
            exit(EXIT_SUCCESS);
    }

    return 0;
}
