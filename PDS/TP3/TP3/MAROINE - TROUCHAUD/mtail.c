/*
GROUPE 4
MAROINE Maxime, TROUCHAUD Alexandre
PDS TP3
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 500

typedef enum { false, true } bool;

bool opt_manual_limited_lines = false;
int nb_lines_wanted = 5;

int opt_path_c;
char** opt_path_v;

char buffer[BUFFER_SIZE];
int nb_lines = 0;

void analyseArgs(int argc, char** argv);
int count_lines(char* buffer, int buffer_size);
int read_file(char* pathname);
void display_lines(char* pathname, int line_to_read);

int main(int argc, char** argv) {
    analyseArgs(argc, argv);
    read_file(opt_path_v[0]);
    display_lines(opt_path_v[0], nb_lines_wanted);
    return 0;
}

/*
 * Analyse des arguments
 */
void analyseArgs(int argc, char** argv) {
    int optch;
    int numeric_value = 0;
    extern int opterr;
    
    /* chaine contenant les caractères des arguments */
    char format[] = "n:";

    opterr = 1;
    
    /* on parcours des arguments */
    while ((optch = getopt(argc, argv, format)) != -1)
        switch (optch) {
            case 'n':
                assert((numeric_value = atoi(optarg)) > 0);
                nb_lines_wanted = numeric_value;
                break;
        }
    
    if(optind >= argc) {
        printf("Pas assez d'argument\n");
        exit(EXIT_FAILURE);
    }
    /* lis les derniers arguments, qui sont des chemins d'accès */
    opt_path_c = argc - optind;
    opt_path_v = &(argv[optind]);
}

/*
Fonction qui compte le nombre de lignes
*/
int count_lines(char* buffer, int buffer_size) {
    int count = 0;
    int i = 0;
    for(i = 0; i<buffer_size; i++) {
        if(buffer == NULL) return -1;
        if(buffer[i] == '\n') count++;
    }
    return count;
}

/*
Fonction lisant l'entièreté du fichier entré en paramètre
*/
int read_file(char* pathname) {
    int file;
    int res = 0;
    int bytes_read = 0;

    file = open(pathname, O_RDONLY | O_CREAT);
    assert(file > 0);
    
    while((bytes_read = read(file, buffer, sizeof(char)*BUFFER_SIZE))) {
        assert(bytes_read != 0);
        res = count_lines(buffer, bytes_read);
        if(res >=0) {
            nb_lines+=res;
        }

    }
    close(file);
    return 0;
}

/*
Lis le nombre de lignes demandées
*/
void display_lines(char* pathname, int line_to_read) {
    int i = 0;
    int file;
    int line_passed = 0;
    int bytes_read = 0;
    int limit_to_read = nb_lines - line_to_read;

    file = open(pathname, O_RDONLY | O_CREAT);
    assert(file > 0);

    while((bytes_read = read(file, buffer, sizeof(char)*BUFFER_SIZE))) {
        assert(bytes_read > 0);
        for(i = 0; i < bytes_read; i++) {
            if(line_passed>limit_to_read)
                printf("%c", buffer[i]);
            if(buffer[i] == '\n') 
                line_passed++;
        }
    }
    close(file);
}