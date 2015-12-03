#!/bin/bash

# Par Marc Baloup et Maxime Maroine
# Licence 3 Informatique - Lille 1
# 2015-2016


echo "--- Préparation des fichiers pour compteur-gc ---"
for size in `awk 'BEGIN { for( i=1000; i<=1000000000; i*=10 ) print i }'`; do
	echo "$size octets :"
	./aleazard $size > $size.adn
	echo " ok"
done
echo -n "" > resultat.dat
echo "-------------------------------------------------"



echo "-------------- Test de compteur-gc --------------"
for size in `awk 'BEGIN { for( i=1000; i<=1000000000; i*=10 ) print i }'`; do
	echo -n "Pour $size octets ..."
    for nbTh in `awk 'BEGIN { for( i=1; i<=32; i*=2 ) print i }'`; do
		echo -n "$size $nbTh " >> resultat.dat
		echo -n " $nbTh"
		nbTest=5
		sum=0
		for i in `awk 'BEGIN { for( i=1; i<=5; i++ ) print i }'`; do
			resTemp=`./compteur-gc $nbTh $size.adn c`
			sum=`echo $sum + $resTemp | bc -l`
		done
		
		echo "$sum / $nbTest" | bc -l >> resultat.dat
    done
    echo " ok"
done


echo -n "Affichage du graph ... "
gnuplot -persist run.gnu
echo "ok"

echo "-------------------------------------------------"



echo -n "Nettoyage des fichiers de tests pour compteur-gc ..."
rm *.adn
echo " ok"


