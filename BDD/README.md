### Important:

  Activation de votre base de donnée a l'aide http://intranet.fil.univ-lille1.fr

### Login

  psql -h webtp
  mot de passe de login


### Commandes utiles

	Pour charger un fichier \i file.sql

### Commandes lancement RA

	Par rapport à l'énoncé qui nous est fournie, les commandes sont les suivantes (à faire à partir de TP1) :
	- export CLASSPATH=$CLASSPATH:aql.jar
	- rlwrap java edu.gsu.cs.ra.RA boutique

### Datalog
/home/enseign/DES/des

### RA
	project <=> SELECT
	select <=> WHERE
	minus <=> NOT IN

	Exemples:

	project[fnom](fournisseurs);
	<=> équivalent:
		SELECT fnom
		FROM fournisseurs

	select[fad='Paris'](fournisseurs);
	<=> équivalent:
		SELECT *
		FROM fournisseurs
		WHERE fad='Paris'

	project[fid](select[prix > 10 AND prix < 20](catalogue));
	<=> équivalent:
	SELECT fid
	FROM catalogue
	WHERE prix > 10 AND prix < 20

	Donner les noms d’articles rouges ou verts.
	project[anom](select[acoul='rouge'](articles)) union project[anom](select[acoul='vert'](articles))
	SELECT anom
	FROM articles
	WHERE acoul='rouge'
	UNION
	SELECT anom
	FROM articles
	WHERE acoul='vert'

	Donner la liste des articles fournissables, avec les prix auxquels ils sont offerts et le nom du fournisseur correspondant.
	project[anom, prix, fnom](articles join catalogue join fournisseurs);
	SELECT anom, prix, fnom
	FROM articles NATURAL JOIN catalogue NATURAL JOIN fournisseurs

	Quels fournisseurs offrent uniquement des articles à plus de 10000 euros ?
	(project[fid](catalogue))
		minus
	(project[fid](select[prix<10000](catalogue)));
	<=>
	SELECT fid
	FROM catalogue
	WHERE fid NOT IN(
		SELECT fid
		FROM catalogue
		WHERE prix<10000
	)
