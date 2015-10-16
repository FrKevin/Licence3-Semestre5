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
void initVar();
void destroyVar();
void assertMessage(int cond, char * message);
int multif(funct_t f[], int args[], int nargs);
/* Fin Prototype de fonction */

/*
 *
 */
void initVar(const char* argv[]){
  int i = 0;
  f = (funct_t*)malloc(nargs*sizeof(funct_t));
  args = (int*)malloc(nargs*sizeof(int));
  for(i=0; i<nargs; i++){
    f[i] = test;
    args[i] = atoi(argv[i+2]);
  }
}

void destroyVar(){
  free(f);
  f = NULL;
  free(args);
  args = NULL;
}

int test(int a){
  printf("appel a f(%d)\n", a);
  fflush(stdout);
  return (a > 10);
}

/*
 *
 */
void assertMessage(int cond, char * message){
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
void analyseArgs(int argc, const char * argv[]){
  assertMessage(argc > 1, "no argument");
  nargs = atoi(argv[1]);
  assertMessage(nargs == (argc-2), "miss argumment");
}

/*
 *
 *
 */
int multif(funct_t f[], int args[], int nargs){
  int i=0;
  int status;
  int conjonction =1;
  pid_t pid;
  for (i=0; i< nargs; i++){
    pid = fork();
    assertMessage(pid !=-1, "Fork failure");
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
  analyseArgs(argc, argv);
  initVar(argv);
  multif(f, args, nargs);
  destroyVar();
  exit(EXIT_SUCCESS);
}
