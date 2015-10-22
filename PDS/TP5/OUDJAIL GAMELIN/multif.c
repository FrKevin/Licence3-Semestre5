#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* definition des types */
typedef int (*funct_t)(int);
/* */

/* Variable global */
static funct_t *f;
static int *args;
static int nargs;
/* */

/* Prototype de fonction */
int test(int a);
void init_var();
void destroy_var();
void assert_message(int cond, char * message);
int multif(funct_t f[], int args[], int nargs);
void analyse_args(int argc, const char * argv[]);
/* Fin Prototype de fonction */

/*
 * Construit le tableau de fonction et de leur arguments
 * @param : const char* argv[]: les arguments passer au programme
 */
void init_var(const char* argv[]){
  int i = 0;
  f = (funct_t*)malloc(nargs*sizeof(funct_t));
  args = (int*)malloc(nargs*sizeof(int));
  for(i=0; i<nargs; i++){
    f[i] = test;
    args[i] = atoi(argv[i+1]);
  }
}

/*
 *  libère la méoire
 */
void destroy_var(){
  free(f);
  f = NULL;
  free(args);
  args = NULL;
}

/*
 * Simple fonction de test
 */
int test(int a){
  printf("appel a f(%d)\n", a);
  fflush(stdout);
  return (a > 10);
}

/*
 * Ecrit sur la sortie d'erreur
 * @param : int cond: la condition d'assertion
 * @param : char * message: le message a afficher
 * @return
 */
void assert_message(int cond, char * message){
  if(!cond){
    fprintf(stderr, "%s\n", message);
    perror(NULL);
    exit(EXIT_FAILURE);
  }
}

/*
  Permet d'analyser les argument passé en parametre au programme
  @param : Il prend un tableau de chaine de caractére correspondant au paramètres des fonctions
  @return : Elle ne renvoie pas d'elements
*/
void analyse_args(int argc, const char * argv[]){
  assert_message(argc > 1, "no argument");
  nargs = argc-1;
/*   assert_message(nargs == (argc-2), "miss argumment"); */
}

/*
 * Excécute une liste de fonction avec leur arguments
 * @param : funct_t f[]: Liste des fonctions a excécuter
 * @param : int args[]: les arguments pour chaque fonctions
 * @param : int nargs; le nombre d'argument de fonction
 */
int multif(funct_t f[], int args[], int nargs){
  int i=0;
  int status;
  int conjonction =1;
  pid_t pid;
  for (i=0; i< nargs; i++){
    pid = fork();
    assert_message(pid !=-1, "Fork failure");
    /* Fils */
    if(pid == 0){
      exit(f[i](args[i]));
    }
  }
  for(i=0; i<nargs; i++){
    wait(&status);
    conjonction = conjonction & WEXITSTATUS(status);
  }
  return conjonction;
}

int main(int argc,const char* argv[]) {
  analyse_args(argc, argv);
  init_var(argv);
  printf("%i\n", multif(f, args, nargs));
  destroy_var();
  exit(EXIT_SUCCESS);
}
