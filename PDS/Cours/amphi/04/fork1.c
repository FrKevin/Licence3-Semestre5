#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    pid_t pid;

    pid = fork();
    switch(pid) {
        case -1:
            exit(EXIT_FAILURE);

        case 0:
            /* fils */
            printf("fils: %d (mon père: %d)\n", getpid(), getppid());
            exit(EXIT_SUCCESS);

        default:
            printf("père: %d (mon père: %d)\n", getpid(), getppid());
            /* père */
    }

    return 0;
}
