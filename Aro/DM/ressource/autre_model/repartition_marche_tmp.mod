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

/* Variables binaire representant le fait que la ligne est validé ou non, en fonction du rapport concernant le nombre de points de vente */
var npvb {dv in DIVISIONS, dt in DETAILLANTS} binary;

/* Variables binaire representant le fait que la ligne est validé ou non, en fonction du rapport concernant le marché des spiritueux */
var msb {dv in DIVISIONS, dt in DETAILLANTS} binary;

/* Variables binaire representant le fait que la ligne est validé ou non, en fonction du rapport concernant le marché d'huiles par regions */
var mhb {dv in DIVISIONS, dt in DETAILLANTS, rg in REGIONS} binary;

/* Variables binaire representant le fait que la ligne est validé ou non, en fonction du rapport concernant le nombre de detaillants par categories */
var ndb {dv in DIVISIONS, dt in DETAILLANTS, ct in CATEGORIES} binary;


/* AFFICHAGE ------------------------------ */
param affichage_affectation {DETAILLANTS} symbolic in DIVISIONS;
for {dt in DETAILLANTS} {
	for {dv in DIVISIONS} {
		if affectation [dt, dv] == 1 then {
			let affichage_affectation [dt] := dv;
		}
	}
}


display affichage_affectation;