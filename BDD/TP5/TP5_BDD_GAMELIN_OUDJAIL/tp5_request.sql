-- Q1
SELECT e.eid, e.enom, max(a.portee)
FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
GROUP BY e.eid
HAVING count(a.aid) >= 2;

--Q2
SELECT e.enom
FROM employes e NATURAL JOIN certifications c
WHERE e.salaire <=
      (SELECT min(v.prix)
       FROM vols v
       WHERE v.dep = 'CDG' and v.arr = 'NOU'
      );

--Q3
SELECT v.dep, v.arr, v.distance
FROM vols v
WHERE NOT EXISTS(
  SELECT 1
  FROM employes e NATURAL JOIN certifications c NATURAL JOIN avions a
  WHERE v.distance > a.portee and e.salaire < 100000
);

--Q4
