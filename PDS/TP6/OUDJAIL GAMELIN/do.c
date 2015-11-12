#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "lib/makeargv.h"

/* Constantes */

#define AND 1
#define OR 0

/* Variable global*/
int conjonction = AND; /* L'operateur de la conjonction */
int begin_cmd; /* L'index de la premère commande */
int ncmd; /* Le nombre de commandes */
int option_kill = 0; /* représente le paramètre --cc par défaut désactiver (= 0)
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

void analyse_args(int arc, const char *argv[]) {
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
  while ((opt = getopt_long_only(argc, argv,"aoc", long_options, &long_index )) != -1) {
    switch (opt) {
      case 'a':
      conjonction = AND;
      break;
      case 'o':
      conjonction = OR;
      case 'c':
      option_kill = 1;
      break;
    }
  }
  assert_message(optind + 1 < argc, "Lower arguments ");
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
   for(i = index+1; i< ncmd; i++){
      assert_message( kill(-t_pid[i], SIGKILL ) != -1, "Kill failure");
    }
}

/*
* Attends tous les fils crée et fait la conjonction des valeurs retourné
* @return le resultat de la conjonction des fils
*/
int wait_child(pid_t* t_pid){
 int status;
 int i;
 int result;
 result = conjonction == AND ? EXIT_SUCCESS : EXIT_FAILURE;
 for(i=0; i<ncmd; i++){
   wait(&status);
   assert_message(WIFEXITED(status), "The processus not quit normaly");
   if(conjonction == AND) {
     result &= WEXITSTATUS(status);
   }
   else {
     result |= WEXITSTATUS(status);
   }
   if(option_kill && ((conjonction == AND && !result) || (conjonction == OR && result)) {
     kill_process(i, t_pid);
   }
 }
 return result;
}

/*
* exécute commande do
* @param int argc le nombre d'arguments
*/
int my_do(int argc, const char * argv[]){
 pid_t* t_pid;
 int i;
 int t_pid_index = 0;
 int status;
 int result;
 t_pid = malloc(ncmd);
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
 /* printf("Conjonction %i\n", result); */
 free(t_pid);
 return result;
}

int main(int argc,const char argv[]) {
  analyse_args(argc, argv);
  exit(my_do(argc, argv));
  /* exit(EXIT_SUCCESS);*/
}
