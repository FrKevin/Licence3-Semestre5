-- Q1
\qecho "Q1: Pour chaque pilote certié pour au moins deux avions, donnez l'eid et la portée maximale d'avion pour lesquels ce pilote est certiée."
SELECT e.eid, e.enom, max(a.portee)
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY e.eid
HAVING count(a.aid) >= 2;

--Q2
\qecho "Q2: Déeterminez les noms de pilotes dont le salaire est inférieur au prix du vol le moins cher de l'aéroport Paris-Charles de Gaulle (CDG) vers l'aéroport La Tontouta en Nouvelle Calédonie (NOU)."
SELECT e.enom
FROM employes e NATURAL JOIN certifications c
WHERE e.salaire <=
      (SELECT min(v.prix)
       FROM vols v
       WHERE v.dep = 'CDG' and v.arr = 'NOU'
      );

--Q3
\qecho "Q3: Quelles routes (départ et destination) peuvent ^etre volées par tous les pilotes gagnant plus de 100 000 euros ?"
SELECT v.dep, v.arr, v.distance
FROM vols v
WHERE NOT EXISTS(
  SELECT 1
  FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
  WHERE v.distance > a.portee and e.salaire < 100000
);

--Q4 every <=> bool_and retourne true si toutes les entrées sont validées
\qecho "Q4: Affichez les noms des pilotes qui sont uniquement certifiés pour des avions avec une portéé supérieure à 1500 km."
SELECT e.enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a 
GROUP By e.eid
HAVING every(a.portee > 1500);

--OU
\qecho "2e verssion"
SELECT DISTINCT(e.enom)
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a 
WHERE a.portee > 1500 and NOT EXISTS (
	SELECT 1
	FROM employes e2 NATURAL JOIN certifications c2 NATURAL JOIN avions a2
	WHERE e2.eid = e.eid and a2.portee <= 1500
);

--Q5
\qecho "Q5: Affichez les noms des pilotes qui sont uniquement certiés pour des avions avec une portée supérieure à 1500 km, pour au moins deux tels avions."
SELECT e.enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a 
GROUP By e.eid
HAVING every(a.portee > 1500) and count(aid) > 1;

--Q6 bool_or -> retourne true si une entré est vrai 
\qecho "Donnez les noms des pilotes qui sont certiés uniquement pour des avions d'une portée supérieure à 1500 km, et qui sont certiés pour au moins un type de Boeing."
SELECT DISTINCT enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY eid
HAVING every(portee>1500) AND bool_or(anom like 'Boeing%');

--Q7 
\qecho "Q7: Trouvez l'identifant de l'employé avec le salaire le deuxième plus haut."
SELECT *
FROM employes
ORDER BY salaire DESC
LIMIT 1 OFFSET 1;

--Q8
\qecho "Q8: Affichez les noms des pilotes qui peuvent piloter des avions d'une portèe supérieure à 2000km, mais qui ne sont certiés pour aucun Boeing."
SELECT DISTINCT enom
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY eid
HAVING bool_or(portee>2000) AND every(anom not like 'Boeing%');

--Q9
\qecho "Q9: Affichez les noms et revenus d'employés qui ne sont pas des pilotes, mais qui gagnent plus que le revenu moyen des pilotes."
SELECT e.enom
FROM employes e
WHERE e.eid NOT IN (
	SELECT c.eid
	FROM certifications c
) and e.salaire > (
	SELECT avg(e2.salaire)
	FROM employes e2 NATURAL JOIN certifications c2
);

--Q10
\qecho "Q10: Calculez la difference entre le revenu moyen de pilotes, et le revenu moyen de tous les employés (pilotes inclus)."
SELECT (
	SELECT avg(e.salaire)
	FROM employes e NATURAL JOIN certifications c 
) - (
	SELECT avg(e2.salaire)
	FROM employes e2
) as Différence;

--Q11
\qecho "Q11: "
\qecho "Timbuktu n existe pas dans la table..."
