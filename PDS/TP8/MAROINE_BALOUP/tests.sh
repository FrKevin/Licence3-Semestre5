#!/bin/bash

# Par Marc Baloup et Maxime Maroine
# Licence 3 Informatique - Lille 1
# 2015-2016


echo "--- Préparation des fichiers pour compteur-gc ---"
for size in `awk 'BEGIN { for( i=1000; i<=10000000; i*=10 ) print i }'`; do
	echo "$size octets"
    ./aleazard $size > $size.adn
done
echo -n "" > gc_result.txt
echo "-------------------------------------------------"



echo "-------------- Test de compteur-gc --------------"
for size in `awk 'BEGIN { for( i=1000; i<=10000000; i*=10 ) print i }'`; do
	echo -n "Pour $size octets ..."
    for nbTh in `awk 'BEGIN { for( i=1; i<=10; i++ ) print i }'`; do
		echo -n "$size $nbTh " >> gc_result.txt
		nbTest=20
		sum=0
		for i in `awk 'BEGIN { for( i=1; i<=20; i++ ) print i }'`; do
			resTemp=`./compteur-gc $nbTh $size.adn c`
			sum=`echo $sum + $resTemp | bc -l`
		done
		
		echo "$sum / $nbTest" | bc -l >> gc_result.txt
    done
    echo " ok"
done
echo "Les résultats se trouvent dans gc_result.txt"
echo "-------------------------------------------------"



echo -n "Nettoyage des fichiers de tests pour compteur-gc ..."
rm *.adn
echo " ok"


