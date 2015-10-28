#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int check_conjonction(const char *first_argv){
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

void analyse_args(int argc, const char * argv[]){
  assert_message(argc >= 2, "lower arguments ");
  begin_cmd = check_conjonction(argv[1]);
}

/*
 * La commande que le fils exécute
 */
void work_child(const char * argv){
  char **cmdargv;
  makeargv(argv, " ", &cmdargv);
  execvp(cmdargv[0], cmdazrgv);
  exit(EXIT_FAILURE);
}

void pars_status(int status){

}

/*
 * Attends tous les fils crée et fait la conjonction des valeurs retourné
 */
void wait_child(){
  int status;
  for(i=0; i<nargs; i++){
    wait(&status);
    if(WIFEXITED(status)){
      conjonction = conjonction & WEXITSTATUS(status);
    }
  }
}

/*
 * exécute commande do
 * @param int argc le nombre d'arguments
 */
void my_do(int argc, const char * argv[]){
  int ncmd = argc - begin_cmd;
  pid_t* t_pid = malloc(ncmd);
  int i;
  int t_pid_index = 0;
  int status;
  for(i = begin_cmd; i < argc; i++){
    status = fork();
    assert_message(status != -1, "fork failure !");
    t_pid[t_pid_index] = status;
    if(status == 0){
      work_child(argv[i]);
    }
    t_pid_index++;
  }
  free(t_pid);
}

int main(int argc,const char* argv[]) {
    analyse_args(argc, argv);
    my_do(argc, argv);
    exit(EXIT_SUCCESS);
}
