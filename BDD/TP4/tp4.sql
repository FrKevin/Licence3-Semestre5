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
