/*
MAROINE Maxime, BALOUP Marc TP3
*/

set search_path to maroine_baloup_tp2;

\qecho ------------------Question 1------------------
\qecho
SELECT acoul
FROM Articles a1
WHERE NOT EXISTS
(
SELECT 1
FROM Articles a2
WHERE a1.aid <> a2.aid AND a1.acoul = a2.acoul
);

\qecho ------------------Question 2------------------
\qecho
\qecho =====IN=====
SELECT anom
FROM Articles
WHERE acoul = 'rouge' AND anom NOT IN(SELECT anom FROM Articles WHERE acoul='vert');

\qecho =====SOME=====
SELECT anom
FROM Articles a1
WHERE acoul = 'rouge' AND NOT EXISTS(
SELECT 1
FROM Articles a2
WHERE acoul='vert' AND a1.anom = a2.anom);

\qecho =====ALL=====
SELECT anom
FROM Articles
WHERE acoul = 'rouge' AND anom <> ALL(
SELECT anom
FROM Articles
WHERE acoul='vert');

\qecho ------------------Question 3------------------
\qecho
\qecho =====Version groupe=====
SELECT fnom
FROM Fournisseurs f NATURAL JOIN Catalogue c NATURAL JOIN Articles a
WHERE acoul = 'rouge'
GROUP BY fid
HAVING max(c.prix) >= ALL(SELECT max(c2.prix)
FROM Catalogue c2
WHERE f.fid = c2.fid);

\qecho =====Version non groupée=====
SELECT fnom
FROM Fournisseurs f NATURAL JOIN Catalogue c NATURAL JOIN Articles a
WHERE c.prix = (SELECT max(c2.prix)
FROM Catalogue c2
WHERE f.fid = c2.fid AND a.acoul = 'rouge');

\qecho ------------------Question 4------------------
\qecho
\qecho GROUP BY
SELECT anom
FROM Articles NATURAL JOIN Catalogue
GROUP BY anom
HAVING count(*) > 1;

\qecho EXISTS

SELECT DISTINCT anom
FROM Articles a1 NATURAL JOIN Catalogue c1
WHERE EXISTS(SELECT 1
FROM Articles a2 NATURAL JOIN Catalogue c2
WHERE a1.anom = a2.anom AND c1.fid <> c2.fid);

\qecho ------------------Question 5------------------
\qecho
SELECT fnom
FROM Fournisseurs f
WHERE NOT EXISTS(SELECT 1
FROM Articles a
WHERE NOT EXISTS(SELECT 1
FROM Catalogue c
WHERE a.aid = c.aid AND c.fid = f.fid));

\qecho ------------------Question 6------------------
\qecho
\qecho Version ALL
SELECT fnom
FROM Fournisseurs f NATURAL JOIN Catalogue c
WHERE c.prix >= ALL(SELECT max(c2.prix) FROM Catalogue c2);

\qecho Version EXISTS
SELECT fnom
FROM Fournisseurs f
WHERE EXISTS(SELECT 1
FROM Catalogue c
WHERE c.fid = f.fid AND c.prix >= (
SELECT max(c2.prix)
FROM Catalogue c2));

\qecho ------------------Question 7-----------------
\qecho

SELECT anom, min(prix) as min, max(prix) as max
FROM Articles a NATURAL JOIN Catalogue c
WHERE EXISTS(SELECT 1
FROM Catalogue c2
WHERE a.aid = c2.aid AND c.fid <> c2.fid)
GROUP BY anom;

\qecho ------------------Question 8-----------------
\qecho

\qecho EXISTS
SELECT DISTINCT fnom, anom
FROM Fournisseurs f NATURAL JOIN Catalogue c NATURAL JOIN Articles a
WHERE EXISTS(SELECT 1
FROM Articles a2 NATURAL JOIN Catalogue c2
WHERE c.fid = c2.fid AND a.anom = a2.anom AND a.acoul <> a2.acoul);

\qecho SOME
SELECT DISTINCT fnom, anom
FROM Fournisseurs f NATURAL JOIN Catalogue c NATURAL JOIN Articles a
WHERE anom = SOME(SELECT a2.anom
FROM Articles a2 NATURAL JOIN Catalogue c2
WHERE a2.acoul <> a.acoul and c2.fid = f.fid);

\qecho ------------------Question 9-----------------
\qecho
SELECT fnom, count(*) as Nb_Articles
FROM Fournisseurs f NATURAL JOIN Catalogue c
GROUP BY f.fid
HAVING count(*) >= ALL(SELECT count(*)
FROM Catalogue c2
GROUP BY c2.fid);

\qecho ------------------Question 10-----------------
\qecho

\qecho Version GROUP BY
SELECT anom
FROM Catalogue NATURAL JOIN Articles
GROUP BY anom
HAVING count(*) = 1;

\qecho Version EXISTS
SELECT anom
FROM Catalogue c NATURAL JOIN Articles a
WHERE NOT EXISTS(SELECT 1
FROM Catalogue c2 NATURAL JOIN Articles a2
WHERE c2.fid <> c.fid and a.anom = a2.anom);

\qecho ------------------Question 11-----------------
\qecho

\qecho Version EXISTS
SELECT fnom
From Fournisseurs f NATURAL JOIN Catalogue c
WHERE NOT EXISTS(SELECT 1
FROM Articles a2
WHERE a2.aid = c.aid);


\qecho Version IN
SELECT fnom
FROM Fournisseurs f NATURAL JOIN Catalogue c
WHERE c.aid NOT IN(SELECT a.aid
FROM Articles a);

\qecho Version SOME
SELECT fnom
FROM Fournisseurs f NATURAL JOIN Catalogue c
WHERE f.fid = SOME(SELECT c2.fid
FROM Catalogue c2 NATURAL JOIN Articles a
GROUP BY c2.fid
HAVING count(*)<1);

\qecho ------------------Question 12-----------------
\qecho

\qecho Version EXISTS
SELECT DISTINCT anom
FROM Articles a
WHERE EXISTS(SELECT 1
FROM Catalogue c
WHERE a.aid = c.aid and c.prix > 100);

\qecho Version SOME
SELECT DISTINCT anom
FROM Articles a 
WHERE aid = SOME(SELECT c.aid
FROM Catalogue c
WHERE prix > 100);

\qecho Version min
(SELECT DISTINCT a.*
FROM Articles a NATURAL JOIN Catalogue c
EXCEPT
SELECT a2.*
FROM Catalogue c2 NATURAL JOIN Articles a2
WHERE c2.prix < 100);

\qecho ------------------Question 13-----------------
\qecho

SELECT aid
FROM Articles a
WHERE EXISTS(SELECT 1
FROM Catalogue c NATURAL JOIN Fournisseurs f
WHERE c.aid = a.aid AND f.fad like '%USA') AND NOT EXISTS(SELECT 1
FROM Catalogue c2 NATURAL JOIN Fournisseurs f2
WHERE c2.aid = a.aid AND f2.fad not like '%USA');