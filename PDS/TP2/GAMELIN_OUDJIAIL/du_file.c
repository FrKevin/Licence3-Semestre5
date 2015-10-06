#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "ArrayList.h"

int follow_links =0;
int apparent_size =0;
int size_with_block = 1;
int printRecusifFolder =1;
int sizeOfBlock = 512;
const char* pathname;

ArrayList *history;

void checkArgs(int argc, char * const * argv){
  if(argc == 0){
    return;
  }
  else{
    int arg;
    /* chiane contenant tous les arguments possibles*/
    char format[] = "LbBa";
    extern int optind;
    pathname = argv[1];
    /* Parcours des arguments */
    while( (arg = getopt(argc, argv, format)) !=-1){
      switch (arg) {
        case 'L':
          follow_links = 1;
        break;
        case 'b':
          apparent_size = 1;
          size_with_block =0;
        break;
        case 'B':
          size_with_block = 1;
          assert(argc > optind);
          sizeOfBlock = (int)strtol(argv[optind], NULL, 10);
          if(errno != 0){
            perror("Arguments invalide");
            exit(EXIT_FAILURE);
          }
        break;
        case 'a':
          printRecusifFolder = 1;
        break;
        default:
        break;
      }
    }
  }
}

int valid_subdir(const char *file) {
  if(strcmp(file, ".") == 0 || strcmp(file, "..") == 0) {
    return 0;
  }
  return 1;
}


void printSize(const int size, const char* pathname){
  if(size_with_block == 1){
    printf("%i     %s\n", size/sizeOfBlock, pathname);
  }
  else{
    printf("%i     %s\n", size, pathname);
  }
  return;
}

int du_file(const char* pathname) {
  struct dirent * sub_dir;
  char new_pathname[PATH_MAX];
  char ino_dev[255];
  int size;
  DIR* dirCurrent;
  struct stat st;
  int status;

  if(follow_links) {
    status = stat(pathname, &st);
  }
  else {
    status = lstat(pathname, &st);

  }

  if(status == -1){
    perror("");
    exit(EXIT_FAILURE);
  }
  /* Genere un numero unique */
  snprintf(ino_dev, 255, "%i%i", (int)st.st_dev, (int)st.st_ino);

  if(containsAList(history, ino_dev)) {
    return 0;
  }
  /* Est-ce un fichier régulier, Est-ce un lien symbolique */
  if(S_ISREG(st.st_mode) || S_ISLNK(st.st_mode) ){
    size = st.st_size;
  }
  /*  Est-ce un dossier*/
  else if(S_ISDIR(st.st_mode)){
    size = st.st_size;
    dirCurrent = opendir(pathname);
    assert(dirCurrent);
    while((sub_dir = readdir(dirCurrent)) != NULL) {
      if(valid_subdir(sub_dir->d_name)) {
        snprintf(new_pathname, PATH_MAX, "%s/%s", pathname, sub_dir->d_name);
        size += du_file(new_pathname);
      }
    }
    closedir(dirCurrent);
  }
  /* Si ce n'est pas un fichier régulier, ou un liens symbolique ou un dossier*/
  else{
    return 0;
  }
  addElement(&history, ino_dev);
  if(printRecusifFolder == 1)
    printSize(size, pathname);
  return size;
}

int main(int argc, char *argv[]) {
  int size;
  assert(argc != 1);
  history = constructArrayList();
  checkArgs(argc, argv);
  size = du_file(pathname);
  if (printRecusifFolder == 0){
    printSize(size, pathname);
  }
  destructArrayList(history);
  return EXIT_SUCCESS;
}
