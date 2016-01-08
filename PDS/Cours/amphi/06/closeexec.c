#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    close(STDOUT_FILENO);
    execl("/bin/ls", "ls", "-al", NULL);
    exit(EXIT_FAILURE);

    return 0;
}
