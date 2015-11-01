/* Solveur à utiliser */
option solver minos;

/* Ensembles -------------------------------------------------------------------------------------------------------------------- */	
set DIVISIONS := {A, B};
set REGIONS;
set DETAILLANTS;
set CATEGORIES;

/* Paramètres ------------------------------------------------------------------------------------------------------------------- */
/* Paramètres représentant les rapports ainsi que la tolérance qui doivent être appliqué au modèle */
param rapport_borne_min >= 0,  <= 100;
param rapport_borne_max >= 0,  <= 100;
param tolerance >= 0,  <= 100;

/* Paramétres indicé par les detaillants ayant comme ensemble de donné, regions (type de donnée region)  */
param region {DETAILLANTS} symbolic in REGIONS;
param categorie {DETAILLANTS} symbolic in CATEGORIES;
param nb_huile {DETAILLANTS} integer >=0;
param nb_pts_vente {DETAILLANTS} integer>=0;
param nb_spiritueux {DETAILLANTS} integer >=0;

/* Parametres calculés */
/* Paramètres calculés par rapport au borne donné par l’utilisateur et par la tolerance */ 
param rapport_borne_min_tolerance_min := rapport_borne_min - tolerance;
param rapport_borne_min_tolerance_max := rapport_borne_min + tolerance,

param rapport_borne_max_tolerance_min := rapport_borne_max - tolerance;
param rapport_borne_max_tolerance_max : = rapport_borne_max + tolerance;

/* Paramètres calculés, nombre total de points de ventes */
param nb_total_pts_vente := sum {d in DETAILLANTS}  nb_pts_vente [d];

/* Paramètres calculés, nombre total des spiritieux */
param nb_total_spiritieux := sum {d in DETAILLANTS} nb_spiritueux [d];


/* Variables -------------------------------------------------------------------------------------------------------------------- */
/* Variables binaire, experimantal */
/* Variables binaire representant le fait que la ligne est validé ou non, en fonction du rapport concernant le nombre de points de vente */
var npvb {dv in DIVISIONS, dt in DETAILLANTS} binary;

/* Variables binaire representant le fait que la ligne est validé ou non, en fonction du rapport concernant le marché des spiritueux */
var msb {dv in DIVISIONS, dt in DETAILLANTS} binary;

/* Variables binaire representant le fait que la ligne est validé ou non, en fonction du rapport concernant le marché d'huiles par regions */
var mhb {dv in DIVISIONS, dt in DETAILLANTS, rg in REGIONS} binary;

/* Variables binaire representant le fait que la ligne est validé ou non, en fonction du rapport concernant le nombre de detaillants par categories */
var ndb {dv in DIVISIONS, dt in DETAILLANTS, ct in CATEGORIES} binary;

/* Contraintes */

subject to rapport_nb_pts_vente {dv in DIVISIONS, dt in DETAILLANTS} 