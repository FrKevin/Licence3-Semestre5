#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Variable global */
static int nchild;
/* */

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
void analyseArgs(int argc, const char * argv[]){
  assert_message(argc > 1, "no argument");
  nchild = atoi(argv[1]);
}

/*
 * fonction a faire par le fils
 */
void todo(){
  while(1 == 1){
    printf("%d\n", getpid());
    sleep(5);
  }
}

/*
 * Attends tous fils créés
 */
void wait_child(){
  int i;
  int status;
  for (i = 0; i < nchild; i++) {
    wait(&status);
    printf("child n°%i terminated.\n", WEXITSTATUS(status));
  }
}

/*
 *  Construit tous les fils
 */
void init_child(){
  int i;
  pid_t pid;
  for(i =0; i < nchild; i++){
    pid = fork();
    assert_message(pid !=-1, "Fork failure");
    if(pid == 0){
      todo();
      exit(EXIT_SUCCESS);
    }
  }
}

void oprocess(){
  init_child();
  wait_child();
}

int main(int argc,const char* argv[]) {
  analyseArgs(argc, argv);
  oprocess();
  exit(EXIT_SUCCESS);
}
