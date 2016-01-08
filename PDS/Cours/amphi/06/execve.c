#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *env[]) {
    char *env_argv[2];
    char *env_env[2];

    env_argv[0] = "env";
    env_argv[1] = NULL;

    env_env[0] = "PATH=/bin:/usr/bin";
    env_env[1] = NULL;

    /* execve("/usr/bin/env", env_argv, env); */
    execve("/usr/bin/env", env_argv, env_env);
    exit(EXIT_FAILURE);

    /* Juste pour -Wall... */
    /* printf("%s\n", env_env[0]); */

    return 0;
}
