#!/bin/bash

# Par Marc Baloup et Maxime Maroine
# Licence 3 Informatique - Lille 1
# 2015-2016





echo "---------- Exécution de la commande do ----------"
echo "-- ./do true ------------------------------------"
./do true; echo "exit $? (attendu : 0)"
echo "-- ./do false -----------------------------------"
./do false; echo "exit $? (attendu : 1)"
echo "-- ./do false false -----------------------------"
./do false false; echo "exit $? (attendu : 1)"
echo "-- ./do false true ------------------------------"
./do false true; echo "exit $? (attendu : 1)"
echo "-- ./do true true -------------------------------"
./do true true; echo "exit $? (attendu : 0)"
echo "-- ./do -a false true ---------------------------"
./do -a false true; echo "exit $? (attendu : 1)"
echo "-- ./do -o false true ---------------------------"
./do -o false true; echo "exit $? (attendu : 0)"
echo "-- ./do -a xterm false (fermeture de xterm nécessaire pour afficher le résultat)"
./do -a xterm false; echo "exit $? (attendu : 1)"
echo "-- ./do -ac xterm false -------------------------"
./do -ac xterm false; echo "exit $? (attendu : 1 sans attendre la fermeture de xterm)"
echo "-- ./do -ack xterm false ------------------------"
./do -ack xterm false; echo "exit $? (attendu : 1 et kill automatique de xterm)"
echo "-------------------------------------------------"
echo ""




echo "The end."
