#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "lib/makeargv.h"

/* Constantes */
#define AND EXIT_SUCCESS
#define OR EXIT_FAILURE
/*  */

/* Variable global*/
int conjonction = AND; /* L'operateur de la conjonction */
int begin_cmd; /* L'index de la premère commande */
int ncmd; /* Le nombre de commandes */
int option_kill = 0; /* représente le paramètre --cc par défaut désactiver (= 0) */
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

void analyse_args(int argc, char * const argv[]) {
  int opt = 0;
/*
 * 1er colonne: le paramètre cible
 * 2e paramètre
 * 3e flag
 * 4e alias
 */
  static struct option long_options[] = {
       {"and", no_argument, 0,  'a' },
       {"or", no_argument, 0, 'o' },
       {"cc", no_argument, 0, 'c' },
       {0, 0, 0, 0 }
  };
  int long_index = 0;
  while ((opt = getopt_long_only(argc, argv,"aoc", long_options, &long_index ) ) != -1) {
    switch (opt) {
      case 'a':
        conjonction = AND;
      break;
      case 'o':
        conjonction = OR;
      break;
      case 'c':
        option_kill = 1;
      break;
    }
  }
  assert_message(optind < argc, "Lower arguments ");
  begin_cmd = optind;
  ncmd = argc - begin_cmd;
}

/*
* La commande que le fils exécute
*/
void work_child(const char * argv){
 char **cmdargv;
 makeargv(argv, " ", &cmdargv);
 execvp(cmdargv[0], cmdargv);
 exit(EXIT_FAILURE);
}

/*
 * Détruit tous les procesus a partir d’un index
 * @param int index on commence a kill a partie de index+1
 * @param pid_t* t_pid l’ensemble des pid de toute les commande lancé
 */
void kill_process(int index, pid_t* t_pid){
   int i = 0;
   for(i = index; i< ncmd; i++){
      assert_message( kill(-t_pid[i], SIGKILL ) != -1, "Kill failure");
    }
}

int IFKILLED(int result) {
  return option_kill && ((conjonction == AND && !result) || (conjonction == OR && result));
}

/*
* Attends tous les fils crée et fait la conjonction des valeurs retourné
* @return le resultat de la conjonction des fils
*/
int wait_child(pid_t* t_pid){
  int status;
  int i;
  int result;
  result = conjonction;
  for(i=0; i<ncmd; i++){
    wait(&status);
    assert_message(WIFEXITED(status), "The processus not quit normaly");
    if(conjonction == AND) {
      if(WEXITSTATUS(status) == EXIT_FAILURE){
        result = EXIT_FAILURE;
      }
    }
    else {
      if(WEXITSTATUS(status) == EXIT_SUCCESS){
        result = EXIT_SUCCESS;
      }
    }
    if(IFKILLED(result)) {
      kill_process(i+1, t_pid);
    }
  }
  return result;
}

/*
* exécute commande do
* @param int argc le nombre d'arguments
*/
int my_do(int argc, char *argv[]){
 pid_t* t_pid;
 int i;
 int t_pid_index = 0;
 int status;
 int result;
 t_pid = (pid_t*) malloc(ncmd * sizeof(pid_t));
 for(i = begin_cmd; i < argc; i++){
   status = fork();
   assert_message(status != -1, "fork failure !");
   t_pid[t_pid_index] = status;
   if(status == 0){
     work_child(argv[i]);
   }
   t_pid_index++;
 }
 result = wait_child(t_pid);
 free(t_pid);
 return result;
}

int main(int argc, char *argv[]) {
  analyse_args(argc, argv);
  exit(my_do(argc, argv));
}
