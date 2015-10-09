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

#define SIZE_OF_BUFFER 1024
/* Fin Constante */

/* Variables globale */

static const char* pathname;

static long ntail = 10;

/* Fin Variables globale */

/* Prototype de fonction */

int check_read(int rstatus, int wait_noctet_read);
int is_file(const char *pathname);
int index_tail_buffer(const char *buffer, int bufsize, int ntail, int *nlines);
long get_last_octet(int fd);
char get_char_bypoct(int fd, int poctet);
void analyse_args(int argc, const char * argv[]);
void print_buffer(const char* buffer, int bufsize);
int tail_before_pos(int df, unsigned int pos, int ntail);
void tail();

/* Fin Prototype de fonction */


/* Fonction permettant de savoir si une lecture (voir fct read) c'est bien passer en verifiant plusieurs cas
  @param : Prend le status de la fonction read(son retour) , ainsi qu'un entier representant ce que le nombre d'octet que l'on voulait lire
  @return : Retourne vrai si read c'est bien passer, faux sinon avec une impression d'un message ainsi que du statut de la variable errno sur la sortie d'erreur
*/

int check_read(int rstatus, int wait_noctet_read) {
  if(rstatus == -1) {
    perror("Erreur sur read");
    return 0;
  }
  if (rstatus != wait_noctet_read) {
    printf("%d\n", rstatus);
    perror("Erreur sur read, octets manquant en lecture");
    return 0;
  }
  return 1;
}

/*
  Fonction permettant de recuperer un caractere à une position donné dans le fichier
  @param : Prend un descripeur de fichier et une position de l'octet qu'on veut recuperer
  @return : Renvoie le caractere
*/

char get_char_bypoct(int fd, int poctet) {
  int rstatus;
  int hcurrent;
  char get_char[1];
  hcurrent = lseek(fd, 0, SEEK_CUR);
  assert(hcurrent != -1);
  assert(lseek(fd, poctet, SEEK_SET) != -1);
  rstatus = read(fd, get_char, 1);
  assert(check_read(rstatus, 1));
  assert(lseek(fd, hcurrent, SEEK_SET) != -1);
  return get_char[0];
}


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
 * Retourne l’index du début des ntail dernières lignes.
  Cet index est relatif au tampon de taille bufsize.
  Si le tampon comporte moins de ntail lignes, une valeur négative est retournée et nlines est positionné avec le nombre de lignes du buffer.
  @param : Elle prend  un buffer de char, un entier representant sa taille, un entier representant le nombre de ligne que l'on veut en partant à la fin et un entier correspondant au nombre reel de ligne compter
  @return : Retourne l'index representant une position dans le buffer, si égale -1 c'est tout le buffer qui doit etre pris sinon à partir de la position renvoyé
 */

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

/*
  Permet de recuperer le dernier octet du fichier
  @param : Il prend en parametre un descripeur de fichier (obtenu par un open) representé par un entier.
  @return : Renvoie la taille du fichier en octet (ou la position du dernier octet)
*/

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
  Cette fonction permet de lire les n dernieres lignes d'un fichier, à partir d'une position dans le fichiers
  @param : Elle prend en parametre un descriteur de fichier (open) representé par un entier,
           une position dans le fichier representé par un entier et un nombre de ligne à afficher en partant de la position vers le debut
  @return : Elle renvoie un statut, 1 correspond à une execution qui c
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
  if(pos == 0) { /* Cas d'arret de recursion, fin de fichier */
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
  lstatus = lseek(df, pseek, SEEK_SET);                                         /* Permet de positionner  */
  assert(lstatus != -1);
  noctet_read = read(df, &buffer, wait_noctet_read);
  assert(check_read(noctet_read, wait_noctet_read));
  index_tail_buff = index_tail_buffer(buffer, noctet_read, ntail, &nlines);
  if(index_tail_buff == -1) {                                                   /* Cas de recursion n < ntail, donc imprime tout le buffer */
    lstatus = lseek(df, -noctet_read, SEEK_CUR);                                /* Tete de lecture remise avant le read */
    assert(lstatus != -1);
    tail_before_pos(df, pos-noctet_read, ntail-nlines);
    print_buffer(buffer, noctet_read);                                          /* Print appelées après la recursion permet d'avoir un ordre d'impression identique a l'ordre des lignes dans le fichier */
  }
  else {                                                                        /* Cas d'arret de recursion, le ntail(nombre de ligne à aficher) est atteint  */
    nbuffer = buffer + index_tail_buff+1;
    print_buffer(nbuffer, noctet_read-index_tail_buff-1);
  }
  return 1;
}

void tail(){
  int df;
  int loctet_file;
  int last_eol = 0;
  df = open(pathname, O_RDONLY);
  assert(df != -1);
  /* On recupere le dernier octet du fichier */
  loctet_file = get_last_octet(df);
  if(loctet_file == 0 || ntail == 0) {
    return;
  }
  /* On verirfie si le dernier caractere du fichier est un retour à la ligne */
  if(get_char_bypoct(df, loctet_file-1) == '\n') {
    --loctet_file;
    last_eol = 1;
  }
  /* On, appelle la fonction tail_before_pos qui va imprimer les derniere ligne recurcivement */
  assert(tail_before_pos(df, loctet_file, ntail) != -1);

  if(last_eol) { printf("\n"); }

  /* On libère la mémoire */
  assert(close(df) != -1);
}

int main(int argc,const char* argv[]) {
  analyse_args(argc, argv);
  tail();
  return EXIT_SUCCESS;
}
