#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

/* Variables globale */
static const char* pathname;
static int bufsize;
/* Fin Variables globale */

/* Prototype de fonction */
int is_file(const char *pathname);
void analyse_args(int argc, const char * argv[]);
void print_buffer(const char* buffer, int bufsize);
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
    if( getenv("MCAT_BUFSIZ") == NULL){
      bufsize =1024;
    }
    else{
        bufsize = atoi(getenv("MCAT_BUFSIZ"));
    }
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

void cat(){
  int fd;
  int read_octet;
  char *buf = calloc(bufsize * sizeof(char), sizeof(char));
  fd = open(pathname, O_RDONLY);
  assert(fd != -1);
  while( (read_octet = read(fd, buf, bufsize)) != 0 ){
    if(read_octet == -1){
      exit(EXIT_FAILURE);
    }
    else{
      print_buffer(buf, read_octet);
    }
  }
  close(fd);
  free(buf);
}

int main(int argc,const char* argv[]) {
  analyse_args(argc, argv);
  cat();
  return EXIT_SUCCESS;
}
