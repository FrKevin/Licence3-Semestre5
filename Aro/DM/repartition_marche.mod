/* Solveur à utiliser */
option solver minos;

/* Ensembles -------------------------------------------------------------------------------------------------------------------- */	
SET DIVISIONS;
SET REGIONS;
SET DETAILLANTS;
SET CATEGORIES;

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
param nb_total_point_vente := sum {d in DETAILLANTS}  nb_pts_vente [d];

/* Variables -------------------------------------------------------------------------------------------------------------------- */
/* Variables indicés par les divisions */

/* 
  Le nombre de detaillant par categories (voir 4)  
  exemple: nb_detaillant [D1][A] = 10
*/
var nb_detaillant {DIVISION, CATEGORIE} integer >=0; 

/* Le nombre de points de vente par division (voir 1) */
var nb_pts_vente{DIVISIONS} integer >=0; 

/* Le nombre de spiritueux par division (voir 2) */
var nb _spiritueux{DIVISIONS} integer >= 0;

/* Le nombre de spiritueux par division (voir 3) */
var nb_huile{DIVISIONS} integer >= 0;

/* Contraintes */
