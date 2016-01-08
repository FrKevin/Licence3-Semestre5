#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    assert(access(argv[1], R_OK | W_OK) == 0);

    return 0;
}
