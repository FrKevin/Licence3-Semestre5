#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "lib/makeargv.h"

/* Constantes */
#define AND 0
#define OR 1
/*  */

/* Variable global*/
int conjonction = AND;
int begin_cmd;
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
 *  Check si le premier arguments est: --or ou --and
 *  @param first_argv le premier argument
 *  @return:
 *    l'index 2 si la chaine contient --or ou --and
 *    l'index 1 sinon
 */
int check_conjonction(char *first_argv){
  if(strcmp("--or", first_argv) == 0 ){
    conjonction = OR;
    return 2;
  }
  if(strcmp("--and", first_argv) == 0 ){
    conjonction = AND;
    return 2;
  }
  return 1;
}

void analyse_args(int argc, char * argv[]){
  assert_message(argc >= 2);
  int begin_cmd;
  int i = 0;
  begin_cmd = check_conjonction(argv[1]);
}

void do(){
  
}

int main(int argc,const char* argv[]) {
    exit(EXIT_SUCCESS);
}
