#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char*argv[]) {
    int res;
    char nomfichier[10];

    if(argc < 2) {
        exit(2);
    }

    strcpy(nomfichier, "/tmp/");
    strncat(nomfichier, argv[1], 4);

    res = creat(nomfichier, S_IRWXU);
    if(res == -1) {
        perror("creat");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
