#include <unistd.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fds[2];
    char c;

    assert(pipe(fds) != -1);

    if(write(fds[0], &c, 1) == -1)
        perror("erreur d’écriture sur 0");
    if(write(fds[1], &c, 1) == -1)
        perror("erreur d’écriture sur 1");

    if(read(fds[0], &c, 1) == -1)
        perror("erreur de lecture sur 0");
    if(read(fds[1], &c, 1) == -1)
        perror("erreur de lecture sur 1");

    return 0;
}
