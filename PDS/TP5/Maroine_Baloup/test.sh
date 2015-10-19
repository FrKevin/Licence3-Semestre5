#!/bin/bash

# Par Marc Baloup et Maxime Maroine
# Licence 3 Informatique - Lille 1
# 2015-2016





echo "-------------- Exécution du multif --------------"
echo "-- ./multif -------------------------------------"
./multif
echo "-- ./multif 0 -----------------------------------"
./multif 0
echo "-- ./multif 12 ----------------------------------"
./multif 12
echo "-- ./multif 12 34 56 ----------------------------"
./multif 12 34 56
echo "-- ./multif 12 34 5 -----------------------------"
./multif 12 34 5
echo "-- ./multif a -----------------------------------"
./multif a
echo "-------------------------------------------------"
echo ""



echo "--------------- Exécution du race ---------------"
echo "-- ./race ---------------------------------------"
./race
echo "-------------------------------------------------"
echo ""



echo "The end."
