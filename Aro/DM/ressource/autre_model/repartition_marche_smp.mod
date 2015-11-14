/* Commande script AMPL */
reset;

/* Solveur � utiliser : GUROBI, (permet de resoudre des models lineaires contenant des nombres entiers */
option solver gurobi;

/* Ensembles -------------------------------------------------------------------------------------------------------------------- */	
set REGIONS;
set DETAILLANTS;
set CATEGORIES;

/* Param�tres ------------------------------------------------------------------------------------------------------------------- */
/* Param�tres repr�sentant les rapports ainsi que la tol�rance qui doivent �tre appliqu� au mod�le */
param rapport_marcheD1 >= 0,  <= 100;
param tolerance >= 0,  <= 100;

/* Param�tres indic� par les detaillants ayant comme ensemble de donn�, regions (type de donn�e region)  */
param region {DETAILLANTS} symbolic in REGIONS;
param categorie {DETAILLANTS} symbolic in CATEGORIES;
param nb_huile {DETAILLANTS} integer >= 0;
param nb_pts_vente {DETAILLANTS} integer >= 0;
param nb_spiritueux {DETAILLANTS} integer >= 0;

/* Parametres calcul�s */
/* Param�tres calcul�s, nombre global de points de ventes */
param nb_global_pts_vente := sum {dt in DETAILLANTS}  nb_pts_vente [dt];

/* Param�tres calcul�s, nombre global des spiritieux */
param nb_global_spiritieux := sum {dt in DETAILLANTS} nb_spiritueux [dt];

/* Param�tres calcul�s, nombre d'huile global par regions 
param nb_global_huile_region {rg in REGIONS} := sum {dt in DETAILLANTS} if region [dt] = rg then nb_huile [dt] else 0;

/* Param�tres calcul�s, nombre d'huile global par regions 
param nb_global_detaillant_categorie {ct in CATEGORIES} := sum {dt in DETAILLANTS} if categorie [dt] = ct then 1 else 0;

/* Param�tres calcul�s par rapport au borne donn� par l�utilisateur et par la tolerance */ 
param rpmD1_tol_min := rapport_marcheD1 - tolerance;
param rpmD1_tol_max := rapport_marcheD1 + tolerance;

/* Variables -------------------------------------------------------------------------------------------------------------------- */
/* Variables binaire representant le fait que la ligne est valid� ou non, en fonction du rapport concernant le nombre de points de vente */
var affectationD1 {dt in DETAILLANTS} binary;

/* Objectif --------------------------------------------------------------------------------------------------------------------- */
/* Objectif fixe */
maximize 
objectif_statique :
	100;

/* Contraintes ------------------------------------------------------------------------------------------------------------------ */
/* Contraintes d'unicit� 
subject to 
affectation_unique_detaillant {dt in DETAILLANTS} :
	sum {dv in DIVISIONS} affectationD1 [dt] <= 1; 
*/
		
/* Contraintes sur les differents rapports */
/* Commentaire ... */
subject to 
rapport_nb_pts_vente_global :
	rpmD1_tol_min * nb_global_pts_vente / 100  <= sum {dt in DETAILLANTS} affectationD1 [dt] * nb_pts_vente [dt] <= rpmD1_tol_max * nb_global_pts_vente / 100 ;
	
/* ... */
subject to
rapport_marche_spiritieux_global :
	rpmD1_tol_min * nb_global_spiritieux / 100 <= sum {dt in DETAILLANTS} affectationD1 [dt] * nb_spiritueux [dt] <= rpmD1_tol_max * nb_global_spiritieux / 100;

/* ... */
subject to
rapport_marche_huile_region_min {rg in REGIONS}: 
	   (sum {dt in DETAILLANTS} affectationD1 [dt] * (if region [dt] = rg then nb_huile [dt] else 0)) / (sum {dt2 in DETAILLANTS} (if region [dt2] = rg then nb_huile [dt2] else 0)) * 100 >= 35;

subject to
rapport_marche_huile_region_max {rg in REGIONS}: 
	   (sum {dt in DETAILLANTS} affectationD1 [dt] * (if region [dt] = rg then nb_huile [dt] else 0)) / (sum {dt2 in DETAILLANTS} (if region [dt2] = rg then nb_huile [dt2] else 0)) * 100 <= 45;
/* ... 	
subject to
rapport_nb_detaillant_categorie {ct in CATEGORIES}: 
	rpmD1_tol_min * nb_global_detaillant_categorie [ct] / 100 <= sum {dt in DETAILLANTS} affectationD1 [dt] <= rpmD1_tol_max * nb_global_detaillant_categorie [ct] / 100;
	
/* Inclusion des donn�es */
data "repartition_marche_smp.dat";

/* Commande Script AMPL */
/* Resolution du model */
solve;

/* Affichage des donn�es du model */
display affectationD1;