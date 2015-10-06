#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

/* /\ ATENTION => Ne jamais printf un buffer de read, car il ne met pas de caractère de fin s\0 */

/* Constante */

#define SIZE_OF_BUFFER 10

/* Fin Constante */

const char* pathname;

static long lines_tail = 10;
static long lines_current = 0;
static int nb_octet_file;

void splitBuffer(char *buff, int len) {
  int i=0;
  for(i=0; i < size; ++i) {
    if(buff[i] == '\0') {

    }
  }
}

int isFile(const char * pathname){
  struct stat st;
  int status;

  status = stat(pathname, &st);
  assert(status == 0);
  return S_ISREG(st.st_mode);
}

/*
 * Retourne le nombre \n présent dans le texte
 */
int getNBAntiSlashN(const char *buffer, int bufsize){
  int i;
  int lines = 0;
  for(i = 0; i < bufsize; ++i) {
    if(buffer[i] == '\0'){
      lines++;
    }
  }
  return lines;
}


void checkArgs(int argc,const char * argv[]){
  assert(argc > 1);
  if(isFile(argv[1])){
    pathname = argv[1];
    if(argc > 2)
      lines_tail = atoi(argv[3], NULL, 10); // ATOI
  }
  else{
    perror("Ce n'est pas un fichier !");
    exit(EXIT_FAILURE);
  }
}

/*
 *  Ecrit sur la sortie
 */
void printText(const char* text, int nbChar){
    assert (write(STDOUT_FILENO, text, nbChar) !=-1);
}





/*
 * Déplace la tête de lecteur d'un différence de size
 */
int tail_before_pos(int df, const int size){
  int status;
  int nbLine;
  int nbOctetRead;
  char buff[SIZE_OF_BUFFER]
  status = lseek(df, -size, SEEK_CUR);
  assert(status != -1));
  nbOctetRead = read(df, &buff, SIZE_OF_BUFFER);
  if(nbOctetRead != SIZE_OF_BUFFER) {

  }
  nbLine = getNBAntiSlashN(buff);
  if(lines_current < lines_tail) {
    tail_before_pos(df, size*2);
    printText(buff);
  }
  if(lines_current > lines_tail) {
    lines_tail - (lines_current - nbLine) /* Expression permettant de recuperer le nbr ligne restante
  }
  printText(buff);

}

void tail(){
  int diffLine;
  int status;
  char buff[sizeOfBuff];
  int df = open(pathname, O_RDONLY);
  /* 1) On démare a la fin du fichier */
  nbOctetsFile = lseek(df, 0, SEEK_END);
  assert(nbOctetsFile != -1);
  tail_before_pos(df, sizeOfBuff);
  /* On libère la mémoire */
  close(df);
}

int main(int argc,const char* argv[]) {
  checkArgs(argc, argv);
  tail();
  return EXIT_SUCCESS;
}
