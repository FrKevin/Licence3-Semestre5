#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]) {
    int res;
    res = creat("/tmp/test", S_IRWXU);
    if(res == -1) {
        perror("creat");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
