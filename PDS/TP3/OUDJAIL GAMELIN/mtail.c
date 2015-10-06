#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

/* /\ ATONTION => Ne jamais printf un buffer de read, car il ne met pas de caractère de fin s\0 */

long lines = 10;
const char* pathname;
int sizeOfBuff = 10;

int isFile(const char * pathname){
  struct stat st;
  int status;

  status = stat(pathname, &st);
  assert(status == 0);
  return S_ISREG(st.st_mode);
}

void checkArgs(int argc,const char * argv[]){
  assert(argc > 1);
  if(isFile(argv[1])){
    pathname = argv[1];
    if(argc > 2)
      lines = (int)strtol(argv[3], NULL, 10);
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
 * Retourne le nombre \n présent dans le texte
 */
int getAntislashN(char * text){
  char * copy = text;
  int lignes = 0;
  while(copy != NULL){
    if(strcmp(text, "\\n") == 0){
      lignes++;
    }
    copty++;
  }
  return lignes;
}

/*
 * Déplace la tête de lecteur d'un différence de size
 */
void myLseek(int df, int size){
  int status;
  int ligne;
  status = lseek(df, -size, SEEK_CUR);
  assert(status != -1););
}

void tail(){
  int diffLine;
  int status;
  char buff[sizeOfBuff];
  int df = open(pathname, O_RDONLY);
  /* 1) On démare a la fin du fichier */
  status = lseek(df, 0, SEEK_END);
  assert(status != -1);
  myLseek(df, sizeOfBuff);
  /* On libère la mémoire */
  close(df);
}

int main(int argc,const char* argv[]) {
  checkArgs(argc, argv);
  tail();
  return EXIT_SUCCESS;
}
