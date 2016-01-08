#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[], char *env[]) {
    char **envp = env;

    while(*envp != NULL) {
        printf("%s\n", *envp);
        envp++;
    }

    printf("\n%s\n", getenv("PATH"));

    return 0;
}

