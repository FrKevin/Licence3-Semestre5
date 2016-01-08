#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>

void usr1(int sig) {
    printf("USR1 reçu\n");
}

int main(int argc, char *argv[]) {
    struct sigaction sa;

    sa.sa_handler = &usr1;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGUSR1, &sa, NULL) == 0);

    while(1)
        pause();

    return 0;
}
