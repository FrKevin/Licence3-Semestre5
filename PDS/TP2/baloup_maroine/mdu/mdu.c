/*
 * Par Marc Baloup et Maxime Maroine 
 * 
 * Licence 3 Informatique - Université Lille 1
 * 
 * 2015-2016
 */
#include <unistd.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum { false, true } bool;

/* paramètres du programme */
static bool opt_follow_links = false;
static bool opt_apparent_size = false;
static char** opt_path_v;
static int opt_path_c;

/* --------------------
 * structure de données pour la mise en mémoire des path déjà analysés
 * --------------------
 */
 
/* structure choisie : la liste chainée */
struct PathListElementStruct {
	char path[PATH_MAX];
	struct PathListElementStruct* nextElement;
}; typedef struct PathListElementStruct PathListElement;

struct PathListStruct {
	PathListElement* firstElement;
	PathListElement* lastElement;
	int nbElement;
}; typedef struct PathListStruct PathList;

/* Initialise la liste */
void PathList_init(PathList* this) {
	this->firstElement = NULL;
	this->lastElement = NULL;
	this->nbElement = 0;
}

/* ajoute un élément dans la liste */
void PathList_addPath(PathList* this, const char* newPath) {
	PathListElement* element = malloc(sizeof(PathListElement));
	strcpy(element->path, newPath);
	element->nextElement = NULL;
	if (this->firstElement == NULL) {
		/* premier élément à enregistrer */
		this->firstElement = element;
		this->lastElement = element;
	}
	else {
		this->lastElement->nextElement = element;
		this->lastElement = element;
	}
	this->nbElement++;
}

/* vérifie l'existance d'un élément dans la liste */
bool PathList_containsPath(PathList* this, const char* pathname) {
	PathListElement* current = this->firstElement;
	while (current != NULL) {
		if (strcmp(pathname, current->path) == 0)
			return true;
		current = current->nextElement;
	}
	return false;
}

/* vide (libère la mémoire) la liste */
void PathList_clear(PathList* this) {
	PathListElement* current;
	PathListElement* next;
	current = this->firstElement;
	while(current != NULL) {
		next = current->nextElement;
		free(current);
		current = next;
	}
	this->firstElement = NULL;
	this->lastElement = NULL;
	this->nbElement = 0;
}


/*
 * ==================================================================
 */

PathList element_history;

/* déclaration des fonctions */
bool valid_folder(const char* path);
long du(const char* pathname, bool first);
void analyseArgs(int argc, char** argv);
long getRightSize(struct stat st);


/* Main */
int main(int argc, char** argv) {
	int i;
	analyseArgs(argc, argv);
	
	PathList_init(&element_history);
	
	for(i=0; i<opt_path_c; i++) {
		printf("%ld\t%s\n", du(opt_path_v[i], true), opt_path_v[i]);
	}
	
	PathList_clear(&element_history);
	
	return EXIT_SUCCESS;
}

/*
 *Analyse du dossier
 */
 bool valid_folder(const char* path) {
 	if(strcmp(path, ".") == 0 || strcmp(path, "..") == 0) {
 		return false;
 	}
 	return true;
 }
 
/*
 * Retourne la bonne valeur selon les arguments
 */
long getRightSize(struct stat st) {
	if (opt_apparent_size)
		return st.st_size;
	else
		return st.st_blocks;
}

/*
 * Analyse des arguments
 */
void analyseArgs(int argc, char** argv) {
	int optch;
	extern int opterr;
	
	/* chaine contenant les caractères des arguments */
	char format[] = "Lb";

	opterr = 1;
	
	/* on parcours des arguments */
	while ((optch = getopt(argc, argv, format)) != -1)
		switch (optch) {
			case 'L':
				opt_follow_links = true;
				break;
			case 'b':
				opt_apparent_size = true;
				break;
		}
	
	if(optind >= argc) {
		fprintf(stderr, "Pas assez d'argument\n");
		exit(EXIT_FAILURE);
	}
	/* lis les derniers arguments, qui sont des chemins d'accès */
	opt_path_c = argc - optind;
	opt_path_v = &(argv[optind]);
}



/*
 * Fonction DU
 */
long du(const char* pathname, bool first) {
	long size;
	int stat_return;
	struct stat st;
	struct dirent* subdir;
	char subdir_pathname[PATH_MAX];
	DIR* dir;
	char fullpathname[PATH_MAX];
	
	size = 0;
	
	realpath(pathname, fullpathname);
	
	if (PathList_containsPath(&element_history, fullpathname) == true) {
		return 0;
	}
	
	
	if (opt_follow_links) {
		stat_return = stat(pathname, &st);
	}
	else {
		stat_return = lstat(pathname, &st);
	}
	
	if(stat_return != 0) {
		fprintf(stderr, "Erreur d'accès au fichier '%s' : %s\n", pathname, strerror(errno));
		return 0;
	}

	/* Fichier régulier ? */
	if(S_ISREG(st.st_mode)) {
		PathList_addPath(&element_history, fullpathname);
		size = getRightSize(st);
	}
	/* Lien symbolique ? on ne prends pas sa cible */
	else if (S_ISLNK(st.st_mode)) {
		size = getRightSize(st);
	}
	/* Dossier ? */
	else if(S_ISDIR(st.st_mode)) {
		PathList_addPath(&element_history, fullpathname);
		size = getRightSize(st);
		dir = opendir(pathname);
		if(dir == NULL)
		fprintf(stderr, "Erreur d'accès au fichier '%s' : %s\n", pathname, strerror(errno));
		else {
			while((subdir = readdir(dir)) != NULL) {
				if(valid_folder(subdir->d_name) == true) {
					snprintf(subdir_pathname, PATH_MAX, "%s/%s", pathname, subdir->d_name);
					size += du(subdir_pathname, false);
				}
			}
		}
		closedir(dir);
		if (!first)
			printf("%ld\t%s\n", size, pathname);
	}
	return size;
}
