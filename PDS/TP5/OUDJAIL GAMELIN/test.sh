#! /bin/bash

echo "------------------ Testmultif ------------------"
echo "avec un argument: le résultat est 0"
./multif 1
echo "avec un argument: le résultat est 1"
./multif 11
echo "avec deux arguments: le résultat est 0"
./multif 11 0
echo "avec deux arguments: le résultat est 1"
./multif 11 12
echo "------------------------------------------------"

echo ""

echo "------------------ Testrace --------------------"
for i in `seq 1 4`;
do
  echo "Course n° $i: "
  echo "Resultat:"
  ./race
  echo ""
done
echo "------------------------------------------------"

echo ""

echo "Observation de processus"
echo "Q2: "
echo " Utilisez la commande kill pour terminer les processus fils. > les fils ne sont plus excecuter."
echo "Que se passe-t-il si vous tuez le processus père ? > Les processus fils sont récuperer par le père du père et sont toujour en exécution."
