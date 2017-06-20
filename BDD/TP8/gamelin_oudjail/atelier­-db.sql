DROP TABLE IF EXISTS machine CASCADE;
DROP TABLE IF EXISTS composer CASCADE;
DROP TABLE IF EXISTS piece CASCADE;
DROP TYPE IF EXISTS fournisseur CASCADE;
DROP TYPE IF EXISTS commande CASCADE;
DROP TYPE IF EXISTS client CASCADE;


-- Creation des tables
CREATE TABLE machine(
	id serial primary key,
	nom varchar(255) NOT NULL,
	prix numeric(8,2) NOT NULL,
	description varchar(1000)
);

CREATE TABLE fournisseur(
	id serial primary key,
	nom varchar(255) NOT NULL,
	numero_rue varchar(255) NOT NULL,
	nom_rue varchar(255) NOT NULL,
	nom_ville varchar(255) NOT NULL,
	code_ville varchar(255) NOT NULL,
	numero_tel varchar(255) NOT NULL,
	numero_fax varchar(255) NOT NULL,
);

CREATE TABLE client(
	id serial primary key,
	nom varchar(255) NOT NULL
);

CREATE TABLE piece(
	id serial primary key,
	nom varchar(255) NOT NULL,
	nb_exemplaire INTEGER NOT NULL,
	id_fournisseur INTEGER NOT NULL
);

CREATE TABLE composer(
	id_machine INTEGER,
	id_piece INTEGER,
	quantite_piece INTEGER NOT NULL,
	primary key(id_machine, id_piece)
);

CREATE TABLE commande(
	id_machine INTEGER,
	id_client INTEGER,
	date_prevue date NOT NULL,
	quantite_demande INTEGER NOT NULL,
	primary key(id_machine, id_client, date_prevue)
);

-- Insertion des données
INSERT INTO machine(nom, prix)
  VALUES
  ('Presse', 35000),
  ('Moissonneuse-­batteuse', 50000);

INSERT INTO fournisseur(nom, numero_rue, nom_rue, nom_ville, code_ville, numero_tel, numero_fax)
  VALUES
  ('Recharges Agricoles', 'XX', 'XX', 'Boulogne', '62200', 'XX', 'XX'),
  ('MultiRoues', 'XX', 'XX', 'Tourcoing', '59200', 'XX', 'XX'),
  ('Pouce Vert', 'XX', 'XX', 'Lille', '59000', 'XX', 'XX');

INSERT INTO client(nom)
  VALUES
  ('Chicorée'),
	('Mecanique Lucien'),
	('Saponnier'),
  ('Gremise');

INSERT INTO piece(nom, nb_exemplaire, id_fournisseur)
  VALUES
  ('arbre', 42, (select id from fournisseur where nom = 'Recharges Agricoles') ),
  ('deroulements', 42, (select id from fournisseur where nom = 'MultiRoues') ),
  ('embrayages', 42, (select id from fournisseur where nom = 'Recharges Agricoles') ),
  ('roues', 42, (select id from fournisseur where nom = 'MultiRoues') ),
  ('structure primaire', 42, (select id from fournisseur where nom = 'MultiRoues') ),
  ('van', 42, (select id from fournisseur where nom = 'XX') ),
  ('batteur', 42, (select id from fournisseur where nom = 'XX') ),
  ('ascenseur', 42, (select id from fournisseur where nom = 'XX') );


INSERT INTO composer(id_machine, id_piece, quantite_piece)
	VALUES
	((select id from machine where nom = 'Presse'), (select id from piece where nom = 'arbre'), 1),
	((select id from machine where nom = 'Presse'), (select id from piece where nom = 'deroulements'), 10),
	((select id from machine where nom = 'Presse'), (select id from piece where nom = 'embrayages'), 4),
	((select id from machine where nom = 'Presse'), (select id from piece where nom = 'roues'), 4),
	((select id from machine where nom = 'Presse'), (select id from piece where nom = 'structure primaire'), 1),
	((select id from machine where nom = 'Moissonneuse-batteuse'), (select id from piece where nom = 'van'), 1),
	((select id from machine where nom = 'Moissonneuse-batteuse'), (select id from piece where nom = 'batteur'), 1),
	((select id from machine where nom = 'Moissonneuse-batteuse'), (select id from piece where nom = 'ascenseur'), 1),
	((select id from machine where nom = 'Moissonneuse-batteuse'), (select id from piece where nom = 'roues'), 4),
	((select id from machine where nom = 'Moissonneuse-batteuse'), (select id from piece where nom = 'structure primaire'), 1);


INSERT INTO commande(id_machine, id_client, date_prevue, quantite_demande)
	VALUES
	((select id from machine where nom = 'Presse'), (select id from client where nom = 'Mecanique Lucien'), '2016/03/15', 15),
	((select id from machine where nom = 'Presse'), (select id from client where nom = 'Saponnier'), '2016/03/30', 50),
	((select id from machine where nom = 'Presse'), (select id from client where nom = 'Chicorée'), '2016/04/30', 15),
	((select id from machine where nom = 'Moissonneuse-batteuse'), (select id from client where nom = 'Chicorée'), '2016/04/30', 30),
	((select id from machine where nom = 'Moissonneuse-batteuse'), (select id from client where nom = 'Gremise'), '2016/05/20', 1);



-- Ajout des contraintes
ALTER TABLE piece
	ADD CONSTRAINT fk_piece_to_fournisseur FOREIGN KEY (id_fournisseur) REFERENCES fournisseur(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE;

ALTER TABLE composer
	ADD CONSTRAINT fk_composer_to_machine FOREIGN KEY (id_machine) REFERENCES machine(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE;

ALTER TABLE composer
	ADD CONSTRAINT fk_composer_to_piece FOREIGN KEY (id_piece) REFERENCES piece(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE;

ALTER TABLE commande
	ADD CONSTRAINT fk_commande_to_machine FOREIGN KEY (id_machine) REFERENCES machine(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE;

ALTER TABLE commande
	ADD CONSTRAINT fk_commande_to_client FOREIGN KEY (id_client) REFERENCES client(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE;
