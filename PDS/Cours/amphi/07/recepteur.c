#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void usr1(int sig) {
    printf("USR1 reçu\n");
}

void usr2(int sig) {
    printf("USR2 reçu\n");
}

void cont(int sig) {
    printf("CONT reçu\n");
}

int main(int argc, char *argv[]) {
    struct sigaction sa;

    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    sa.sa_handler = &usr1;
    assert(sigaction(SIGUSR1, &sa, NULL) == 0);
    sa.sa_handler = &usr2;
    assert(sigaction(SIGUSR2, &sa, NULL) == 0);
    sa.sa_handler = &cont;
    assert(sigaction(SIGCONT, &sa, NULL) == 0);

    while(1)
        pause();

    return 0;
}
