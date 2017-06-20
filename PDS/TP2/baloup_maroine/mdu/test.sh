#!/bin/bash

# Par Marc Baloup et Maxime Maroine
# Licence 3 Informatique - Lille 1
# 2015-2016


echo -n "création de dossiers de tests ... "
mkdir test_folder
mkdir test_folder/sub_test_folder
echo "ok"

echo -n "Création des fichiers ... "
touch test_folder/toto.txt
touch test_folder/tete.txt
touch test_folder/sub_test_folder/tata.txt
touch test_folder/sub_test_folder/titi.txt
echo "ok"

echo -n "Remplissage de fichiers ... "
echo "Ceci est un test" >> test_folder/toto.txt
echo "Ceci est un autre test" >> test_folder/sub_test_folder/titi.txt
echo "ok"

echo ""
echo "----- Liste des éléments du dossier de test -----"
ls -lR test_folder
echo "-------------------------------------------------"
echo ""
echo "------ Exécution des commandes classiques -------"
echo "-- ./mdu test_folder ----------------------------"
./mdu test_folder
echo "-- du -B512 test_folder -------------------------"
du -B512 test_folder
echo "-------------------------------------------------"
echo ""
echo "--------- Exécution des commandes avec ----------"
echo "-------- affichage des tailles apparent ---------"
echo "-- ./mdu -b test_folder -------------------------"
./mdu -b test_folder
echo "-- du -b test_folder ----------------------------"
du -b test_folder
echo "-------------------------------------------------"
echo ""
echo -n "Création de liens symboliques ..."
ln -s 2 test_folder/1
ln -s 1 test_folder/2
ln -s ../ test_folder/parentDir
echo "ok"
echo ""
echo "----- Exécution des commandes avec parcours -----"
echo "------------- des liens symboliques -------------"
echo "-- ./mdu -L test_folder -------------------------"
./mdu -L test_folder
echo "-- du -L -B512 test_folder ----------------------"
du -L -B512 test_folder
echo "-------------------------------------------------"
echo ""

echo -n "Suppression du dossier de tests ... "
rm -r test_folder
echo "ok"
echo "The end."
