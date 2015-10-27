#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Constante */
#define nchild 10
#define count 100000000
/* Fin Constante */

/*
 * fonction a faire pour la course
 */
void todo(){
  int i;
  for (i = 0; i < count; i++) {}
  printf("TODO\n");
  fflush(stdout);
  for (i = 0; i < count; i++) {}
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
      exit(i);
    }
  }
}

/**
 * Que la course commence
 */
void race(){
  init_child();
  wait_child();
}

int main(int argc,const char* argv[]) {
  race();
  exit(EXIT_SUCCESS);
}
