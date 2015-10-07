#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

/* /\ ATTENTION => Ne jamais printf un buffer de read, car il ne met pas de caractère de fin \0 */

/* Constante */

#define SIZE_OF_BUFFER 10

/* Fin Constante */

const char* pathname;

static long ntail = 10;


int is_file(const char *pathname){
  struct stat st;
  int status;

  status = stat(pathname, &st);
  assert(status == 0);
  return S_ISREG(st.st_mode);
}

int index_tail_buffer(const char *buffer, int bufsize,
                      int ntail, int *nlines) {

    int nlines_current = 0;
    int index_tail = 0;
    assert(buffer && ntail);
    for(index_tail=bufsize-1; index_tail >= 0; --index_tail) {
      if(buffer[index_tail] == '\n') {
        nlines_current++;
      }

      if(nlines_current == ntail) {
        *nlines = nlines_current;
        return index_tail;
      }
    }
    *nlines = nlines_current;
    return -1;
}


long get_last_octet(int fd, int pos) {
  int loctet = lseek(fd, 0, SEEK_END);
  assert(loctet != -1);
  assert(lseek(fd, 0, SEEK_SET) != -1);
  return loctet;
}

void check_args(int argc, const char * argv[]){
  assert(argc > 1);
  if(is_file(argv[1])){
    pathname = argv[1];
    if(argc > 2)
      ntail = atoi(argv[3]); // ATOI
  }
  else{
    perror("Ce n'est pas un fichier !");
    exit(EXIT_FAILURE);
  }
}

int check_read(int rstatus) {
  if(rstatus == -1) {
    perror("Erreur sur read");
    return 0;
  }
  return 1;
}

/*
 *  Ecrit sur la sortie
 */
void print_buffer(const char* buffer, int bufsize){
    assert (write(STDOUT_FILENO, buffer, bufsize) !=-1);
}

/*
 * Déplace la tête de lecteur d'un différence de size
 */
int tail_before_pos(int df, unsigned int pos, int ntail){
  int status;
  int nlines;
  int index_tail_buff;
  int pseek;
  int noctet_read;
  char buffer[SIZE_OF_BUFFER];
  if(pos < SIZE_OF_BUFFER) {
    pseek = pos;
  }
  else {
    pseek = pos - SIZE_OF_BUFFER;
  }
  lstatus = lseek(df, pseek, SEEK_SET);
  assert(lstatus != -1));
  noctet_read = read(df, &buffer, SIZE_OF_BUFFER);
  if(noctet_read != SIZE_OF_BUFFER) {
    assert(check_read(noctet_read));
    if(lstatus) {
      fprintf(stderr, "%s\n", "Probleme de lecture, octets manquants");
      exit(EXIT_FAILURE);
    }
  }
  index_tail_buff = tail_before_pos(buffer, noctet_read, ntail, &nlines);
  if(index_tail_buff == -1) { /* Cas de recursion n < ntail, donc imprime tout le buffer */
    lstatus = lseek(df, -noctet_read, SEEK_CUR); /* Tete de lecture remise avant le read */
    assert(lstatus != -1);
    tail_before_pos(df, pos-noctet_read, ntail-nlines);
    print_buffer(buffer, noctet_read);
  }
  else {
    buffer = buffer + index_tail_buff;
    print_buffer(buffer, SIZE_OF_BUFFER-index_tail_buff);
  }
  return 1;
}

void tail(){
  int df;
  int nb_octet_file;
  df = open(pathname, O_RDONLY);
  assert(df != -1);
  /* 1) On recupere le dernier octet du fichier */
  noctet_file = get_last_octet(df);

  assert(tail_before_pos(df, noctet_file, ntail) != -1);
  /* On libère la mémoire */
  assert(close(df) != -1);

}

int main(int argc,const char* argv[]) {
  check_args(argc, argv);
  tail();
  return EXIT_SUCCESS;
}
