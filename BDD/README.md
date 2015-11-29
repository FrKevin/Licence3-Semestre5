###Important:
  
  activation de votre base de donnée a l'aide http://intranet.fil.univ-lille1.fr

###Login

  psql -h webtp
  mot de passe de login

  
###Commandes utiles
	
	Pour charger un fichier \d file.sql
	
###Commandes lancement RA
	Par rapport à l'énoncé qui nous est fournie, les commandes sont les suivantes (à faire à partir de TP1) :
	- export CLASSPATH=$CLASSPATH:aql.jar
	- rlwrap java edu.gsu.cs.ra.RA boutique

###RA
	project <=> Select
	select <=> WHERE 
	* <=> NATURAL JOIN
	
	Exemples:
	
	project[fnom](fournisseurs);
	<=> équivalent:
		Select fnom
		FROM fournisseurs
	
	select[fad='Paris'](fournisseurs);
	<=> équivalent:
		Select *
		FROM fournisseurs
		WHERE fad='Paris'
		
	project[fid](select[prix > 10 AND prix < 20](catalogue));
	<=> équivalent:
	Select fid
	FROM catalogue
	WHERE prix > 10 AND prix < 20
	
