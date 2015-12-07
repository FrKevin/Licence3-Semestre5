-- Requete 5
-- Q1
\qecho "Q1: Afficher les noms et prix des machines produites par l’atélier (résultat attendu: Presse à 35000 euros, Moissonneuse­-batteuse – 50000 euros)"
SELECT m.nom, m.prix
FROM machine m;

-- Q2
\qecho "Q2: Afficher, pour les fournisseurs des pièces roues, leurs noms et villes (résultat attendu: MultiRoues de Tourcoing)"
SELECT f.nom, f.nom_ville
FROM fournisseur f JOIN piece p ON p.id_fournisseur = f.id;

-- Q3
