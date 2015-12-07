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
  ('ascenseur', 42, (select id from fournisseur where nom = 'XX') ),
