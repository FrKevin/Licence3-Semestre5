-- Q1-1
	\qecho "Q1-1 : Les couleurs rares, c’est a dire pour lesquelles il n’y existe que un seul article de cette couleur (EXISTS).";
	SELECT a1.*
	FROM articles a1
	WHERE NOT EXISTS (SELECT 1
					  FROM articles a2
					  WHERE a1.aid <> a2.aid and a1.acoul = a2.acoul);
					  

-- Q1-2
	\qecho "Q1-2 : Articles rouges, qui n’existent pas en vert (EXISTS, A/S,IN).";
	\qecho "Version EXISTS :";
	SELECT a1.*
	FROM articles a1
	WHERE cast(a1.acoul as VARCHAR) = 'rouge' 
		and NOT EXISTS (SELECT 1
						FROM articles a2
						WHERE a1.anom = a2.anom and cast(a2.acoul as VARCHAR) = 'vert');
						
	\qecho "Version A/S :";
	SELECT a1.*
	FROM articles a1
	WHERE cast(a1.acoul as VARCHAR) = 'rouge' 
	 and 'vert' <> all(SELECT cast(a2.acoul as VARCHAR)
					   FROM articles a2
					   WHERE a1.anom = a2.anom);
					   
	
	\qecho "Version IN :";
	SELECT a1.*
	FROM articles a1
	WHERE cast(a1.acoul as VARCHAR) = 'rouge' 
		and a1.anom not in (SELECT a2.anom	
							FROM articles a2	
							WHERE cast(a2.acoul as VARCHAR) = 'vert');
							
	
-- Q1-3
	\qecho ": Ecrivez une requete qui donne le nom des fournisseurs dont l’article le plus cher est rouge.";
	\qecho ": Version group by"
	SELECT f.fnom
	FROM catalogue c1 NATURAL JOIN articles a NATURAL JOIN fournisseurs f
	WHERE cast(a.acoul as VARCHAR) = 'rouge'
	GROUP BY f.fid
	HAVING max(c1.prix) = (SELECT max(c2.prix)
						   FROM catalogue c2
						   WHERE f.fid = c2.fid);
						   
	\qecho ": Version sans group by"					   
	SELECT f.*
	FROM catalogue c1 NATURAL JOIN articles a NATURAL JOIN fournisseurs f
	WHERE c1.prix = (select max(c2.prix)
					 from catalogue c2
					 where c1.fid = c2.fid) and cast(a.acoul as VARCHAR) = 'rouge';
					 
	
-- Q1-4
	SELECT a.*
	FROM articles a
	WHERE EXISTS (SELECT 1
				  FROM catalogue c
				  WHERE c.aid = a.aid
				  GROUP BY c.aid
				  HAVING count(c.aid) >= 2);
				 
-- Q1-5
	-- Tout les articles, avec toute les couleurs associé
	SELECT f.*
	FROM fournisseurs f
	WHERE NOT EXISTS 
		(SELECT 1
		 FROM articles a
		 WHERE NOT EXISTS
			(SELECT 1
			 FROM catalogue c jo
			 WHERE c.fid = f.fid and c.aid = a.aid 
			)
		);
		
-- Q1-6
	SELECT f.fnom
	FROM fournisseurs f
	WHERE EXISTS 
		(SELECT 1
		 FROM catalogue c1
		 WHERE c1.fid = f.fid and c1.prix >= ALL(SELECT c2.prix FROM catalogue c2)
		 );
		 
-- Q1-7
	SELECT a1.anom, min(c1.prix) as "prix_min", max(c1.prix) as "prix_max"
	FROM articles a1 NATURAL JOIN  catalogue c1
	WHERE EXISTS 
		(SELECT 1
		 FROM catalogue c2
		 WHERE c2.fid <> c1.fid and a1.aid = c2.aid
		)
	GROUP BY a1.anom;
	
--Q1-8

	SELECT DISTINCT f1.fnom, a1.anom
	FROM articles a1 NATURAL JOIN catalogue c1 NATURAL JOIN fournisseurs f1
	WHERE EXISTS 
		(SELECT 1
		 FROM articles a2 NATURAL JOIN catalogue c2 NATURAL JOIN fournisseurs f2
		 WHERE f1.fid = f2.fid and a1.anom = a2.anom and a1.acoul <> a2.acoul
		);
		
-- Q1-9

	SELECT c.fid, count(DISTINCT c.aid)
	FROM catalogue c
	GROUP BY c.fid
	HAVING count(DISTINCT c.aid) >= ALL(SELECT count(DISTINCT c2.aid)
										FROM catalogue c2
										GROUP BY c2.fid
									    );
					   
-- Q1-10

	SELECT a.anom
	FROM articles a NATURAL JOIN catalogue c1
	WHERE NOT EXISTS
		(SELECT 1
		 FROM catalogue c
		 WHERE a.aid = c.aid
		 GROUP BY c.aid
		 HAVING count(DISTINCT c.fid) > 1
		);
	