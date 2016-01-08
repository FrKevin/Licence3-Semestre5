#include <unistd.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
    pthread_exit(NULL);

    return 100;
}
