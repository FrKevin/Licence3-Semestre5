-- Q1
	\qecho "Par article, le nombre de couleurs dans lequel cet article existe. Affichez les
				colonnes ARTICLE et NB_COUL, representant respectivement les noms d’articles et leur
				nombre de couleurs.'";
	SELECT  a.anom as Article, count(a.aid) as Nb_coul 
	FROM articles a  
	GROUP BY a.anom

-- Q2
	\qecho "Les noms des articles fournissables, avec par article le prix maximal et minimal,
				uniquement pour les articles avec plus d’un fournisseur. Indiquer pour chaque article, son
				nombre de fournisseurs. Ce nombre doit ˆetre deux pour le Acme Widget Washer.
				Trier par prix moyen d´ecroissant";
	SELECT anom as Articles, max(prix) as maxPrix, min(prix) as minPrix, count(fid) as Nb_fournisseurs
	FROM articles NATURAL JOIN catalogue 
	GROUP BY anom 
	Having count(*) > 1 
	ORDER BY prix DESC 

--Q3
	\qecho "Les couleurs \"rares\", pour lesquelles il n’y a qu’un seul article.";
	SELECT a.acoul as rares 
	FROM articles a 
	GROUP BY a.acoul 
	HAVING count(*) = 1 

--Q4
	\qecho "Par couleur, le prix moyen des articles. Il faut uniquement prendre en compte
				des couleurs, pour lesquelles plus d’un article est fournissable. De plus, il faut exclure la
				Ferrari. L’affichage des deux colonnes intitul´ees COULEUR et PRIX MOYEN doit se
				faire du prix moyen le plus ´elev´e, au prix moyen le plus bas.";
	SELECT acoul as Couleur, avg(prix) as prixMoyen
	FROM articles NATURAL JOIN catalogue
	WHERE aid <> 15
	GROUP BY anom, acoul
	ORDER By prixMoyen DESC
	
--Q5
	\qecho "Par article fournissable, et par couleur de l’article, le nombre de fournisseurs";
	SELECT anom as Article, acoul as Couleur, count(*) as Nb_fournisseurs
	FROM articles NATURAL JOIN catalogue
	GROUP BY acoul, anom
	
--Q6
	\qecho "Par article (toutes couleurs confondues), le nombre de fournisseurs. Il faut
				egalement inclure les articles n’ayant pas de fournisseur.";
	SELECT a.anom as Articles, count(f.fid) as Nb_Fournisseurs
	FROM articles a 
		LEFT JOIN catalogue c on a.aid = c.aid 
		LEFT JOIN fournisseurs f on f.fid = c.fid 
	Group by a.anom

--Q7
	\qecho "Les noms des fournisseurs (FOURNISSEUR), uniquement pour ceux offrant
				plus d’un article, et les nombres d’articles (NB_A). Si un article existe en plusieurs couleurs,
				il faut le compter comme un seul article. Aide : kiventout vend sept articles differents.";
	\qecho "1) on recupere tous les fournisseurs qui proposent des articles";
	SELECT * 
	FROM fournisseurs NATURAL JOIN catalogue NATURAL JOIN articles	
	\qecho "2) on peut remarquer que kiventout proposent deux articles avec le meme nom mais des couleur différentes.
		Il faut donc grouper par nom des fournisseurs et par articles";
	SELECT fnom as fournisseurs
	FROM fournisseurs NATURAL JOIN catalogue NATURAL JOIN articles 
	Group by fnom, anom
	\qecho "3) on compte par fournisseurs";
	SELECT t.fournisseurs, count(t.fournisseurs) as Nb_Articles
	FROM (
	SELECT fnom as fournisseurs, count(aid) as Nb_Articles
	FROM fournisseurs NATURAL JOIN catalogue  NATURAL JOIN articles
	Group By fid, anom
	   ) as t
	Group By t.fournisseurs
	
--Q8
