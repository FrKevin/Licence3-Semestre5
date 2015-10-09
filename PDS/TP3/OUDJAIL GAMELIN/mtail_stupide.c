#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

/* Constante */
#define SIZE_OF_BUFFER 1
/* Fin Constante */

/* Variables globale */
static const char* pathname;
static long ntail = 10;
/* Fin Variables globale */

/* Prototype de fonction */
int is_file(const char *pathname);
void analyse_args(int argc, const char * argv[]);
void tail();
int nlines_of_file(int df);
/* Fin Prototype de fonction */

/*
  Fonction qui permet de savoir, si un fichier passé en parametre est valide ou non
  @param : Prend en parametre une chaine de caractere correspondant à l'addresse du fichier
  @return : Retourne un entier (bool), 1 - > vrai, 0 -> faux
*/
int is_file(const char *pathname){
  struct stat st;
  int status;

  status = stat(pathname, &st);
  assert(status == 0);
  return S_ISREG(st.st_mode);
}

/*
  Permet d'analyser les argument passé en parametre au programme
  @param : Il prend un tableau de chaine de caractére correspondant au differente commande que l'utilisateur tape, et un entier correspondant à sa taille
  @return : Elle ne renvoie pas d'elements
*/
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
  Cette fonction permet d'ecrire sur la sortie standard un buffer (tableau de char sans terminateur (\0))
  @param : Elle prend en parametre un buffer et une taille
  @return : Elle ne renvoie pas d'elements
*/
void print_buffer(const char* buffer, int bufsize){
    assert (write(STDOUT_FILENO, buffer, bufsize) !=-1);
}

/*
  Cette fonction permet de récupérer le nomdre de ligne présent dans le fichier
  @param : Elle prend en parametre un descripteur de fichier
  @return : Elle ne renvoie pas d'element le nombre de ligne
*/
int nlines_of_file(int df){
  int nlines = 0;
  char buffer[SIZE_OF_BUFFER];
  int nread_octet;
  while( (nread_octet = read(df, buffer, SIZE_OF_BUFFER)) != 0){
    assert(nread_octet != -1);
    if(buffer[0] == '\n'){
      nlines++;
    }
  }
  lseek(df,SEEK_SET, 0);
  return nlines;
}

/*
  Cette fonction permet de récupérer le nomdre de ligne présent dans le fichier
  @param : Elle prend en parametre un descripteur de fichier
  @return : void
*/
void print_last_file(int df){
  int lignes_max = 0;
  int current_line = 0;
  char buffer[SIZE_OF_BUFFER];
  int nread_octet;
  lignes_max = nlines_of_file(df);
  while( (nread_octet = read(df, buffer, SIZE_OF_BUFFER)) != 0){
    assert(nread_octet != -1);
    if( (lignes_max - ntail <= 0) || (current_line >= (lignes_max - ntail)) ){
      print_buffer(buffer, nread_octet);
    }
    if(buffer[0] == '\n'){
      current_line++;
    }
  }
}

void tail(){
  int df;
  df = open(pathname, O_RDONLY);
  assert(df != -1);
  print_last_file(df);
}

int main(int argc,const char* argv[]) {
  analyse_args(argc, argv);
  tail();
  printf("\n");
  fflush(stdout);
  return EXIT_SUCCESS;
}
