#! /bin/bash

echo "--------- Creation des fichiers test --------"
mkdir test
touch test/text.txt
touch test/vide

echo "fhoshsdjvwjhvoiqhefbqbvjsiuhqzbejkfbohvbdjbsvoibfiozebufhn" >> test/text.txt
echo "qhoihfsh<fpcoshcjhsdvobiwhdoisvhfshicjshvidvjbwuoufsfe<oshicdsw" >> test/text.txt
echo "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" >> test/text.txt

# création d'un gros fichier de 30 Mio environ
echo "création d'un gros fichier de 130 Mio environ "
touch test/big
dd if=/dev/urandom of=test/big bs=131072 count=1000
echo "--------------------- OK --------------------"

echo -n "Définition de la variable globale pour les tests simples ... "
MCAT_BUFSIZ=1024
export MCAT_BUFSIZ
echo "ok"

echo ""


#Test sur un fichier vide
echo "---- Test: pour un fihcier vide ----"
echo "cat systeme"
cat test/vide
echo "notre cat"
./mcat test/vide
echo "------------------------------------"

echo ""

#Test sur un fichier avec texte
echo "---- Test: pour un fihcier avec texte ----"
echo "cat systeme"
cat test/text.txt
echo "notre cat"
./mcat test/text.txt
echo "------------------------------------"

echo ""

echo "------ Exécution des tests de performance, avec plusieurs tailles de buffer -------"
#On supprime si il existe deja le fichier .dat
rm -f time.dat && echo "#buffsize real user sys" > time.dat

for size in `awk 'BEGIN { for( i=1; i<=8388608; i*=2 ) print i }'`;
do
    export MCAT_BUFSIZ=$size
    echo -n "Test pour un buffer de $MCAT_BUFSIZ octets ... "
    /usr/bin/time -f "$MCAT_BUFSIZ %e %U %S" ./mcat test/big > /dev/null 2>> time.dat
    echo "ok"
done

echo -n "Génération du graph ... "
gnuplot run.gnu
echo ""
echo "--------------------------------------- OK -----------------------------------------"

echo ""

echo "---------------------------"
echo "Suppression du dossier test et du time.at"
rm -r test
rm time.dat
echo "----------- OK ------------"
