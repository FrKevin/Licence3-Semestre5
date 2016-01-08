#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>

/* Compteur de signaux reçus */

int main(int argc, char *argv[]) {
    pid_t pid;
    long iter;

    pid = (pid_t)strtol(argv[1], NULL, 10);
    iter = strtol(argv[2], NULL, 10);

    for(; iter > 0; iter--)
        assert(kill(pid, SIGUSR1) == 0);

    assert(kill(pid, SIGUSR2) == 0);

    return 0;
}
