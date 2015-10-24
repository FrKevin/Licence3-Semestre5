/** 
  \file graphe.h
  \brief Fichier d'entête de la bibliothèque sur les graphes


*/

/*! \mainpage Bibliothèque de manipulation de graphes en C
 *

 * Cette bibliothèque fournit les opérations de base sur les graphes,
 * afin de réaliser facilement des opérations sur les graphes.
 * Vous devez lire les (courtes) sections qui suivent avant
 * d'aller regarder la documentation.
 *
 * - \subpage presentation 
 * - \subpage installation 
 * - \subpage syntaxe_graphe 
 * - \subpage consignes 
 
 \authors François Lemaire, Arnaud Liefooghe, Marie-Emilie Voge, Léopold Weinberg
 \date 2010


 * \page presentation Présentation générale

 La bibliothèque permet de manipuler des graphes orientés ou non.
 Les graphes sont toujours valués, et le type des valeurs
 des arcs/arêtes est double (flottant double précision).
 Attention, la valeur nulle pour un arc/arête est interdite.

 L'intérêt de cette bibliothèque est de pouvoir
 charger un fichier texte ou générer aléatoirement
 des graphes, et de pouvoir consulter avec des fonctions
 d'interface des informations comme les voisins, successeurs, ...

 En interne, les données sont stockées pour améliorer l'efficacité
 des opérations. La méthode est simple : les données sont stockés
 sous différents formats (liste de voisins, liste de successeurs,
 matrice d'incidence, ...) afin d'avoir des opérations
 de consultation en coût constant.

 Les sommets des graphes sont des chaînes de caractères.
 
 Les sommets sont manipulés par leur numéro, qui est compris
 entre 0 et le nombre de sommets moins un.
 
 * \page installation Installation/Compilation
 *
 * Il n'y a rien à installer. Nous vous fournissons deux fichiers
 * <a href="graphe.h">graphe.h</a>
 * et
 * <a href="graphe.c">graphe.c</a>
 *
 * Vous utiliserez la compilation séparée.
 * Télécharger le fichier d'exemple 
 * <a href="testAnalyseur.c">testAnalyseur.c</a>
 * et lancer la commande
 * \code
$ gcc -Wall -g -std=c99 testAnalyseur.c graphe.c -o testAnalyseur
 * \endcode

 * Votre programme se lance avec
 * \code
 * $ ./testAnalyseur <fichier_graphe>
 * \endcode
 * où fichier_graphe est un fichier contenant un graphe
 * au format décrit dans la section suivante.

 * Pour tester la commande précédente, télécharger
 * le fichier <a href="ex-no.grp">ex-no.grp</a>
 * et lancez
 \code
 $ ./testAnalyseur ex-no.grp
 \endcode
 qui devrait vous afficher le contenu des graphe dans une version détaillée


 \page syntaxe_graphe Syntaxe des fichiers de graphe
 
 Vous pouvez mettre des commentaires d'une ligne grâce au caractère #
 suivi du commentaire. Le # peut apparaître n'importe où dans la ligne.

 Le fichier doit avoir la syntaxe suivante :

\code

type = <oriente OU non-oriente>;

sommets = <liste de sommets séparés par des espaces> ;

arcs = <liste d'arcs séparés par des espaces, un arc étant représenté par Origine Destination Valeur_de_l'arc> ;
\endcode

Les arcs ont par défaut le type double (flottant double précision).

Exemple d'un graphe non orienté :
\include ex-no.grp 

Exemple d'un graphe orienté :
\include ex-o.grp 



\page consignes Consignes d'utilisation de la bibliothèque

Les structures de données sont commentées, mais uniquement
dans un but pédagogique. Lorsque vous utilisez la bibliothèque,
vous ne devez <b>jamais</b> accèder directement aux structures.
Vous devez utiliser les fonctions mises à votre disposition.

L'intérêt est que si les structures de données de la 
bibliothèque changent en cours d'année, votre code
continuera de fonctionner. De plus, lors du contrôle
TP de fin de semestre, vous pourriez avoir une version
de la librairie avec des structures de données différentes,
il vaut mieux donc apprendre à utiliser uniquement les
interfaces de fonctions.

Si vous estimez que des fonctions manquent, vous pouvez
toujours en parler à votre enseignant et le convaincre
de la rajouter.


Vous devez toujours utiliser l'option <tt>-Wall</tt>.
En C, un avertissement est très souvent une erreur.
Vous êtes encouragés à utiliser en plus les
options <tt>-g -std=c99</tt>.

 */


#ifndef _GRAPHE_H_
#define _GRAPHE_H_

/** Nombre maximum de sommets pour un graphe. */
#define MAX_SOMMETS 100

/** Nombre maximum d'arcs pour un graphe. */
#define MAX_ARCS (MAX_SOMMETS*MAX_SOMMETS)

/** Taille maximum du nom d'un sommet. */
#define LONG_NOM_SOMMET_MAX 50

/** Type pour stocker un nom de sommet. */
typedef char tNomSommet[LONG_NOM_SOMMET_MAX];

/** Type pour stocker un numéro de sommet. */
typedef int tNumeroSommet;

/** Type pour stocker la valeur d'un arc. */
typedef double tValeurArc;

/**
   Tableau de taille variable contenant des entiers (réservé à la librairie, ne pas utiliser).
   
   Attention : la taille est limitée au nombre maximum de sommets. 
   Exemple d'utilisation : pour colorer les sommets en couleur
*/
typedef struct  {
  /** le tableau d'entiers */
  int tab[MAX_SOMMETS];
  /** le nombre d'entiers effectivement utilisés dans le tableau */
  int nb;
} tTableauEntiers;

/** Type pour stocker un arc (vous pouvez accéder aux champs
de ce type). */
typedef struct  {
  /** Le numéro de l'origine. */
  int orig;
  /** Le numéro de la destination. */
  int dest;
  /** La valeur de l'arc. */
  tValeurArc val;
} tArc;

/**
   Type pour stocker la liste des arcs (réservé à la librairie, ne pas utiliser)
   
   NB: limité à MAX_ARCS arcs */
typedef struct  {
  /** Le tableau des arcs préalloué. */
  tArc tab[MAX_ARCS];
  /** Le nombre d'arcs qui ont été stockés dans le tableau. */
  int nb;
} tTableauArcs;

/** Type pour stocker un arbre (ne pas accéder aux champs directement,
 mais utiliser l'interface) */
typedef struct tGraphe{
  /** Orientation de l'arbre.
      Vaut 1 si l'arbre est orienté, 0 sinon.  */
  int estOriente;

  /** \brief Nombre de sommets. */
  int nbSommets;
  /** Nom des sommets. */
  tNomSommet nomSommets[MAX_SOMMETS];

  /** La matrice d'adjacence.

      Si il y a un arc de i à j, alors
      matriceAdjacence[i][j] contient la valeur de l'arc.
      Sinon, matriceAdjacence[i][j] vaut 0.
   */
  tValeurArc matriceAdjacence[MAX_SOMMETS][MAX_SOMMETS];
  
  /** Tableaux des successeurs.
      
      Ce tableau n'est rempli que pour les graphes orientés.
      Pour tout sommet i, 
      tableSuccesseurs[i] est le tableau des successeurs
      du sommet i. */
  tTableauEntiers tableSuccesseurs[MAX_SOMMETS];

  /** Tableaux des prédécesseurs.
      
      Ce tableau n'est rempli que pour les graphes orientés.
      Pour tout sommet i, 
      tablePredecesseurs[i] est le tableau des successeurs
      du sommet i. */
  tTableauEntiers tablePredecesseurs[MAX_SOMMETS];

  /** Tableaux des voisins.
      
      Ce tableau n'est rempli que pour les graphes non orientés.
      Pour tout sommet i, 
      tableVoisins[i] est le tableau des successeurs
      du sommet i. */
  tTableauEntiers tableVoisins[MAX_SOMMETS];


  /** Tableau des arcs.

      Ce tableau contient la liste de tous les arcs */
  tTableauArcs tableArcs;


} *tGraphe;



/** Type pour stocker une file de sommets (ne pas accéder aux champs
 directement, mais utiliser l'interface)*/
typedef struct tFileSommets {
  /** tableau de MAX_SOMMETS+1 numéros */
  tNumeroSommet tab[MAX_SOMMETS+1];

  /** indice de l'élément qui sera défilé */
  int debut;
  /** indice où le prochain élément sera enfilé */
  int fin;
} *tFileSommets;


/** Type pour stocker une pile de sommets (ne pas accéder aux champs
 directement, mais utiliser l'interface)*/
typedef struct tPileSommets {
  /** tableau de MAX_SOMMETS numéros */
  tNumeroSommet tab[MAX_SOMMETS];

  /** indice de l'élément qui sera empilé */
  int tete;
} *tPileSommets;




/**
 * \defgroup Allocation Allocation, chargement et libération des graphes 
 *
 * Avant d'être utilisé, un graphe doit être alloué par la fonction
 grapheAlloue. Une fois utilisé, il est libéré par la fonction
 grapheLibere. Dans la majorité des cas, vous chargerez un graphe avec
 la fonction grapheChargeFichier.

Exemple typique d'utilisation:
   \code 
   tGraphe graphe;
   graphe = grapheAlloue();

   grapheChargeFichier(graphe, "fichier.grp");
 
   ... code ...

   grapheLibere(graphe);
   \endcode

 */
/*@{*/


/** 
    Initialisation d'un graphe.

    Exemple d'utilisation :
    \code
    tGraphe graphe;
    graphe = grapheAlloue();
    \endcode
 */
tGraphe grapheAlloue();

/** 
    Libère la mémoire occupée par un graphe.

    \param graphe : un graphe précédemment obtenu par 
    la fonction grapheAlloue()

    \code
    tGraphe graphe;
    graphe = grapheAlloue();

    ... code ...
 
    grapheLibere(graphe);
    \endcode
    
*/
void grapheLibere(tGraphe graphe);

/** Définit si un graphe est orienté ou pas
    \param graphe : un graphe (obtenu par grapheAlloue)
    \param oriente : 0 (=non-orienté) ou 1 (=orienté)
    Le graphe doit être vide, donc fraichement
    obtenu par grapheAlloue */
void grapheChangeType(tGraphe graphe, int oriente);


/** Crée un graphe aléatoire 
    \param graphe : un graphe (obtenu par grapheAlloue)
    \param nbSommets : le nombre de sommets
    \pram estOriente : 1 si on veut un graphe orienté, 0 sinon
    \param probaArc : la probabilité qu'il y ait un
    arc entre deux sommets quelconques

 */
void grapheAleatoire(tGraphe graphe, 
		     int nbSommets,
		     int estOriente,
		     double probaArc);

/**
   Charge un graphe depuis un fichier.
   \param graphe : un graphe (obtenu par grapheAlloue)
   \param fichier : un nom de fichier contenant un graphe

   Exemple d'utilisation :
   \code 
   tGraphe graphe;
   graphe = grapheAlloue();

   grapheChargeFichier(graphe, "fichier.grp");
 
   ... code ...

   grapheLibere(graphe);
   \endcode

*/
int grapheChargeFichier(tGraphe graphe, char *fichier);

/*@}*/


/* Modification */
  
/**
 * \defgroup Modification Modification des graphes 
 */
/*@{*/
/**
   Ajoute un sommet à un graphe 
   \param graphe : un graphe 
   \param sommet : un nom de sommet

   Le sommet ne doit pas déjà exister, et le graphe ne
   doit pas être plein.
 */
void grapheAjouteSommet(tGraphe graphe, tNomSommet sommet);

/**
   Ajoute un sommet à un graphe
   \param graphe : un graphe 
   \param arc : un arc

   L'arc ne doit pas déjà exister, et le graphe ne
   doit pas être plein. Si le graphe n'est pas orienté,
   l'arc est vu comme une arète.
 */
void grapheAjouteArc(tGraphe graphe, tArc arc);
/*@}*/


/* Consultation */


/**
 * \defgroup Consultation Consultation des graphes 
 */
/*@{*/

/**
   Affiche de manière détaillée un graphe.

   \param graphe : un graphe

   Exemple d'utilisation :
   \code
   tGraphe graphe;
   graphe = grapheAlloue();

   grapheChargeFichier(graphe, "fichier.gra");
 
   grapheAffiche(graphe);

   ... code ...

   grapheLibere(graphe);
   \endcode
*/
void grapheAffiche(tGraphe graphe);


/**
   Teste si un graphe est orienté ou pas.

   \param graphe : un graphe

   Renvoie 1 si le graphe est orienté, 0 sinon
*/
int grapheEstOriente(tGraphe graphe);

/**
   Renvoie le nombre de sommets d'un graphe

   \param graphe : un graphe
*/
int grapheNbSommets(tGraphe graphe);

/**
   Récupère le nom d'un sommet désigné par son numéro 

   \param graphe : un graphe
   \param numero : le numéro du sommet dont on veut le nom
   \param nomSommet : paramètre qui reçoit le nom du sommet

   Lance une erreur si le numéro n'est pas correct.

   Exemple :
   \code
      tNomSommet nom;
      grapheRecupNomSommet(graphe, 2, nom);
      // si l'appel n'a pas généré d'erreur, alors nom contient le nom du sommet
      printf("Le nom du sommet numéro 2 est : %s\n", nom);
   \endcode
*/
void grapheRecupNomSommet(tGraphe graphe, tNumeroSommet numero,
			  tNomSommet nomSommet);

/**
   Recherche un numéro de sommet à partir d'un nom

   \param graphe : un graphe
   \param nomSommet : nom du sommet dont on veut le numéro
   
   Renvoie le numéro si un sommet existe avec ce nom, sinon
   renvoie -1

   Exemple :
   \code
      tNumeroSommet numero;
      numero = grapheChercheSommetParNom(graphe, "A");
      if (numero == -1) 
        printf("Il n'y a pas de sommet nommé A dans le graphe\n")
      else
        printf("Le numéro du sommet A est : %d\n", numero);
   \endcode
  
*/
tNumeroSommet grapheChercheSommetParNom(tGraphe graphe, tNomSommet nomSommet); 

/**
   Renvoie le nombre de successeurs d'un sommet.

   \param graphe : un graphe \b orienté
   \param sommet : un numéro de sommet

   Renvoie le nombre de successeurs du sommet passé en paramètre.
   \warning déclenche une erreur si le graphe n'est pas orienté
   
*/
int grapheNbSuccesseursSommet(tGraphe graphe, tNumeroSommet sommet);

/**
   Renvoie le i-ème successeur d'un sommet.

   \param graphe : un graphe \b orienté
   \param sommet : un numéro de sommet
   \param i : un numéro de successeur

   Renvoie le successeur numéro \p i
   du sommet \p sommet.
   \warning déclenche une erreur si le graphe n'est pas orienté
   
*/
tNumeroSommet grapheSuccesseurSommetNumero(tGraphe graphe, 
					   tNumeroSommet sommet, 
					   int i);

/**
   Renvoie le nombre de prédécesseurs d'un sommet.

   \param graphe : un graphe \b orienté
   \param sommet : un numéro de sommet

   Renvoie le nombre de prédécesseurs du sommet passé en paramètre.
   \warning déclenche une erreur si le graphe n'est pas orienté
   
*/
int grapheNbPredecesseursSommet(tGraphe graphe, tNumeroSommet sommet);

/**
   Renvoie le i-ème prédécesseur d'un sommet.

   \param graphe : un graphe \b orienté
   \param sommet : un numéro de sommet
   \param i : un numéro de successeur

   Renvoie le successeur numéro \p i
   du sommet \p sommet.
   \warning déclenche une erreur si le graphe n'est pas orienté
   
*/
tNumeroSommet graphePredecesseurSommetNumero(tGraphe graphe, 
					     tNumeroSommet sommet, 
					     int i);

/**
   Renvoie le nombre de voisins d'un sommet.

   \param graphe : un graphe 
   \param sommet : un numéro de sommet

   Renvoie le nombre de voisins du sommet passé en paramètre.
*/
int grapheNbVoisinsSommet(tGraphe graphe, tNumeroSommet sommet);

/**
   Renvoie le i-ème voisin d'un sommet.

   \param graphe : un graphe \b orienté
   \param sommet : un numéro de sommet
   \param i : un numéro de successeur

   Renvoie le voisin numéro \p i
   du sommet \p sommet.
   
*/
tNumeroSommet grapheVoisinSommetNumero(tGraphe graphe, 
				       tNumeroSommet sommet, 
				       int i);


/**
   Renvoie le nombre d'arcs d'un graphe 

   \param graphe : un graphe

   Si le graphe n'est pas orienté, l'arc est vu comme
   une arète.
  
*/
int grapheNbArcs(tGraphe graphe);

/**
   Renvoie le i-ème arc d'un graphe

   \param graphe : un graphe
   \param i : un numéro d'arc

   Si le graphe n'est pas orienté, l'arc est vu comme
   une arète.
*/
tArc grapheRecupArcNumero(tGraphe graphe, int i);


/**
   Récupère la valeur d'un arc

   \param graphe : un graphe
   \param orig : numéro du sommet d'origine
   \param dest : numéro du sommet de destination

   Renvoie la valeur de l'arc. Si l'arc n'existe pas,
   la valeur nulle est renvoyée.
*/
tValeurArc grapheRecupValeurArc(tGraphe graphe,
			 tNumeroSommet orig,
			 tNumeroSommet dest);

/**
   Teste l'existence d'un arc.

   \param graphe : un graphe
   \param orig : numéro du sommet d'origine
   \param dest : numéro du sommet de destination

   Renvoie 1 si il existe un arc de \p orig vers \p dest,
   0 sinon.

   Si le graphe n'est pas orienté, l'arc est vu comme
   une arète.
*/
int grapheExisteArcEntre(tGraphe graphe,
			 tNumeroSommet orig,
			 tNumeroSommet dest);


/*@}*/


/**
 * \defgroup fileSommets Manipulation des files de sommets
 *
 * Définit des opérations sur les files de sommets, qui sont
 * utiles pour les parcours de graphe.
 * \include exempleFile.c
 */
/*@{*/

/** Alloue une nouvelle file */
tFileSommets fileSommetsAlloue();
/** Libère une file allouée par fileSommetsAlloue */
void fileSommetsLibere(tFileSommets);
/** Teste si une file est vide */
int fileSommetsEstVide(tFileSommets);
/** Teste si une file est pleine */
int fileSommetsEstPleine(tFileSommets);
/** Enfile un numéro de sommet */
void fileSommetsEnfile(tFileSommets, tNumeroSommet);
/** Défile un numéro de sommet */
tNumeroSommet fileSommetsDefile(tFileSommets);

/*@}*/


/**
 * \defgroup pileSommets Manipulation des piles de sommets
 * Définit des opérations sur les piles de sommets, qui sont
 * utiles pour les parcours de graphe.
 * \include exemplePile.c
 */
/*@{*/

/** Alloue une nouvelle pile */
tPileSommets pileSommetsAlloue();
/** Libère une pile allouée par pileSommetsAlloue */
void pileSommetsLibere(tPileSommets);
/** Teste si une pile est vide */
int pileSommetsEstVide(tPileSommets);
/** Teste si une pile est pleine */
int pileSommetsEstPleine(tPileSommets);
/** Affiche le contenu de la pile (pour déboguer uniquement) */
void pileSommetsAffiche(tPileSommets);
/** Récupère la valeur de la tête de la pile (sans la dépiler) */
tNumeroSommet pileSommetsTete(tPileSommets);
/** Empile un numéro de sommet */
void pileSommetsEmpile(tPileSommets, tNumeroSommet);
/** Dépile un numéro de sommet et le renvoie*/
tNumeroSommet pileSommetsDepile(tPileSommets);

/*@}*/



/* Déclenchement d'erreur */

/**
 * \defgroup erreur Déclenchement d'erreur
 *
 * Vous pouvez déclencher une erreur avec la fonction halt.
 * C'est cette fonction qui est appelée par la bibliothèque en cas d'erreur.
 * N'hésitez pas à l'utiliser vous même.
 */
/*@{*/

/**
   Permet d'afficher un message d'erreur, et de quitter le programme.
   
   L'utilisation est identique à celle de printf
*/
void halt(char * format, ...);

/*@}*/

#endif /* _GRAPHE_H_ */
