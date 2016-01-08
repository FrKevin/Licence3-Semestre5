#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGINT, &sa, NULL) == 0);

    while(1)
        pause();

    return 0;
}
