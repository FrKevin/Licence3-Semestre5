DROP TABLE IF EXISTS Articles CASCADE;
DROP TABLE IF EXISTS fournisseurs CASCADE;
DROP TABLE IF EXISTS catalogue CASCADE;
DROP TYPE IF EXISTS colors CASCADE;

CREATE TYPE colors as ENUM('rouge','noir','argente','opaque','cyan','magenta','vert','superjaune', 'rose');

CREATE TABLE Articles(
	aid serial primary key,                     
	anom varchar(30) NOT NULL, 
	acoul colors NOT NULL
);

CREATE TABLE Catalogue(
	fid bigint,   
	aid bigint, 
	prix numeric(8,2) NOT NULL,
	primary key(fid, aid)
);

CREATE TABLE Fournisseurs(
	fid serial primary key,
	fnom varchar(30) NOT NULL,
	fad varchar(70) NOT NULL
);

ALTER TABLE Catalogue 
	ADD CONSTRAINT fk_Catalogue_to_Articles FOREIGN KEY (aid) REFERENCES Articles(aid) 
	ON DELETE CASCADE 
	ON UPDATE CASCADE;
	
ALTER TABLE Catalogue 
	ADD CONSTRAINT fk_Catalogue_to_Fournisseurs FOREIGN KEY (fid) REFERENCES Fournisseurs(fid) 
	ON DELETE CASCADE 
	ON UPDATE CASCADE;
	
ALTER TABLE Catalogue
	ADD CONSTRAINT prix_catalogue_positive
	CHECK (prix>0);
