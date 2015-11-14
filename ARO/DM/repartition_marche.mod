
/* Solveur � utiliser : GUROBI, (permet de resoudre des models lineaires contenant des nombres entiers */
option solver gurobi;

/* Ensembles -------------------------------------------------------------------------------------------------------------------- */	
set DIVISIONS;
set REGIONS;
set DETAILLANTS;
set CATEGORIES;

/* Param�tres ------------------------------------------------------------------------------------------------------------------- */
/* Param�tres repr�sentant les rapports ainsi que la tol�rance qui doivent �tre appliqu� au mod�le */
param rapport_marche {DIVISIONS} >= 0,  <= 100;
param tolerance >= 0,  <= 100;

/* Param�tres indic� par les detaillants ayant comme ensemble de donn�, regions (type de donn�e region)  */
param region {DETAILLANTS} symbolic in REGIONS;
param categorie {DETAILLANTS} symbolic in CATEGORIES;
param nb_huile {DETAILLANTS} integer >= 0;
param nb_pts_vente {DETAILLANTS} integer >= 0;
param nb_spiritueux {DETAILLANTS} integer >= 0;

/* Parametres calcul�s */
/* Param�tres calcul�s par rapport au borne donn� par l�utilisateur et par la tolerance */ 
param rapport_marche_tol_min {dv in DIVISIONS} := rapport_marche [dv] - tolerance;
param rapport_marche_tol_max {dv in DIVISIONS} := rapport_marche [dv] + tolerance,

/* Param�tres calcul�s, nombre global de points de ventes */
param nb_global_pts_vente := sum {dt in DETAILLANTS}  nb_pts_vente [dt];

/* Param�tres calcul�s, nombre global des spiritieux */
param nb_global_spiritieux := sum {dt in DETAILLANTS} nb_spiritueux [dt];

/* Param�tres calcul�s, nombre d'huile global par regions */
param nb_global_huile_region {rg in REGIONS} := sum {dt in DETAILLANTS} if region [dt] = rg then nb_huile [dt] else 0;

/* Param�tres calcul�s, nombre d'huile global par regions */
param nb_global_detaillant_categorie {ct in CATEGORIE} := sum {dt in DETAILLANTS} if categorie [dt] = ct then 1 else 0;

/* Variables -------------------------------------------------------------------------------------------------------------------- */
/* Variables binaire representant le fait que la ligne est valid� ou non, en fonction du rapport concernant le nombre de points de vente */
var affectation {dt in DETAILLANTS, dv in DIVISIONS} binary;

/* Objectif --------------------------------------------------------------------------------------------------------------------- */
/* Objectif fixe */
maximize 
objectif_statique :
	100;

/* Contraintes ------------------------------------------------------------------------------------------------------------------ */
/* Contraintes d'unicit� */
subject to 
affectation_unique_detaillant {dt in DETAILLANTS} :
	sum {dv in DIVISIONS} affectation [dt, dv] = 1; /* ou <= ambiguit� du sujet */
		
/* Contraintes sur les differents rapports (sans les tolerances pour l'instant) */
/* Commentaire ... */
subject to 
rapport_nb_pts_vente_global {dv in DIVISIONS}:
	sum {dt in DETAILLANTS} affectation [dt, dv] * nb_pts_vente [dt] <= rapport_marche [dv] * nb_global_pts_vente / 100;
	
/* ... */
subject to
rapport_marche_spiritieux_global {dv in DIVISIONS}:
	sum {dt in DETAILLANTS} affectation [dt, dv] * nb_spiritueux [dt] <= rapport_marche [dv] * nb_global_spiritieux / 100;

/* ... */
subject to
rapport_marche_huile_region {dv in DIVISIONS}: 
	sum {dt in DETAILLANTS} affectation [dt, dv] * nb_huile [dt] <= rapport_marche [dv] * nb_global_huile_region [region [dt]] / 100;

/* ... */	
subject to 
rapport_nb_detaillant_categorie {dv in DIVISIONS}: 
	sum {dt in DETAILLANTS} affectation [dt, dv] <= rapport_marche [dv] * nb_global_detaillant [categorie [dt]] / 100;
