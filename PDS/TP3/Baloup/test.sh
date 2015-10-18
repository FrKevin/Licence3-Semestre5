#!/bin/bash

# Par Marc Baloup et Maxime Maroine
# Licence 3 Informatique - Lille 1
# 2015-2016


echo -n "création et remplissage du dossier de test ... "
mkdir test
touch test/vide
touch test/petit
touch test/grand


echo "Lorem ipsum dolor sit amet, consectetur adipiscing elit." >> test/grand
echo "Phasellus tristique felis ut elit porttitor tempor." >> test/grand
echo "Pellentesque ut tortor rhoncus sapien faucibus lobortis id eget dui." >> test/grand
echo "Morbi ac augue ultricies, dignissim arcu nec, consequat massa." >> test/grand
echo "Suspendisse pellentesque est eu lorem sagittis, id pulvinar nulla mollis." >> test/grand
echo "Donec convallis sem eget nunc ultricies, sed porttitor eros lobortis." >> test/grand
echo "Mauris volutpat velit vehicula, consectetur orci quis, vestibulum sapien." >> test/grand
echo "" >> test/grand
echo "Vivamus lobortis risus in lectus finibus auctor." >> test/grand
echo "Vestibulum tincidunt lacus in vestibulum sollicitudin." >> test/grand
echo "Pellentesque dictum eros vel volutpat imperdiet." >> test/grand
echo "Aenean sed nibh quis arcu congue dignissim." >> test/grand
echo "Nam sit amet mauris in lorem dictum ultricies at." >> test/grand
echo "Fusce accumsan sapien sodales sem ultrices, sit amet." >> test/grand
echo "Maecenas ut risus quis mi gravida molestie." >> test/grand
echo "Vivamus feugiat magna facilisis erat suscipit ornare." >> test/grand
echo -n "Donec feugiat risus id mi imperdiet sagittis." >> test/grand

# fichier qui fini par un retour à la ligne
cp test/grand test/grand_with_nl
echo "" >> test/grand_with_nl




echo "Lorem ipsum dolor sit amet, consectetur adipiscing." >> test/petit
echo "Phasellus tristique felis ut elit porttitor tempor." >> test/petit
echo "Pellentesque ut tortor rhoncus sapien faucibusi." >> test/petit
echo "Morbi ac augue ultricies, dignissim arcu nec, consequat." >> test/petit



echo "ok"
echo ""




echo "----- Liste des éléments du dossier de test -----"
ls -lR test
echo "-------------------------------------------------"
echo ""




echo "-- Exécution des commandes sur le fichier vide --"
echo "-- ./mtail -n 3 test/vide -----------------------"
./mtail -n 3 test/vide
echo "-- ./mtail_stupide -n 3 test/vide ---------------"
./mtail_stupide -n 3 test/vide
echo "-- tail -n 3 test/vide --------------------------"
./mtail -n 3 test/vide
echo "-------------------------------------------------"
echo ""




echo "-- Exécution des commandes sur un petit fichier -"
echo "-- ./mtail -n 6 test/petit ----------------------"
./mtail -n 6 test/petit
echo "-- ./mtail_stupide -n 6 test/petit --------------"
./mtail_stupide -n 6 test/petit
echo "-- tail -n 6 test/petit -------------------------"
./mtail -n 6 test/petit
echo "-------------------------------------------------"
echo ""




echo "-- Exécution des commandes sur un grand fichier -"
echo "-- ./mtail -n 8 test/grand ----------------------"
./mtail -n 8 test/grand
echo "-- ./mtail_stupide -n 8 test/grand --------------"
./mtail_stupide -n 8 test/grand
echo "-- tail -n 8 test/grand -------------------------"
./mtail -n 8 test/grand
echo "-------------------------------------------------"
echo ""




echo "-- Exécution des commandes sur un grand fichier -"
echo "-- Avec un retour à la ligne en fin de fichier --"
echo "-- ./mtail -n 8 test/grand_with_nl --------------"
./mtail -n 8 test/grand_with_nl
echo "-- ./mtail_stupide -n 8 test/grand_with_nl ------"
./mtail_stupide -n 8 test/grand_with_nl
echo "-- tail -n 8 test/grand_with_nl -----------------"
./mtail -n 8 test/grand_with_nl
echo "-------------------------------------------------"
echo ""




echo -n "Suppression du dossier de tests ... "
rm -r test
echo "ok"
echo "The end."
