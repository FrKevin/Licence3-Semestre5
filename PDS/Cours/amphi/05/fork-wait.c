#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    pid_t pid, pid2;
    int status;
    /* char * buff = NULL; */

    switch(pid = fork()) {
        case -1:
            exit(EXIT_FAILURE);

        case 0:
            /* fils */
            printf("fils: %d (mon père: %d)\n", getpid(), getppid());
            /* sleep(1); */
            /* *buff = '1'; */
            exit(0x1234);

        default:
            /* père */
            printf("père: %d (mon père: %d)\n", getpid(), getppid());
            pid2 = wait(&status);
            assert(pid2 != -1);
            if(WIFEXITED(status))
                printf("Valeur de retour: %x\n", WEXITSTATUS(status));
            if(WIFSIGNALED(status))
                printf("Signal: %d\n", WTERMSIG(status));

    }

    return 0;
}
