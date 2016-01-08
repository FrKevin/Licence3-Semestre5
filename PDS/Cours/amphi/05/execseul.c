#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    execlp("ls", "ls", "-al", NULL);
    /* execlp("eaieauils", "ls", "-al", NULL); */
    exit(EXIT_FAILURE);

    return 0;
}
