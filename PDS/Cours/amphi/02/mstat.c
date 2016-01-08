#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    struct stat st;

    /* assert(stat(argv[1], &st) == 0); */
    assert(lstat(argv[1], &st) == 0);

    printf("%o\n", st.st_mode);

    if(S_ISREG(st.st_mode))
        printf("fichier normal\n");

    return 0;
}
