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

static const char* pathname;

static long ntail = 10;




int check_read(int rstatus, int wait_noctet_read) {
  if(rstatus == -1) {
    perror("Erreur sur read");
    return 0;
  }
  if (rstatus != wait_noctet_read) {
    perror("Erreur sur read, octets manquant en lecture");
    return 0;
  }
  return 1;
}

char get_char_bypoct(int df, int poctet) {
  int rstatus;
  int hcurrent;
  char get_char[1];
  hcurrent = lseek(df, 0, SEEK_CUR);
  assert(hcurrent != -1);
  assert(lseek(df, poctet, SEEK_SET) != -1);
  rstatus = read(df, get_char, 1);
  assert(check_read(rstatus, 1));
  assert(lseek(df, hcurrent, SEEK_SET));
  return get_char[0];
}


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


long get_last_octet(int fd) {
  int loctet;
  int hcurrent;
  hcurrent = lseek(fd, 0, SEEK_CUR);
  assert(hcurrent != -1);
  loctet= lseek(fd, 0, SEEK_END);
  assert(loctet != -1);
  assert(lseek(fd, hcurrent, SEEK_SET) != -1);
  return loctet;
}

void analyse_args(int argc, const char * argv[]){
  assert(argc > 1);
  if(is_file(argv[1])){
    pathname = argv[1];
    if(argc > 2)
      ntail = abs(atoi(argv[3])); /* Apparemement deprecié pour strtoi */
  }
  else{
    perror("Ce n'est pas un fichier !");
    exit(EXIT_FAILURE);
  }
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
  int lstatus;
  int nlines;
  int index_tail_buff;
  int pseek;
  int noctet_read;
  int wait_noctet_read;
  char buffer[SIZE_OF_BUFFER];
  char *nbuffer;
  if(pos == 0) { /* Cas d'arret, fin de fichier */
    return 1;
  }
  if(pos < SIZE_OF_BUFFER) {
    pseek = 0;
    wait_noctet_read = pos;
  }
  else {
    pseek = pos - SIZE_OF_BUFFER;
    wait_noctet_read = SIZE_OF_BUFFER;
  }
  lstatus = lseek(df, pseek, SEEK_SET);
  assert(lstatus != -1);
  noctet_read = read(df, &buffer, wait_noctet_read);
  assert(check_read(noctet_read, wait_noctet_read));
  index_tail_buff = index_tail_buffer(buffer, noctet_read, ntail, &nlines);
  if(index_tail_buff == -1) { /* Cas de recursion n < ntail, donc imprime tout le buffer */
    lstatus = lseek(df, -noctet_read, SEEK_CUR); /* Tete de lecture remise avant le read */
    assert(lstatus != -1);
    tail_before_pos(df, pos-noctet_read, ntail-nlines);
    print_buffer(buffer, noctet_read);
  }
  else {
    nbuffer = buffer + index_tail_buff;
    print_buffer(nbuffer, noctet_read-index_tail_buff);
  }
  return 1;
}

void tail(){
  int df;
  int loctet_file;
  df = open(pathname, O_RDONLY);
  assert(df != -1);
  /* On recupere le dernier octet du fichier */
  loctet_file = get_last_octet(df);
  if(get_char_bypoct(df, loctet_file) == '\n') {
    --loctet_file;
  }
  /* On, appelle la fonction tail_before_pos qui va imprimer les derniere ligne recurcivement */
  assert(tail_before_pos(df, loctet_file, ntail) != -1);
  /* On libère la mémoire */
  assert(close(df) != -1);
}

int main(int argc,const char* argv[]) {
  analyse_args(argc, argv);
  tail();
  printf("\n");
  fflush(stdout);
  return EXIT_SUCCESS;
}
