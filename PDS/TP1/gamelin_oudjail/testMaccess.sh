#!/bin/bash

rm -r test/
mkdir test

# Test: erreur => L'un des composant du chemin d'acces n'existe pas ou est un liens symbolique pointant nulle part
echo "./maccess truc.txt\n"
echo "Affiche une erreur: L'un des composant du chemin d'acces n'existe pas ou est un liens symbolique pointant nulle part"
./maccess -r -v ./test/truc.txt
echo "\n"

#Test: Vous avez les droits
echo "./test/touch truc.txt\n"
touch ./test/truc.txt
echo "chmod u+r truc.txt\n"
chmod u+r truc.txt
echo "Affiche: Vous avez les droits\n"
./maccess -r ./test/truc.txt
echo "\n"

#Test: Vous ne possédez pas les droits
echo "chmod u-r ./test/truc.txt\n"
chmod u-r ./test/truc.txt
echo "Affiche: Vous ne possédez pas les droits\n"
./maccess -r ./test/truc.txt
echo "\n"

#Test: L'acces au fichier est refuse
echo "Affiche: L'acces au fichier est refuse\n"
./maccess -r -v ./test/truc.txt
echo "\n"

#Test Arguments invalides -v et -t
echo "./maccess truc.txt -r -v -w -r -v\n"
echo "Affiche Arguments invalides -v\n"
./maccess -r -v -w -v -x ./test/truc.txt
echo "Affiche Arguments invalides -t\n"
./maccess -r -t ./test/truc.txt
echo "\n"

#Test Le fichier pointe sur trop de liens symbolique
echo "touch ./test/tata.txt\n"
touch ./test/tata.txt
echo "touch ./test/toto.txt\n"
touch ./test/toto.txt
echo "ln -s ./test/tata.txt ./test/toto.txt\n"
ln -s ./test/tata.txt ./test/toto.txt
echo "ln -s ./test/tata.txt ./test/toto.txt\n"
echo "Affiche: Le fichier pointe sur trop de liens symbolique\n"
./maccess -r -v ./test/truc.txt
echo "\n"

#Test: Le pathname est trop long
echo "Affiche: Le pathname est trop long\n"
./maccess -r -v ./test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/../test/truc.txt
echo "\n"

#Test: L'un des elements du chemin d'acces n'est pas un repertoire
echo "touch dir\n"
touch dir
echo "Affiche: L'un des elements du chemin d'acces n'est pas un repertoire\n"
./maccess -r -v ./test/dir/truc.txt
echo "\n"

#Test: Erreur produite car demande d'écriture dans un fichier exécutable qui est en cours d'utilisation
echo "Affiche: Erreur produite car demande d'écriture dans un fichier exécutable qui est en cours d'utilisation\n"
./maccess -r -v ./test/testMaccess.sh
