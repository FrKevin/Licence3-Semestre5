#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char * tampon = NULL;

    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGSEGV, &sa, NULL) == 0);

    tampon[0] = 'a';

    return 0;
}
