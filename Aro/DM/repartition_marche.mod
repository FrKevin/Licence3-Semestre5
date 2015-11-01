/* Solveur � utiliser */
option solver minos;

/* Ensembles -------------------------------------------------------------------------------------------------------------------- */	
set DIVISIONS := {A, B};
set REGIONS;
set DETAILLANTS;
set CATEGORIES;

/* Param�tres ------------------------------------------------------------------------------------------------------------------- */
/* Param�tres repr�sentant les rapports ainsi que la tol�rance qui doivent �tre appliqu� au mod�le */
param rapport_borne_min >= 0,  <= 100;
param rapport_borne_max >= 0,  <= 100;
param tolerance >= 0,  <= 100;

/* Param�tres indic� par les detaillants ayant comme ensemble de donn�, regions (type de donn�e region)  */
param region {DETAILLANTS} symbolic in REGIONS;
param categorie {DETAILLANTS} symbolic in CATEGORIES;
param nb_huile {DETAILLANTS} integer >=0;
param nb_pts_vente {DETAILLANTS} integer>=0;
param nb_spiritueux {DETAILLANTS} integer >=0;

/* Parametres calcul�s */
/* Param�tres calcul�s par rapport au borne donn� par l�utilisateur et par la tolerance */ 
param rapport_borne_min_tolerance_min := rapport_borne_min - tolerance;
param rapport_borne_min_tolerance_max := rapport_borne_min + tolerance,

param rapport_borne_max_tolerance_min := rapport_borne_max - tolerance;
param rapport_borne_max_tolerance_max : = rapport_borne_max + tolerance;

/* Param�tres calcul�s, nombre total de points de ventes */
param nb_total_pts_vente := sum {d in DETAILLANTS}  nb_pts_vente [d];

/* Param�tres calcul�s, nombre total des spiritieux */
param nb_total_spiritieux := sum {d in DETAILLANTS} nb_spiritueux [d];


/* Variables -------------------------------------------------------------------------------------------------------------------- */
/* Variables binaire, experimantal */
/* Variables binaire representant le fait que la ligne est valid� ou non, en fonction du rapport concernant le nombre de points de vente */
var npvb {dv in DIVISIONS, dt in DETAILLANTS} binary;

/* Variables binaire representant le fait que la ligne est valid� ou non, en fonction du rapport concernant le march� des spiritueux */
var msb {dv in DIVISIONS, dt in DETAILLANTS} binary;

/* Variables binaire representant le fait que la ligne est valid� ou non, en fonction du rapport concernant le march� d'huiles par regions */
var mhb {dv in DIVISIONS, dt in DETAILLANTS, rg in REGIONS} binary;

/* Variables binaire representant le fait que la ligne est valid� ou non, en fonction du rapport concernant le nombre de detaillants par categories */
var ndb {dv in DIVISIONS, dt in DETAILLANTS, ct in CATEGORIES} binary;

/* Contraintes */

subject to rapport_nb_pts_vente {dv in DIVISIONS, dt in DETAILLANTS} 