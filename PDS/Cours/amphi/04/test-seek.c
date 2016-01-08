#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(lseek(STDIN_FILENO, 0, SEEK_SET) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    };

    return 0;
}
