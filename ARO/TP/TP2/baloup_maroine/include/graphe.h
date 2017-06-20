/** 
  \file graphe.h
  \brief Fichier d'entÃªte de la bibliothÃ¨que sur les graphes


*/

/*! \mainpage BibliothÃ¨que de manipulation de graphes en C
 *

 * Cette bibliothÃ¨que fournit les opÃ©rations de base sur les graphes,
 * afin de rÃ©aliser facilement des opÃ©rations sur les graphes.
 * Vous devez lire les (courtes) sections qui suivent avant
 * d'aller regarder la documentation.
 *
 * - \subpage presentation 
 * - \subpage installation 
 * - \subpage syntaxe_graphe 
 * - \subpage consignes 
 
 \authors FranÃ§ois Lemaire, Arnaud Liefooghe, Marie-Emilie Voge, LÃ©opold Weinberg
 \date 2010


 * \page presentation PrÃ©sentation gÃ©nÃ©rale

 La bibliothÃ¨que permet de manipuler des graphes orientÃ©s ou non.
 Les graphes sont toujours valuÃ©s, et le type des valeurs
 des arcs/arÃªtes est double (flottant double prÃ©cision).
 Attention, la valeur nulle pour un arc/arÃªte est interdite.

 L'intÃ©rÃªt de cette bibliothÃ¨que est de pouvoir
 charger un fichier texte ou gÃ©nÃ©rer alÃ©atoirement
 des graphes, et de pouvoir consulter avec des fonctions
 d'interface des informations comme les voisins, successeurs, ...

 En interne, les donnÃ©es sont stockÃ©es pour amÃ©liorer l'efficacitÃ©
 des opÃ©rations. La mÃ©thode est simple : les donnÃ©es sont stockÃ©s
 sous diffÃ©rents formats (liste de voisins, liste de successeurs,
 matrice d'incidence, ...) afin d'avoir des opÃ©rations
 de consultation en coÃ»t constant.

 Les sommets des graphes sont des chaÃ®nes de caractÃ¨res.
 
 Les sommets sont manipulÃ©s par leur numÃ©ro, qui est compris
 entre 0 et le nombre de sommets moins un.
 
 * \page installation Installation/Compilation
 *
 * Il n'y a rien Ã  installer. Nous vous fournissons deux fichiers
 * <a href="graphe.h">graphe.h</a>
 * et
 * <a href="graphe.c">graphe.c</a>
 *
 * Vous utiliserez la compilation sÃ©parÃ©e.
 * TÃ©lÃ©charger le fichier d'exemple 
 * <a href="testAnalyseur.c">testAnalyseur.c</a>
 * et lancer la commande
 * \code
$ gcc -Wall -g -std=c99 testAnalyseur.c graphe.c -o testAnalyseur
 * \endcode

 * Votre programme se lance avec
 * \code
 * $ ./testAnalyseur <fichier_graphe>
 * \endcode
 * oÃ¹ fichier_graphe est un fichier contenant un graphe
 * au format dÃ©crit dans la section suivante.

 * Pour tester la commande prÃ©cÃ©dente, tÃ©lÃ©charger
 * le fichier <a href="ex-no.grp">ex-no.grp</a>
 * et lancez
 \code
 $ ./testAnalyseur ex-no.grp
 \endcode
 qui devrait vous afficher le contenu des graphe dans une version dÃ©taillÃ©e


 \page syntaxe_graphe Syntaxe des fichiers de graphe
 
 Vous pouvez mettre des commentaires d'une ligne grÃ¢ce au caractÃ¨re #
 suivi du commentaire. Le # peut apparaÃ®tre n'importe oÃ¹ dans la ligne.

 Le fichier doit avoir la syntaxe suivante :

\code

type = <oriente OU non-oriente>;

sommets = <liste de sommets sÃ©parÃ©s par des espaces> ;

arcs = <liste d'arcs sÃ©parÃ©s par des espaces, un arc Ã©tant reprÃ©sentÃ© par Origine Destination Valeur_de_l'arc> ;
\endcode

Les arcs ont par dÃ©faut le type double (flottant double prÃ©cision).

Exemple d'un graphe non orientÃ© :
\include ex-no.grp 

Exemple d'un graphe orientÃ© :
\include ex-o.grp 



\page consignes Consignes d'utilisation de la bibliothÃ¨que

Les structures de donnÃ©es sont commentÃ©es, mais uniquement
dans un but pÃ©dagogique. Lorsque vous utilisez la bibliothÃ¨que,
vous ne devez <b>jamais</b> accÃ¨der directement aux structures.
Vous devez utiliser les fonctions mises Ã  votre disposition.

L'intÃ©rÃªt est que si les structures de donnÃ©es de la 
bibliothÃ¨que changent en cours d'annÃ©e, votre code
continuera de fonctionner. De plus, lors du contrÃ´le
TP de fin de semestre, vous pourriez avoir une version
de la librairie avec des structures de donnÃ©es diffÃ©rentes,
il vaut mieux donc apprendre Ã  utiliser uniquement les
interfaces de fonctions.

Si vous estimez que des fonctions manquent, vous pouvez
toujours en parler Ã  votre enseignant et le convaincre
de la rajouter.


Vous devez toujours utiliser l'option <tt>-Wall</tt>.
En C, un avertissement est trÃ¨s souvent une erreur.
Vous Ãªtes encouragÃ©s Ã  utiliser en plus les
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

/** Type pour stocker un numÃ©ro de sommet. */
typedef int tNumeroSommet;

/** Type pour stocker la valeur d'un arc. */
typedef double tValeurArc;

/**
   Tableau de taille variable contenant des entiers (rÃ©servÃ© Ã  la librairie, ne pas utiliser).
   
   Attention : la taille est limitÃ©e au nombre maximum de sommets. 
   Exemple d'utilisation : pour colorer les sommets en couleur
*/
typedef struct  {
  /** le tableau d'entiers */
  int tab[MAX_SOMMETS];
  /** le nombre d'entiers effectivement utilisÃ©s dans le tableau */
  int nb;
} tTableauEntiers;

/** Type pour stocker un arc (vous pouvez accÃ©der aux champs
de ce type). */
typedef struct  {
  /** Le numÃ©ro de l'origine. */
  int orig;
  /** Le numÃ©ro de la destination. */
  int dest;
  /** La valeur de l'arc. */
  tValeurArc val;
} tArc;

/**
   Type pour stocker la liste des arcs (rÃ©servÃ© Ã  la librairie, ne pas utiliser)
   
   NB: limitÃ© Ã  MAX_ARCS arcs */
typedef struct  {
  /** Le tableau des arcs prÃ©allouÃ©. */
  tArc tab[MAX_ARCS];
  /** Le nombre d'arcs qui ont Ã©tÃ© stockÃ©s dans le tableau. */
  int nb;
} tTableauArcs;

/** Type pour stocker un arbre (ne pas accÃ©der aux champs directement,
 mais utiliser l'interface) */
typedef struct tGraphe{
  /** Orientation de l'arbre.
      Vaut 1 si l'arbre est orientÃ©, 0 sinon.  */
  int estOriente;

  /** \brief Nombre de sommets. */
  int nbSommets;
  /** Nom des sommets. */
  tNomSommet nomSommets[MAX_SOMMETS];

  /** La matrice d'adjacence.

      Si il y a un arc de i Ã  j, alors
      matriceAdjacence[i][j] contient la valeur de l'arc.
      Sinon, matriceAdjacence[i][j] vaut 0.
   */
  tValeurArc matriceAdjacence[MAX_SOMMETS][MAX_SOMMETS];
  
  /** Tableaux des successeurs.
      
      Ce tableau n'est rempli que pour les graphes orientÃ©s.
      Pour tout sommet i, 
      tableSuccesseurs[i] est le tableau des successeurs
      du sommet i. */
  tTableauEntiers tableSuccesseurs[MAX_SOMMETS];

  /** Tableaux des prÃ©dÃ©cesseurs.
      
      Ce tableau n'est rempli que pour les graphes orientÃ©s.
      Pour tout sommet i, 
      tablePredecesseurs[i] est le tableau des successeurs
      du sommet i. */
  tTableauEntiers tablePredecesseurs[MAX_SOMMETS];

  /** Tableaux des voisins.
      
      Ce tableau n'est rempli que pour les graphes non orientÃ©s.
      Pour tout sommet i, 
      tableVoisins[i] est le tableau des successeurs
      du sommet i. */
  tTableauEntiers tableVoisins[MAX_SOMMETS];


  /** Tableau des arcs.

      Ce tableau contient la liste de tous les arcs */
  tTableauArcs tableArcs;


} *tGraphe;



/** Type pour stocker une file de sommets (ne pas accÃ©der aux champs
 directement, mais utiliser l'interface)*/
typedef struct tFileSommets {
  /** tableau de MAX_SOMMETS+1 numÃ©ros */
  tNumeroSommet tab[MAX_SOMMETS+1];

  /** indice de l'Ã©lÃ©ment qui sera dÃ©filÃ© */
  int debut;
  /** indice oÃ¹ le prochain Ã©lÃ©ment sera enfilÃ© */
  int fin;
} *tFileSommets;


/** Type pour stocker une pile de sommets (ne pas accÃ©der aux champs
 directement, mais utiliser l'interface)*/
typedef struct tPileSommets {
  /** tableau de MAX_SOMMETS numÃ©ros */
  tNumeroSommet tab[MAX_SOMMETS];

  /** indice de l'Ã©lÃ©ment qui sera empilÃ© */
  int tete;
} *tPileSommets;




/**
 * \defgroup Allocation Allocation, chargement et libÃ©ration des graphes 
 *
 * Avant d'Ãªtre utilisÃ©, un graphe doit Ãªtre allouÃ© par la fonction
 grapheAlloue. Une fois utilisÃ©, il est libÃ©rÃ© par la fonction
 grapheLibere. Dans la majoritÃ© des cas, vous chargerez un graphe avec
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
    LibÃ¨re la mÃ©moire occupÃ©e par un graphe.

    \param graphe : un graphe prÃ©cÃ©demment obtenu par 
    la fonction grapheAlloue()

    \code
    tGraphe graphe;
    graphe = grapheAlloue();

    ... code ...
 
    grapheLibere(graphe);
    \endcode
    
*/
void grapheLibere(tGraphe graphe);

/** DÃ©finit si un graphe est orientÃ© ou pas
    \param graphe : un graphe (obtenu par grapheAlloue)
    \param oriente : 0 (=non-orientÃ©) ou 1 (=orientÃ©)
    Le graphe doit Ãªtre vide, donc fraichement
    obtenu par grapheAlloue */
void grapheChangeType(tGraphe graphe, int oriente);


/** CrÃ©e un graphe alÃ©atoire 
    \param graphe : un graphe (obtenu par grapheAlloue)
    \param nbSommets : le nombre de sommets
    \pram estOriente : 1 si on veut un graphe orientÃ©, 0 sinon
    \param probaArc : la probabilitÃ© qu'il y ait un
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
   Ajoute un sommet Ã  un graphe 
   \param graphe : un graphe 
   \param sommet : un nom de sommet

   Le sommet ne doit pas dÃ©jÃ  exister, et le graphe ne
   doit pas Ãªtre plein.
 */
void grapheAjouteSommet(tGraphe graphe, tNomSommet sommet);

/**
   Ajoute un sommet Ã  un graphe
   \param graphe : un graphe 
   \param arc : un arc

   L'arc ne doit pas dÃ©jÃ  exister, et le graphe ne
   doit pas Ãªtre plein. Si le graphe n'est pas orientÃ©,
   l'arc est vu comme une arÃ¨te.
 */
void grapheAjouteArc(tGraphe graphe, tArc arc);
/*@}*/


/* Consultation */


/**
 * \defgroup Consultation Consultation des graphes 
 */
/*@{*/

/**
   Affiche de maniÃ¨re dÃ©taillÃ©e un graphe.

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
   Teste si un graphe est orientÃ© ou pas.

   \param graphe : un graphe

   Renvoie 1 si le graphe est orientÃ©, 0 sinon
*/
int grapheEstOriente(tGraphe graphe);

/**
   Renvoie le nombre de sommets d'un graphe

   \param graphe : un graphe
*/
int grapheNbSommets(tGraphe graphe);

/**
   RÃ©cupÃ¨re le nom d'un sommet dÃ©signÃ© par son numÃ©ro 

   \param graphe : un graphe
   \param numero : le numÃ©ro du sommet dont on veut le nom
   \param nomSommet : paramÃ¨tre qui reÃ§oit le nom du sommet

   Lance une erreur si le numÃ©ro n'est pas correct.

   Exemple :
   \code
      tNomSommet nom;
      grapheRecupNomSommet(graphe, 2, nom);
      // si l'appel n'a pas gÃ©nÃ©rÃ© d'erreur, alors nom contient le nom du sommet
      printf("Le nom du sommet numÃ©ro 2 est : %s\n", nom);
   \endcode
*/
void grapheRecupNomSommet(tGraphe graphe, tNumeroSommet numero,
			  tNomSommet nomSommet);

/**
   Recherche un numÃ©ro de sommet Ã  partir d'un nom

   \param graphe : un graphe
   \param nomSommet : nom du sommet dont on veut le numÃ©ro
   
   Renvoie le numÃ©ro si un sommet existe avec ce nom, sinon
   renvoie -1

   Exemple :
   \code
      tNumeroSommet numero;
      numero = grapheChercheSommetParNom(graphe, "A");
      if (numero == -1) 
        printf("Il n'y a pas de sommet nommÃ© A dans le graphe\n")
      else
        printf("Le numÃ©ro du sommet A est : %d\n", numero);
   \endcode
  
*/
tNumeroSommet grapheChercheSommetParNom(tGraphe graphe, tNomSommet nomSommet); 

/**
   Renvoie le nombre de successeurs d'un sommet.

   \param graphe : un graphe \b orientÃ©
   \param sommet : un numÃ©ro de sommet

   Renvoie le nombre de successeurs du sommet passÃ© en paramÃ¨tre.
   \warning dÃ©clenche une erreur si le graphe n'est pas orientÃ©
   
*/
int grapheNbSuccesseursSommet(tGraphe graphe, tNumeroSommet sommet);

/**
   Renvoie le i-Ã¨me successeur d'un sommet.

   \param graphe : un graphe \b orientÃ©
   \param sommet : un numÃ©ro de sommet
   \param i : un numÃ©ro de successeur

   Renvoie le successeur numÃ©ro \p i
   du sommet \p sommet.
   \warning dÃ©clenche une erreur si le graphe n'est pas orientÃ©
   
*/
tNumeroSommet grapheSuccesseurSommetNumero(tGraphe graphe, 
					   tNumeroSommet sommet, 
					   int i);

/**
   Renvoie le nombre de prÃ©dÃ©cesseurs d'un sommet.

   \param graphe : un graphe \b orientÃ©
   \param sommet : un numÃ©ro de sommet

   Renvoie le nombre de prÃ©dÃ©cesseurs du sommet passÃ© en paramÃ¨tre.
   \warning dÃ©clenche une erreur si le graphe n'est pas orientÃ©
   
*/
int grapheNbPredecesseursSommet(tGraphe graphe, tNumeroSommet sommet);

/**
   Renvoie le i-Ã¨me prÃ©dÃ©cesseur d'un sommet.

   \param graphe : un graphe \b orientÃ©
   \param sommet : un numÃ©ro de sommet
   \param i : un numÃ©ro de successeur

   Renvoie le successeur numÃ©ro \p i
   du sommet \p sommet.
   \warning dÃ©clenche une erreur si le graphe n'est pas orientÃ©
   
*/
tNumeroSommet graphePredecesseurSommetNumero(tGraphe graphe, 
					     tNumeroSommet sommet, 
					     int i);

/**
   Renvoie le nombre de voisins d'un sommet.

   \param graphe : un graphe 
   \param sommet : un numÃ©ro de sommet

   Renvoie le nombre de voisins du sommet passÃ© en paramÃ¨tre.
*/
int grapheNbVoisinsSommet(tGraphe graphe, tNumeroSommet sommet);

/**
   Renvoie le i-Ã¨me voisin d'un sommet.

   \param graphe : un graphe \b orientÃ©
   \param sommet : un numÃ©ro de sommet
   \param i : un numÃ©ro de successeur

   Renvoie le voisin numÃ©ro \p i
   du sommet \p sommet.
   
*/
tNumeroSommet grapheVoisinSommetNumero(tGraphe graphe, 
				       tNumeroSommet sommet, 
				       int i);


/**
   Renvoie le nombre d'arcs d'un graphe 

   \param graphe : un graphe

   Si le graphe n'est pas orientÃ©, l'arc est vu comme
   une arÃ¨te.
  
*/
int grapheNbArcs(tGraphe graphe);

/**
   Renvoie le i-Ã¨me arc d'un graphe

   \param graphe : un graphe
   \param i : un numÃ©ro d'arc

   Si le graphe n'est pas orientÃ©, l'arc est vu comme
   une arÃ¨te.
*/
tArc grapheRecupArcNumero(tGraphe graphe, int i);


/**
   RÃ©cupÃ¨re la valeur d'un arc

   \param graphe : un graphe
   \param orig : numÃ©ro du sommet d'origine
   \param dest : numÃ©ro du sommet de destination

   Renvoie la valeur de l'arc. Si l'arc n'existe pas,
   la valeur nulle est renvoyÃ©e.
*/
tValeurArc grapheRecupValeurArc(tGraphe graphe,
			 tNumeroSommet orig,
			 tNumeroSommet dest);

/**
   Teste l'existence d'un arc.

   \param graphe : un graphe
   \param orig : numÃ©ro du sommet d'origine
   \param dest : numÃ©ro du sommet de destination

   Renvoie 1 si il existe un arc de \p orig vers \p dest,
   0 sinon.

   Si le graphe n'est pas orientÃ©, l'arc est vu comme
   une arÃ¨te.
*/
int grapheExisteArcEntre(tGraphe graphe,
			 tNumeroSommet orig,
			 tNumeroSommet dest);


/*@}*/


/**
 * \defgroup fileSommets Manipulation des files de sommets
 *
 * DÃ©finit des opÃ©rations sur les files de sommets, qui sont
 * utiles pour les parcours de graphe.
 * \include exempleFile.c
 */
/*@{*/

/** Alloue une nouvelle file */
tFileSommets fileSommetsAlloue();
/** LibÃ¨re une file allouÃ©e par fileSommetsAlloue */
void fileSommetsLibere(tFileSommets);
/** Teste si une file est vide */
int fileSommetsEstVide(tFileSommets);
/** Teste si une file est pleine */
int fileSommetsEstPleine(tFileSommets);
/** Enfile un numÃ©ro de sommet */
void fileSommetsEnfile(tFileSommets, tNumeroSommet);
/** DÃ©file un numÃ©ro de sommet */
tNumeroSommet fileSommetsDefile(tFileSommets);

/*@}*/


/**
 * \defgroup pileSommets Manipulation des piles de sommets
 * DÃ©finit des opÃ©rations sur les piles de sommets, qui sont
 * utiles pour les parcours de graphe.
 * \include exemplePile.c
 */
/*@{*/

/** Alloue une nouvelle pile */
tPileSommets pileSommetsAlloue();
/** LibÃ¨re une pile allouÃ©e par pileSommetsAlloue */
void pileSommetsLibere(tPileSommets);
/** Teste si une pile est vide */
int pileSommetsEstVide(tPileSommets);
/** Teste si une pile est pleine */
int pileSommetsEstPleine(tPileSommets);
/** Affiche le contenu de la pile (pour dÃ©boguer uniquement) */
void pileSommetsAffiche(tPileSommets);
/** RÃ©cupÃ¨re la valeur de la tÃªte de la pile (sans la dÃ©piler) */
tNumeroSommet pileSommetsTete(tPileSommets);
/** Empile un numÃ©ro de sommet */
void pileSommetsEmpile(tPileSommets, tNumeroSommet);
/** DÃ©pile un numÃ©ro de sommet et le renvoie*/
tNumeroSommet pileSommetsDepile(tPileSommets);

/*@}*/



/* DÃ©clenchement d'erreur */

/**
 * \defgroup erreur DÃ©clenchement d'erreur
 *
 * Vous pouvez dÃ©clencher une erreur avec la fonction halt.
 * C'est cette fonction qui est appelÃ©e par la bibliothÃ¨que en cas d'erreur.
 * N'hÃ©sitez pas Ã  l'utiliser vous mÃªme.
 */
/*@{*/

/**
   Permet d'afficher un message d'erreur, et de quitter le programme.
   
   L'utilisation est identique Ã  celle de printf
*/
void halt(char * format, ...);

/*@}*/

#endif /* _GRAPHE_H_ */