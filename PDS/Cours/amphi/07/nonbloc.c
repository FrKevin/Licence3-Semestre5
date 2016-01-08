#define __USE_GNU
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fds[2];
    char c;

    assert(pipe(fds) != -1);
    fcntl(fds[0], F_SETFL, fcntl(fds[0],F_GETFL) | O_NONBLOCK);
    /* assert(pipe2(fds, O_NONBLOCK) != -1); */

    if(read(fds[0], &c, 1) == -1)
        perror("lecture");

    return 0;
}
