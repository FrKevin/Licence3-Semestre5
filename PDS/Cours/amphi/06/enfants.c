#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>

void enfants(int sig) {
    static int compteur = 0;

    compteur++;
    printf("%d-eme enfant terminé\n", compteur);

    /* Il faudrait donc : */
    /* while (waitpid(-1, &status, WNOHANG) ... ) { */
    /* ... */
    /* } */
}

int main(int argc, char *argv[]) {
    long int nb;
    struct sigaction sa;

    nb = strtol(argv[1], NULL, 10);
    for (; nb > 0; nb--) {
        switch (fork()) {
            case -1:
                exit(EXIT_FAILURE);

            case 0:
                printf("Fils %d\n", getpid());
                exit(EXIT_SUCCESS);
        }
    }

    sa.sa_handler = &enfants;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGCHLD, &sa, NULL) == 0);

    while(1)
        pause();

    return 0;
}
