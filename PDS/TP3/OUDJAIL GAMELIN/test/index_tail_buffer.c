#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


static int lline_no_void = 0;

char get_char_bypoct(int df, int poctet) {
  int rstatus;
  int hcurrent;
  char get_char[1];
  hcurrent = lseek(df, 0, SEEK_CUR);
  assert(hcurrent != -1);
  assert(lseek(df, poctet, SEEK_SET) != -1);
  rstatus = read(df, get_char, 1);
  assert(check_read(rstatus, 1));
  assert(lseek(df, hcurrent, SEEK_SET) != -1);
  return get_char[0];
}

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
  char get_char[1];
  rstatus = read(df, get_char, 1);
  assert(check_read(rstatus, 1));
  return get_char[0];
}

void print_buffer(const char* buffer, int bufsize){
    assert (write(STDOUT_FILENO, buffer, bufsize) !=-1);
}

/* A voir */
int get_lline_no_void(const char *buffer, int bufsize) {
  int i;
  for(i=bufsize-1; i >= 0; ++i) {
    if(buffer[i] != '\n') {
      return i;
    }
  }
  return 0; /* Ou i ^^ */
}

int get_size_buffer(const char *buffer, int bufsize) {
  if(!lline_no_void) {
    lline_no_void = get_lline_no_void(buffer, bufsize);
    return lline_no_void;
  }
  return bufsize;
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

int main(int argc, char const *argv[]) {
  /* code */

  char *buffer = "test\nprout\ntoto";
  char *nbuffer;
  int nlines;
  int index_tail_buff = index_tail_buffer(buffer, strlen(buffer), 2, &nlines);
  printf("%d : %d\n", index_tail_buff, nlines);
  nbuffer = buffer + 4;
  print_buffer(nbuffer, strlen(buffer)-4);
  printf("\n");
  int df = open(argv[1], O_RDONLY);
  int tete_lecture = lseek(df, 0, SEEK_END);
  lseek(df, 0, SEEK_SET);
  printf("%d\n", tete_lecture);
  tete_lecture = lseek(df, 0, SEEK_CUR);
  printf("%d\n", tete_lecture);
  printf("Macro SEEK_SET : %d\n", SEEK_SET);
  printf("Macro SEEK_CUR : %d\n", SEEK_CUR);
  printf("Macro SEEK_END : %d\n", SEEK_END);

  printf("%s\n", "Test get_last_octet");
  tete_lecture = lseek(df, 3, SEEK_SET);
  printf("Tete de lecture courant : %d\n", tete_lecture);

  int loctet_file = get_last_octet(df);
  printf("Dernier octet du fichier : %d\n", loctet_file);
  tete_lecture = lseek(df, 0, SEEK_CUR);
  printf("Position de la tete de lecture apres l'apelle : %d\n", tete_lecture);

  return 0;
}
