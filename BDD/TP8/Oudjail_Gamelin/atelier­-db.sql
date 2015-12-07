DROP TABLE IF EXISTS machine CASCADE;
DROP TABLE IF EXISTS composer CASCADE;
DROP TABLE IF EXISTS piece CASCADE;
DROP TYPE IF EXISTS fournisseur CASCADE;
DROP TYPE IF EXISTS commande CASCADE;
DROP TYPE IF EXISTS client CASCADE;

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
	id serial primary key,
	date_prevue date NOT NULL,
	quantite_demande INTEGER NOT NULL,
	id_machine INTEGER,
	id_client INTEGER
);

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
