#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


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
        return index_tail;
      }
    }
    *nlines = nlines_current;
    return -1;
}

int main(int argc, char const *argv[]) {
  /* code */

  char *buffer = "test\nprout\ntoto";
  int nlines;
  int index_tail_buff = index_tail_buffer(buffer, strlen(buffer), 3, &nlines);
  printf("%d : %d\n", index_tail_buff, nlines);
  return 0;
}
