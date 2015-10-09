#! /bin/bash

# Par Kevin Gamelin et Veis Oudjail
# Licence 3 Informatique - Lille 1
# 2015-2016

make;


echo "Création et remplissage du dossier de test ... "
mkdir test
touch test/number_1_20


echo "1" >> test/number_1_20
echo "2" >> test/number_1_20
echo "3" >> test/number_1_20
echo "4" >> test/number_1_20
echo "5" >> test/number_1_20
echo "6" >> test/number_1_20
echo "7" >> test/number_1_20
echo "8" >> test/number_1_20
echo "9" >> test/number_1_20
echo "10" >> test/number_1_20
echo "11" >> test/number_1_20
echo "12" >> test/number_1_20
echo "13" >> test/number_1_20
echo "14" >> test/number_1_20
echo "15" >> test/number_1_20
echo "16" >> test/number_1_20
echo "17" >> test/number_1_20
echo "18" >> test/number_1_20
echo "19" >> test/number_1_20
echo "20" >> test/number_1_20

echo "----- Liste des éléments du dossier de test -----"
ls -lR test
echo "-------------------------------------------------"
echo ""


#Test tail sans paramètres
echo "----------------------------------"
echo "tail systeme normale (sans paramètre)";
tail test/number_1_20
echo "----------------------------------"
echo "notre tail (sans paramètre)"
./mtail test/number_1_20
echo "----------------------------------"

echo ""

#Test tail avec paramètres
echo "----------------------------------"
echo "tail systeme, argument -n 5";
tail test/number_1_20 -n 5
echo "----------------------------------"
echo "notre du tail, argument -n 5"
./mtail test/number_1_20 -n 5
echo "----------------------------------"

echo ""

#Test tail 0 ligne
echo "----------------------------------"
echo "tail systeme -n 0";
tail test/number_1_20 -n 0
echo "----------------------------------"
echo "notre du tail, argument -n 0"
./mtail test/number_1_20 -n 0
echo "----------------------------------"

echo ""

#Test tail nombre de ligne < 0
echo "----------------------------------"
echo "tail systeme -n -10";
tail test/number_1_20 -n -10
echo "----------------------------------"
echo "notre du tail, argument -n -10"
./mtail test/number_1_20 -n -10
echo "----------------------------------"

echo -n "Suppression du dossier de tests ... "
rm -r test
echo "ok"
echo "La fin."
