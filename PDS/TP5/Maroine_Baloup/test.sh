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



echo -n "Définition de la variable globale pour les tests simples ... "
MCAT_BUFSIZ=1024
export MCAT_BUFSIZ
echo "ok"
echo ""




echo "----- Liste des éléments du dossier de test -----"
ls -lR test
echo "-------------------------------------------------"
echo ""



echo "--------- Exécution sur un fichier vide ---------"
echo "-- ./mcat test/vide -----------------------------"
./mcat test/vide
echo "-- cat test/vide --------------------------------"
cat test/vide
echo "-------------------------------------------------"
echo ""




echo "-------- Exécution sur un fichier texte ---------"
echo "-- ./mcat test/texte ----------------------------"
./mcat test/texte
echo "-- cat test/texte -------------------------------"
cat test/texte
echo "-------------------------------------------------"
echo ""


echo "------ Exécution des tests de performance -------"
echo "------- avec plusieurs tailles de buffer --------"
rm -f time.dat && echo "#buffsize real user sys" > time.dat

for size in `awk 'BEGIN { for( i=16; i<=8388608; i*=2 ) print i }'`; do
    export MCAT_BUFSIZ=$size
    echo -n "Test pour un buffer de $MCAT_BUFSIZ octets ... "
    /usr/bin/time -f "$MCAT_BUFSIZ %e %U %S" ./mcat test/bigdata > /dev/null 2>> time.dat
    echo "ok"
done

echo -n "Génération du graph ... "
gnuplot run.gnu
echo "ok"

echo "-------------------------------------------------"
echo ""




echo -n "Suppression du dossier de tests ... "
rm -r test
echo "ok"
echo "The end."
