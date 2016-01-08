#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    DIR *rep;
    struct dirent *entree;
    struct stat st;
    char chemin[PATH_MAX+1];
    char cible[PATH_MAX+1];
    int nb;

    rep = opendir(argv[1]);
    assert(rep != NULL);

    while((entree = readdir(rep)) != NULL) {
        printf("%d %s", (int)(entree -> d_ino), entree -> d_name);

        snprintf(chemin, PATH_MAX+1, "%s/%s", argv[1], entree -> d_name);

        assert(lstat(chemin, &st) == 0);
        if(S_ISLNK(st.st_mode)) {
            nb = readlink(chemin, cible, PATH_MAX);
            assert(nb != -1);
            cible[nb] = '\0';
            printf(" -> %s", cible);
        }
        printf("\n");
    }

    closedir(rep);

    return 0;
}
