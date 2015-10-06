-- 2-1
	\qecho "Trouver les noms de fournisseurs. Dans le résultat, renommez l'attribut 'fnom' en 'fournisseur'";
-- ALL :
	\qecho "ALL :";
	select fnom as fournisseur from fournisseurs;
-- Catalogue :
	\qecho "Catalogue :";
	select distinct fnom as fournisseur from fournisseurs natural join catalogue;

-- 2-2
	\qecho "Donner les noms des fournisseurs parisiens.";
-- ALL :
	\qecho "ALL : ";
	select fnom as fournisseur from fournisseurs where fad like '%Paris';
-- Catalogue : 
	\qecho "Catalogue :";
	select distinct fnom as fournisseur from fournisseurs natural join catalogue where fad like '%Paris';

-- 2-3
	\qecho "Trouver les noms de fournisseurs d'articles à moins de 20 euros.";
	SELECT DISTINCT f.fnom as fournisseur
	FROM fournisseurs as f NATURAL JOIN catalogue c 
	WHERE  c.prix < 20;
	
-- 2-4
	\qecho "Quels fournisseurs offrent des articles entre 10 et 20 euros ? Proposez deux requetes avec differentes techniques, dont une operation ensembliste 2 Veillez a ce quechaque fid n'apparaisse qu'une seule fois.";
	\qecho "Requete classique :";
	SELECT DISTINCT f.fnom as fournisseur 
	FROM fournisseurs as f NATURAL JOIN catalogue c 
	WHERE  c.prix < 20 and c.prix > 10;
-- OR 
	\qecho "Requete ensembliste :";
	SELECT DISTINCT f.fnom as fournisseur 
	FROM fournisseurs as f NATURAL JOIN catalogue c 
	WHERE  c.prix < 20
INTERSECT
	SELECT DISTINCT f.fnom as fournisseur
	FROM fournisseurs as f NATURAL JOIN catalogue c 
	WHERE  c.prix  >10;

-- 2-5
	\qecho "Donner les noms d'articles rouges ou verts a moins de 20 euros.";
	SELECT a.anom as "Article"
	FROM articles a NATURAL JOIN catalogue c
	WHERE a.acoul = 'rouge' or a.acoul = 'vert' and c.prix < 20;

-- 2-6
	\qecho "Enumerer les noms des articles fournissables, premierement, a l'aide d'une jointure naturelle, puis avec une jointure interne, et finalement, avec un produit cartesien.";
	-- NATURAL JOIN
	\qecho "Requete natural join :";
	SELECT DISTINCT a.anom as "Article"
	FROM articles a NATURAL JOIN catalogue c;
	
	-- INNER JOIN
	\qecho "Requete inner join :";
	SELECT DISTINCT a.anom as "Article"
	FROM articles a JOIN catalogue c ON c.aid = a.aid;
	
	-- TIMES JOIN
	\qecho "Requete times join :";
	SELECT DISTINCT a.anom as "Article"
	FROM articles as a, catalogue as c
	WHERE a.aid = c.aid;
	
-- 2-7
	\qecho "Donnez les identifiants de fournisseurs d'articles rouges.";
	SELECT DISTINCT c.fid 
	FROM catalogue c  NATURAL JOIN articles a
	WHERE a.acoul = 'rouge';

-- 2-8
	\qecho "Donnez les noms et adresses des fournisseurs proposant uniquement des articles a plus de 1000 euros.";
	SELECT f.fnom, f.fad 
	FROM fournisseurs f 
	WHERE f.fid NOT IN ( 
		SELECT c.fid 
		FROM catalogue c 
		WHERE c.prix < 1000
	);

-- 2-9
	\qecho "Lister toutes les combinaisons possibles d'un article vert avec un article rouge.";
	SELECT * 
	FROM articles a1, articles a2
	WHERE a1.acoul = 'vert' and a2.acoul = 'rouge';
	
-- 2-10
	\qecho "Identifiez les articles non fournissables en utilisant une jointure externe, et donnez les noms. Pour les DUTs : Donnez deux requetes alternatives, une avec une sous-requete avec IN, l'autre EXISTS.";
	-- OUTTER JOIN :
	\qecho "Requete jointure externe :";
	SELECT a.anom
	FROM articles a left join catalogue c ON c.aid = a.aid
	WHERE c.aid IS NULL;
	
	-- REQUEST IN : 
	\qecho "Sous requete :";
	SELECT a.anom 
	FROM articles a 
	WHERE a.aid not in ( 
		SELECT c.aid 
		FROM catalogue c
	);
	
	-- REQUEST EXISTS :
	\qecho "Requete exists :";
	SELECT a.anom 
	FROM articles a
	WHERE NOT EXISTS (
		SELECT 1
		FROM catalogue c
		WHERE a.aid = c.aid
	);

-- 2-11
	\qecho "Trouver les identifiants des fournisseurs qui fournissent aussi bien des articles rouges que des articles verts.";
	SELECT DISTINCT f.fid 
	FROM fournisseurs f NATURAL JOIN Catalogue c NATURAL JOIN articles a  
	WHERE a.acoul = 'rouge' or a.acoul = 'vert';

-- 2-12
	\qecho "Trouver les noms des fournisseurs qui n'offrent ni des articles noirs, ni des articles argentees.";
	SELECT fnom
	FROM fournisseurs
	WHERE fid not in ( 
		SELECT f.fid 
		FROM fournisseurs f NATURAL JOIN Catalogue c NATURAL JOIN articles a 
		WHERE a.acoul = 'noir' or a.acoul = 'argente'
	);
