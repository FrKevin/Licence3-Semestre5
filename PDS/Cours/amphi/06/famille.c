#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>

void ack(int sig) {
    printf("Signal reçu (%d)\n", getpid());
}

int main(int argc, char *argv[]) {
    struct sigaction sa;

    sa.sa_handler = &ack;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGINT, &sa, NULL) == 0);

    switch (fork()) {
        case -1:
            exit(EXIT_FAILURE);
        case 0:
            printf("Fils: %d\n", getpid());
            break;
        default:
            printf("Père: %d\n", getpid());
    }

    /* Cas particulier ! */
    /* Le père et le fils vont tous les deux exécuter le code suivant. */

    sleep(10);

    return 0;
}
