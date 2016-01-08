#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int fd[2];
    char c;
    int lus ;
    /* int i; */

    assert(pipe(fd) != -1);

    switch (fork()) {
        case -1: exit(EXIT_FAILURE);

        case 0:
            /* exit(EXIT_SUCCESS); */

            /* close(fd[1]); */

            while ((lus = read(fd[0],&c,1)) > 0) {
                putchar(c);
                fflush(stdout);
            }
            if(lus == -1)
                perror("erreur de lecture");

            printf("Le fils (lecteur) se termine\n");
            exit(EXIT_SUCCESS);

        default: /* Père */
            /* close(fd[0]); */

            /* for (i = 0; i < 100; i++) { */
            while (1) {
                assert(write(fd[1], ".", 1) != -1);
                usleep(10000);
            }

            printf("Le père (écrivain) se termine\n");
            exit(EXIT_SUCCESS);
    }

    return 0;
}
