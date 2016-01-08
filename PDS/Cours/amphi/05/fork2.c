#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Partage ? */

int main(int argc, char *argv[]) {
    pid_t pid;
    int i = 123;

    switch(pid = fork()) {
        case -1:
            exit(EXIT_FAILURE);

        case 0:
            /* fils */
            printf("fils: %d (mon père: %d)\n", getpid(), getppid());
            printf("fils: i = %d (adresse: %p)\n", i, (void*)&i);
            exit(EXIT_SUCCESS);

        default:
            /* père */
            printf("père: %d (mon père: %d)\n", getpid(), getppid());
            printf("père: i = %d (adresse: %p)\n", i, (void*)&i);
    }

    return 0;
}
