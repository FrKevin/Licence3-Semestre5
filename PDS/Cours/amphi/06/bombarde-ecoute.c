#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

/* Compteur de signaux reçus */

int compteur = 0;

void usr1(int sig) {
    compteur++;
}

void usr2(int sig) {
    printf("%d\n", compteur);
}

int main(int argc, char *argv[]) {
    struct sigaction sa;

    sa.sa_handler = &usr1;
    sa.sa_flags = 0;
    assert(sigfillset(&sa.sa_mask) == 0);
    assert(sigaction(SIGUSR1, &sa, NULL) == 0);

    sa.sa_handler = &usr2;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGUSR2, &sa, NULL) == 0);

    printf("%d\n", getpid());
    fflush(stdout);

    while(1)
        pause();

    return 0;
}
