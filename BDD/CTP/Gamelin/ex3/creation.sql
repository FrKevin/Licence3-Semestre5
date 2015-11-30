#Q3.1
DROP TABLE IF EXISTS  play;
DROP TABLE IF EXISTS  joueur;
DROP TABLE IF EXISTS  jeux;

CREATE TABLE joueur(
	id serial primary key,
  nom varchar(30) NOT NULL,
	adresse varchar(30) NOT NULL
);

CREATE TABLE jeux(
	id serial primary key,
	nom varchar(30) NOT NULL
);

CREATE TABLE play(
	id_joueur serial,
	id_jeux serial,
  primary key(id_joueur, id_jeux)
);

ALTER TABLE play
	ADD CONSTRAINT fk_joueur_to_play FOREIGN KEY (id_joueur) REFERENCES joueur(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE;

ALTER TABLE play
	ADD CONSTRAINT fk_jeux_to_play FOREIGN KEY (id_jeux) REFERENCES jeux(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE;

#Q3.2
INSERT INTO jeux VALUES (0, 'War');
INSERT INTO jeux VALUES (1, 'Racing');
INSERT INTO jeux VALUES (2, 'Foot');
INSERT INTO jeux VALUES (3, 'Adventure');

INSERT INTO joueur VALUES (0, 'joueur1', 'Lille');
INSERT INTO joueur VALUES (1, 'joueur2', 'Lens');
INSERT INTO joueur VALUES (2, 'joueur3', 'Lille');
INSERT INTO joueur VALUES (3, 'joueur4', 'Lille');

INSERT INTO play VALUES (0, 0);
INSERT INTO play VALUES (0, 1);

INSERT INTO play VALUES (1, 2);
INSERT INTO play VALUES (1, 3);

INSERT INTO play VALUES (2, 3);
INSERT INTO play VALUES (2, 1);
INSERT INTO play VALUES (2, 0);

INSERT INTO play VALUES (3, 0);
INSERT INTO play VALUES (3, 3);
