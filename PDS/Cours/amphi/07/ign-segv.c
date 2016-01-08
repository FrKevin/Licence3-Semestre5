#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char * tampon = NULL;

    sigset_t mask;

    assert(sigemptyset(&mask) == 0);
    assert(sigaddset(&mask, SIGSEGV) == 0);
    assert(sigprocmask(SIG_BLOCK, &mask, NULL) == 0);

    tampon[0] = 'a';

    return 0;
}
