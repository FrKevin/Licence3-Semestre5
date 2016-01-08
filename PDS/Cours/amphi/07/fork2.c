#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct exemp {
    int a;
    int b;
};

int main(int argc, char *argv[]) {
    int fd[2];
    struct exemp s;
    int lus,i;

    assert(pipe(fd) != -1);

    switch (fork()) {
        case -1: exit(EXIT_FAILURE);

        case 0:
            close(fd[1]);
            while ((lus = read(fd[0],&s,sizeof(struct exemp))) > 0) {
                assert(lus == sizeof(struct exemp));
                printf("%d, %d\n", s.a, s.b);
                fflush(stdout);
            }
            if(lus == -1)
                perror("erreur de lecture");
            exit(EXIT_SUCCESS);

        default: /* Père */
            close(fd[0]);
            for (i = 0; i < 100; i++) {
                s.a = i;
                s.b = i + 1;
                assert(write(fd[1], &s, sizeof(struct exemp)) != -1);
                usleep(10000);
            }
            exit(EXIT_SUCCESS);
    }

    return 0;
}
