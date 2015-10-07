#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void print_buffer(const char* buffer, int bufsize){
    assert (write(STDOUT_FILENO, buffer, bufsize) !=-1);
}

/* A voir */
int is_line_all_space(const char *buffer, int a, int b) {
  int is_line_all_space = 1;
  int i;
  for(i=a; i < b && is_line_all_space; ++i) {
    is_line_all_space = buffer[i] == ' ';
  }
  return is_line_all_space;
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
