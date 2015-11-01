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