#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
	Variable globale au programme, cette variable recupére l'index du parametre verbose dans la liste d'argument de la commande,
	s'il ne la trouve pas la verbose reste à 0
*/
static int verbose = 0;

static const int MIN_ARGS = 3;
static const int MAX_ARGS = 6; /* Si un seul droit à la fois, MAX-ARGS = 4; */

static const char *MODE_R = "-r";
static const char *MODE_W = "-w";
static const char *MODE_X = "-x";
static const char *MODE_V = "-v";

/*
	Fonction englobant la fonction access(...)
	@return : Si la fonction c'est bien passer, retourne 0, sinon retourne -1 et ecrit le code erreur dans la variable errno
	@param : Le premier parametre contient le chemin d'acces (type : char*), le deuxieme contient le mode à tester (lire, ecrire, execution) de type int
*/

int maccess(char* pathname, int mode) {
	return access(pathname, mode);
}

/*
	Fonction permettant de convertir les droits ecrits par l'utilisateur (-r, -w, -x)
	@return : Si la fonction c'est bien passer, retourne le mode associé au droit entré en paramétre, sinon arrête le programme(exit()) avec un status à EXIT_FAILURE et errno à EINVAL,
	@param : La fonction prend un mode en chaine de caratére, les motif suivant sont accepté : -r, -w, -x
*/

int parseArgs(const char* mode) {
	if(strcmp(mode, MODE_R) == 0 ) {
		if(verbose) { printf("%s\n", "Test l'acces sur le droit de lecture ...");}
		return R_OK;
	}
	if(strcmp(mode, MODE_W) == 0 ) {
		if(verbose) { printf("%s\n", "Test l'acces sur le droit d'ecriture ...");}
		return W_OK;
	}
	if(strcmp(mode, MODE_X) == 0 ) {
		if(verbose) { printf("%s\n", "Test l'acces sur le droit d'execution ...");}
		return X_OK;
	}
	else {
		errno = EINVAL;
		fprintf(stderr, "%s : %s, errno : ", "Arguments invalides", mode);
		perror(NULL);
		exit(EXIT_FAILURE);

	}
}

/*
	Fonction imprimant sur le terminal, si la commande à etait un succés ou s'il y'a eu un problème
	@return Aucune valeur n'est renvoyée
	@param Pas de parametre
*/

void printStatusBasic() {
	if(errno == 0) {
		printf("%s\n", "Vous avez les droits");
	}
	else {
		fprintf(stderr, "%s\n", "Vous ne possédez pas les droits");

	}
}

/*
	Fonction imprimant sur le terminal, si la commande à était un succés ou s'il y'a eu un problème, dans ce cas elle donne plus d'information en recuperant errno et en envoyant les informations la concernant
	@return Aucune valeur n'est renvoyée
	@param Pas de parametre
*/

void printStatusVerbose()  {
	switch(errno) {
		case EACCES:
		perror("L'acces au fichier est refuse");
		break;

		case ELOOP:
		perror("Le fichier pointe sur trop de liens symbolique");
		break;

		case ENAMETOOLONG:
		perror("Le pathname est trop long");
		break;

		case ENOENT:
		perror("L'un des composant du chemin d'acces n'existe pas ou est un liens symbolique pointant nulle part");
		break;

		case ENOTDIR:
		perror("L'un des elements du chemin d'acces n'est pas un repertoire");
		break;

		case EROFS :
		perror("La demande d'ecriture car le systemes de fichiers courant est en lecture seule");
		break;

		case EFAULT:
		perror("Le chemin d'acces pointe en dehors de l'espace d'adressage accessible");
		break;

		case EINVAL:
		perror("Le mode est mal spécifié"); /* Cette  erreur traité en amont : parseArgs()  */
		break;

		case EIO:
		perror("Une erreur d'entrée-sortie s'est produite");
		break;

		case ENOMEM:
		perror("Pas assez de mémoire pour le noyau.");
		break;

		case ETXTBSY:
		perror("Erreur produite car demande d'écriture dans un fichier exécutable qui est en cours d'utilisation");
		break;

		default:
		printf("%s\n", "Vous avez les droits");

	}
}
/*
	Fonction determinant quelle methodes d'impression sur le terminal faut il choisir. Ceci est fait par le biais de la variable globale verbose
	@return Aucune valeur n'est renvoyée
	@param Pas de parametre
*/
void printStatus() {
	if(verbose) {
		printStatusVerbose();
	}
	else {
		printStatusBasic();
	}
}

/*
	Fonction permettant de savoir si l'option -v à etait déclencher dans les args passer en parametre
	@return : Retourne la position de l'argument -v dans la liste d'arguments, s'il il n'existe pas renvoie la valeur 0
	@param : Prend en paramètre le nombre d'arguments et la liste
*/

int isVerbose(int argc, char *argv[]) {
	int index = 0;
	for(index = 1; index < argc; ++index) {
		if(strcmp(argv[index], MODE_V) == 0) {
			return index;
		}
	}
	return 0;
}

/*
	Fonction permettant de verifier la validité des arguments (nombre)
	@return : Retourne un int (bool), s'il est valide -> 1 sinon 0
	@param : Prend en paramètre le nombre d'arguments et la liste
*/

int checkArgs(int argc, char *argv[]) {
	if(argc  < MIN_ARGS || argc > MAX_ARGS ) {
		fprintf(stderr, "Nombre d'arguments invalide (Intervale : [%i, %i] )!\n", MIN_ARGS, MAX_ARGS);
		return 0;
	}
	return 1;
}

/*
	Fonction applicant une strategie de traitements autorisant un seul droit à tester à la fois
	@return : Retourne le status de la fonction access()
	@param : Prend en paramètre le nombre d'arguments et la liste

*/

int traitementArgs(int argc, char *argv[]) {
	int mode;
	if(verbose) {
		mode = parseArgs(argv[(argc-1) - verbose]);
	}
	else {
		mode = parseArgs(argv[1]);
	}
	return maccess(argv[argc-1], mode);
}

/*
	Fonction applicant une strategie de traitements autorisant un plusieurs droit à tester à la fois
	@return : Retourne le status de la fonction access()
	@param : Prend en paramètre le nombre d'arguments et la liste
*/

int traitementArgsMultiple(int argc, char *argv[]) {
	int i;
	int mode = 0;

	for(i=1; i < argc-1; ++i) {
		if(verbose != i) {
			mode = mode | parseArgs(argv[i]);
		}
	}

	return maccess(argv[argc-1], mode);
}


int main (int argc, char *argv[]){
	int status;
  assert(checkArgs(argc, argv));
	verbose = isVerbose(argc, argv);
	status = traitementArgsMultiple(argc, argv);

	printStatus();

  return status;
}
