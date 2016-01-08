#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>

void echo(int sig) {
    printf("Signal reçu : %d\nMême pas mal\n", sig);
}

int main(int argc, char *argv[]) {
    struct sigaction sa;

    sigset_t masque;

    assert(sigemptyset(&masque) == 0);
    assert(sigaddset(&masque, SIGINT) == 0);
    assert(sigprocmask(SIG_BLOCK, &masque, NULL) == 0);

    sa.sa_handler = &echo;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGINT, &sa, NULL) == 0);

    while(1)
        pause();

    return 0;
}
