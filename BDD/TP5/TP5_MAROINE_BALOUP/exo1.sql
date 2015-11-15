\qecho Insertion des donénes dans le schéma "Vols"
\i TP5_create.sql
\qecho
\qecho Ajout terminé
\qecho

SET search_path to Vols;

\qecho
\qecho =========================
\qecho Question 1
\qecho =========================
\qecho

SELECT eid, max(portee)
FROM employes NATURAL JOIN certifications NATURAL JOIN avions
GROUP BY eid
HAVING count(aid) >= 2;

\qecho =========================
\qecho Question 2
\qecho =========================
\qecho

SELECT enom
FROM employes
WHERE salaire <= (SELECT min(prix)
FROM Vols
WHERE dep = 'CDG' AND arr = 'NOU');

\qecho =========================
\qecho Question 3
\qecho =========================
\qecho

SELECT dep, arr, distance
FROM Vols v
WHERE EXISTS(
  SELECT 1
  FROM employes e NATURAL JOIN certifications c NATURAL JOIN Avions a
  WHERE a.portee >= v.distance AND e.salaire > 100000
);

\qecho =========================
\qecho Question 4
\qecho =========================
\qecho

\qecho ----
\qecho  Réponse correspondante à la correction (ne respecte plus la vraie question)
\qecho ----

SELECT DISTINCT enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY eid
HAVING every(portee>1500) AND count(*) > 1
ORDER BY enom ASC;

\qecho ----
\qecho REQUÊTE ORIGINALE (au moins 1 avions)
\qecho ----

SELECT DISTINCT enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY eid
HAVING every(portee>1500)
ORDER BY enom ASC;

\qecho =========================
\qecho Question 5
\qecho =========================
\qecho

\qecho ----
\qecho  Réponse correspondante à la correction (ne respecte plus la vraie question)
\qecho ----

SELECT DISTINCT enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY eid
HAVING every(portee>1500) AND count(aid) > 2
ORDER BY enom ASC;

\qecho ----
\qecho REQUÊTE ORIGINALE (au moins 2 avion)
\qecho ----

SELECT DISTINCT enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY eid
HAVING every(portee>1500) AND count(aid) >= 2
ORDER BY enom ASC;

\qecho =========================
\qecho Question 6
\qecho =========================
\qecho

SELECT DISTINCT enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
WHERE EXISTS(
SELECT 1
FROM avions a2
WHERE anom like 'Boeing %'
)
GROUP BY eid
HAVING bool_and(portee>1500) AND bool_or(anom like 'Boeing%')
ORDER BY enom ASC;

\qecho =========================
\qecho Question 7
\qecho =========================
\qecho

SELECT enom, eid, salaire
FROM employes
ORDER BY salaire DESC
LIMIT 1 OFFSET 1;

\qecho !!! Laura (dans la correction) est la 3ème mieux payée !!!
\qecho

\qecho =========================
\qecho Question 8
\qecho =========================
\qecho

SELECT enom
FROM employes NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY eid
HAVING bool_or(portee>2000) AND bool_and(anom not like 'Boeing%');

\qecho =========================
\qecho Question 9
\qecho =========================
\qecho

\qecho REQUÊTE ORIGINAL
\qecho

SELECT enom
FROM employes
WHERE eid NOT IN (SELECT eid FROM certifications) AND salaire > (SELECT avg(salaire) FROM employes NATURAL JOIN certifications);

\qecho Meilleur salaire employes NON pilote
\qecho

SELECT enom, salaire FROM employes WHERE eid NOT IN(SELECT eid FROM certifications) ORDER BY salaire DESC LIMIT 1;

\qecho Revenu moyen des pilotes
\qecho

SELECT avg(salaire) FROM employes NATURAL JOIN certifications;


\qecho =========================
\qecho Question 10
\qecho =========================
\qecho

SELECT (SELECT avg(salaire) FROM employes NATURAL JOIN certifications) - (SELECT avg(salaire) FROM employes) as "Difference";

\qecho =========================
\qecho Question 11
\qecho =========================
\qecho

\qecho Timbuktu n existe pas dans la table...
\qecho


\qecho
\qecho
\qecho !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
\qecho La table utilisée dans la correction ne semble pas correspondre à la table de l exercice.
\qecho Certaines requêtes ont du être modifiées pour correspondre.
\qecho Le résultat original sera visible en dessous de celles-ci.
\qecho !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
\qecho
