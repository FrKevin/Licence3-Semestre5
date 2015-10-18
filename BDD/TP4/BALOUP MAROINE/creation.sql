/*
MAROINE Maxime, BALOUP Marc TP3
*/

DROP SCHEMA IF EXISTS maroine_baloup_tp2 CASCADE;
CREATE SCHEMA maroine_baloup_tp2;
SET search_path to maroine_baloup_tp2;

DROP TABLE IF EXISTS Catalogue;
DROP TABLE IF EXISTS Articles;
DROP TABLE IF EXISTS Fournisseurs;

DROP TYPE IF EXISTS colors;
CREATE TYPE colors AS ENUM('rose','rouge','noir','argente','opaque','cyan','magenta','vert','superjaune', 'jaune');

CREATE TABLE Articles(
aid int PRIMARY KEY,                     
anom varchar(30) NOT NULL, /* Un article a forcément un nom*/ 
acoul colors NOT NULL /* Un article a forcément une couleur*/
);

CREATE TABLE Fournisseurs(
fid int PRIMARY KEY,
fnom varchar(30) NOT NULL, /* Un fournisseur a forcément un nom... */
fad varchar(70) NOT NULL /* ... et une adresse */
);

CREATE TABLE Catalogue(
fid int NOT NULL, /* Un article présent dans cette table a forcément un fournisseur */
aid int NOT NULL, /* Un fournisseur présent dans cette table a forcément un article */
prix numeric(8,2) NOT NULL CHECK(prix>=0), /* Un article a forcément un prix qui est supérieur à 0*/
UNIQUE(fid, aid), /* Une combinaison fournisseur article est unique*/
FOREIGN KEY (fid) REFERENCES Fournisseurs(fid)  /* Liaison aux fid de fournisseurs */
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (aid) REFERENCES Articles(aid) /* Laison aux aid de Articles*/
ON UPDATE CASCADE
ON DELETE CASCADE
);