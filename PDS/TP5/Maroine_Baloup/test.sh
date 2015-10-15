#!/bin/bash

# Par Marc Baloup et Maxime Maroine
# Licence 3 Informatique - Lille 1
# 2015-2016


echo -n "Création et remplissage du dossier de test (peut prendre un moment à cause du gros fichier) ... "
mkdir test
touch test/vide
touch test/texte


echo "Lorem ipsum dolor sit amet, consectetur adipiscing." >> test/texte
echo "Phasellus tristique felis ut elit porttitor tempor." >> test/texte
echo "Pellentesque ut tortor rhoncus sapien faucibusi." >> test/texte
echo "Morbi ac augue ultricies, dignissim arcu nec, consequat." >> test/texte


echo "ok"
echo ""





echo "----- Liste des éléments du dossier de test -----"
ls -lR test
echo "-------------------------------------------------"
echo ""



echo "--------------- Exécution du race ---------------"
echo "-- ./race ---------------------------------------"
./race
echo "-------------------------------------------------"
echo ""



echo -n "Suppression du dossier de tests ... "
rm -r test
echo "ok"
echo "The end."
