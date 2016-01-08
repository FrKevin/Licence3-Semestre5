#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    execl("/bin/ls", "ls", "-al", NULL);
    exit(EXIT_FAILURE);

    return 0;
}
