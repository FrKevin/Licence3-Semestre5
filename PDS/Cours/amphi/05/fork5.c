#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Post-mortem */

void affiche_etat(int pid) {
    char commande[0x123];

    assert(snprintf(commande, 0x123, "cat /proc/%d/status | grep -E '^State:'", pid) >= 0);
    assert(system(commande) != -1);
}

int main(int argc, char *argv[]) {
    pid_t pid;

    switch(pid = fork()) {
        case -1:
            exit(EXIT_FAILURE);

        case 0:
            /* fils */
            printf("fils: %d (mon père: %d)\n", getpid(), getppid());

            printf("fils: ");
            fflush(stdout);
            affiche_etat(getpid());
            printf("père: ");
            fflush(stdout);
            affiche_etat(getppid());

            exit(EXIT_SUCCESS);

        default:
            /* père */
            printf("père: %d (mon père: %d)\n", getpid(), getppid());
    }

    return 0;
}
