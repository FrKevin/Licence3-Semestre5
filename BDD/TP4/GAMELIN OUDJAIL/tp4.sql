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
	\qecho ": Articles offerts par au moins 2 fournisseurs diff´erents (EXISTS,group)."
	SELECT a.*
	FROM articles a
	WHERE EXISTS (SELECT 1
				  FROM catalogue c
				  WHERE c.aid = a.aid
				  GROUP BY c.aid
				  HAVING count(c.aid) >= 2);
				 
-- Q1-5
	-- Tout les articles, avec toute les couleurs associé
	\qecho "Q1-5 : Vendeur offrant tous les articles (EXISTS)."
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
	\qecho "Q1-6 : Le nom du fournisseur de l’article le plus cher (EXISTS, S/A)."
	SELECT f.fnom
	FROM fournisseurs f
	WHERE EXISTS 
		(SELECT 1
		 FROM catalogue c1
		 WHERE c1.fid = f.fid and c1.prix >= ALL(SELECT c2.prix FROM catalogue c2)
		 );
		 
-- Q1-7
	\qecho "Q1-7 : Les noms des articles fournissables, avec prix maximal et minimal, uniquement pour les articles avec plus d’un fournisseur"
	SELECT a1.anom, min(c1.prix) as "prix_min", max(c1.prix) as "prix_max"
	FROM articles a1 NATURAL JOIN  catalogue c1
	WHERE EXISTS 
		(SELECT 1
		 FROM catalogue c2
		 WHERE c2.fid <> c1.fid and a1.aid = c2.aid
		)
	GROUP BY a1.anom;
	
--Q1-8
	\qecho "Q1-8 : Le nom du fournisseur offrant le meme article en plus d’une couleur, et le nom de cet article (EXISTS, S/A)."
	SELECT DISTINCT f1.fnom, a1.anom
	FROM articles a1 NATURAL JOIN catalogue c1 NATURAL JOIN fournisseurs f1
	WHERE EXISTS 
		(SELECT 1
		 FROM articles a2 NATURAL JOIN catalogue c2 NATURAL JOIN fournisseurs f2
		 WHERE f1.fid = f2.fid and a1.anom = a2.anom and a1.acoul <> a2.acoul
		);
		
-- Q1-9
	\qecho "Q1-9 : Le nombre d’articles offerts par le fournisseur avec le plus grand choix, et l’identifiant de ce fournisseur."
	SELECT c.fid, count(DISTINCT c.aid)
	FROM catalogue c
	GROUP BY c.fid
	HAVING count(DISTINCT c.aid) >= ALL(SELECT count(DISTINCT c2.aid)
										FROM catalogue c2
										GROUP BY c2.fid
									    );
					   
-- Q1-10
	\qecho "Q1-10 : Les noms des articles offerts par un seul fournisseur, toutes couleurs confondues (EXISTS, group by)."
	\qecho "Version EXISTS :"
	SELECT a1.anom
	FROM articles a1 NATURAL JOIN catalogue c1
	WHERE NOT EXISTS 
		(SELECT 1
		 FROM catalogue c2 NATURAL JOIN articles a2
		 WHERE a1.anom = a2.anom and c1.fid <> c2.fid
		);
		
	\qecho "Version GROUP BY :"
	SELECT a.anom
	FROM articles a NATURAL JOIN catalogue c
	GROUP BY a.anom
	HAVING count(DISTINCT c.fid) = 1;
	
--Q1-11
	\qecho "Q1-11 : Vendeur sans articles (EXISTS, IN, A/S,)."
	\qecho "Version EXISTS :"
	SELECT f.fnom
	FROM fournisseurs f
	WHERE NOT EXISTS
		(SELECT 1
		 FROM catalogue c
		 WHERE c.fid = f.fid);
		
	\qecho "Version IN :"		
	SELECT f.fnom
	FROM fournisseurs f
	WHERE f.fid NOT IN
		(SELECT c.fid
		 FROM catalogue c
		);
	
	\qecho "Version A/S :"
	SELECT f.fnom
	FROM fournisseurs f
	WHERE f.fid <> ALL
		(SELECT c.fid
		 FROM catalogue c
		);
		
--Q1-12
	\qecho "Q1-12 : Articles coutant au moins 100 euros, chez tous les vendeurs (comparaison au niveau des aids) (EXISTS, A/S, min)."
	\qecho "Version EXISTS :"	
	SELECT a.*
	FROM articles a
	WHERE NOT EXISTS
		(SELECT 1
		 FROM catalogue c
		 WHERE a.aid = c.aid and c.prix < 100
		);
	
	\qecho "Version A/S :"	
	SELECT a.*
	FROM articles a
	WHERE a.aid <> ALL
		(SELECT c.aid
		 FROM catalogue c
		 WHERE c.prix < 100
		);
		
	\qecho "Version min :"	
		SELECT a1.*
		FROM articles a1
	EXCEPT
		SELECT a2.*
		FROM articles a2
		WHERE a2.aid IN
			(SELECT c.aid
			 FROM catalogue c
			 WHERE c.prix < 100
			);
			
--Q1-13
	
	