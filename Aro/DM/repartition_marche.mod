/* Commande script AMPL */
reset;

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
/* Param�tres calcul�s, nombre d'huile par region et pour chaque detaillant */
param nhuile_region_detaillant {rg in REGIONS, dt in DETAILLANTS} := if region [dt] = rg then nb_huile [dt] else 0;

/* Param�tres calcul�s, nombre de detaillant par categorie et pour chaque detaillant */
param ndetail_categorie_detaillant {ct in CATEGORIES, dt in DETAILLANTS} := if categorie [dt] = ct then 1 else 0;

/* Param�tres calcul�s, nombre global de points de ventes */
param nb_global_pts_vente := sum {dt in DETAILLANTS}  nb_pts_vente [dt];

/* Param�tres calcul�s, nombre global des spiritieux */
param nb_global_spiritieux := sum {dt in DETAILLANTS} nb_spiritueux [dt];

/* Param�tres calcul�s, nombre d'huile global par regions */
param nb_global_huile_region {rg in REGIONS} := sum {dt in DETAILLANTS} if region [dt] = rg then nb_huile [dt] else 0;

/* Param�tres calcul�s, nombre de detaillants global par categories */
param nb_global_detaillant_categorie {ct in CATEGORIES} := sum {dt in DETAILLANTS} if categorie [dt] = ct then 1 else 0;

/* Param�tres calcul�s par rapport au borne donn� par l�utilisateur et par la tolerance */ 
param rpm_tol_min {dv in DIVISIONS} := (rapport_marche [dv] - tolerance) / 100;
param rpm_tol_max {dv in DIVISIONS} := (rapport_marche [dv] + tolerance) / 100;

/* Variables -------------------------------------------------------------------------------------------------------------------- */
/* Variables binaire representant le fait que la ligne est valid� ou non, en fonction du rapport concernant le nombre de points de vente */
var affectation {dt in DETAILLANTS, dv in DIVISIONS} binary;

/* ... *
var ecart_tolerance >= 0, <= 1;

/* Objectif --------------------------------------------------------------------------------------------------------------------- */
/* Objectif fixe */
minimize 
obj_ecart_tolerance :
	100;/*ecart_tolerance * tolerance;*/

/* Contraintes ------------------------------------------------------------------------------------------------------------------ */
/* Contraintes d'unicit� */
subject to 
affectation_unique_detaillant {dt in DETAILLANTS} :
	sum {dv in DIVISIONS} affectation [dt, dv] == 1; 
		
subject to
tolerance_max {dv in DIVISIONS} :
	tolerance <= rapport_marche [dv];
	
/* Contraintes sur les differents rapports */
/* Commentaire ... */ 
subject to 
rapport_nb_pts_vente_global {dv in DIVISIONS}:
	rpm_tol_min [dv] * nb_global_pts_vente <= sum {dt in DETAILLANTS} affectation [dt, dv] * nb_pts_vente [dt]  <= rpm_tol_max [dv] * nb_global_pts_vente;

/* ... */
subject to
rapport_marche_spiritieux_global {dv in DIVISIONS}:
	rpm_tol_min [dv] * nb_global_spiritieux <= sum {dt in DETAILLANTS} affectation [dt, dv] * nb_spiritueux [dt] <= rpm_tol_max [dv] * nb_global_spiritieux;

/* ... 
Note, cette contrainte rend le model infaisable, le solveur n'arrive pas � trouver une solution */
subject to
rapport_marche_huile_region {dv in DIVISIONS, rg in REGIONS}: 
	rpm_tol_min [dv] * nb_global_huile_region [rg] <= (sum {dt in DETAILLANTS} affectation [dt, dv] * nhuile_region_detaillant [rg, dt]) <= rpm_tol_max [dv] * nb_global_huile_region [rg];

/* ... 
Note, cette contrainte rend le model infaisable, le solveur n'arrive pas � trouver une solution	*/
subject to 
rapport_nb_detaillant_categorie {dv in DIVISIONS, ct in CATEGORIES}: 
	rpm_tol_min [dv] * nb_global_detaillant_categorie [ct] <= (sum {dt in DETAILLANTS} affectation [dt, dv] * ndetail_categorie_detaillant [ct, dt]) <= rpm_tol_max [dv] * nb_global_detaillant_categorie [ct];
	
/* Inclusion des donn�es */
data "repartition_marche.dat";

/* Commande Script AMPL */
/* Resolution du model */
solve;

/* Affichage des donn�es du model */
display affectation;
display rpm_tol_min;
display nb_global_huile_region;