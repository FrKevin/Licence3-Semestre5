#! /bin/bash

mkdir test
touch test/tata.txt
mkdir test/home
mkdir test/bin
touch test/home/home.txt
touch test/bin/.lib
ln -s test/badLink1 test/badLink2
ln -s test/badLink2 test/badLink1

make

#Test taille
echo "----------------------------------"
echo "du systeme";
du test
echo ""
echo ""
echo "notre du"
./du_file test
echo "----------------------------------"

echo ""

#Teste taille avec affichage des sous-dossier
echo "----------------------------------"
echo "du systeme, argument -a";
du test -a
echo ""
echo ""
echo "notre du, argument -a"
./du_file test -a
echo "----------------------------------"

echo ""

#Traitement et affichage des sous-dossier pour les liens symbolique (envoie une erreur car il y a une boucle entre deux liens symbolque)
echo "----------------------------------"
echo "du systeme, argument -a -L";
du test -a -L
echo ""
echo ""
echo "notre du, argument -a"
./du_file test -a -L
echo "----------------------------------"

echo ""
rm test/badLink1
rm test/badLink2
ln -s test/tata.txt  test/lint_tata.txt
ln -s du_file.c test/link_du_file
#Traitement et affichage des sous-dossier pour les liens symbolique (aucune erreur)
echo "----------------------------------"
echo "du systeme, argument -a -L";
du test -a -L
echo ""
echo ""
echo "notre du, argument -a"
./du_file test -a -L
echo "----------------------------------"


echo "asaskzncjscjbkwxbcbsfibeiodjscjkdfiod<lniozhfhznfcjkbuibzdklnjosjdicqnscp<jihdznkqcspjizadnqkscpjihzdnqksc" > test/tata.txt
echo "Welcome" > test/home/home.txt
echo "azdfghjuytrdefgj" > test/bin/.lib
echo ""
#affichage du nombre de block des sous-dossiers et du dossier courant
echo "----------------------------------"
echo "du systeme, argument -B 1024 -a";
du test -B 1024 -a
echo ""
echo ""
echo "notre du, argument -B 1024 -a"
./du_file test -B 1024 -a
echo "----------------------------------"

rm -r test
