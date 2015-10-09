#! /bin/bash
make;

#Test tail sans paramètres
echo "----------------------------------"
echo "tail systeme normale (sans paramètre)";
tail test/number.txt
echo ""
echo "notre tail (sans paramètre)"
./mtail test/number.txt
echo "----------------------------------"

echo ""

#Test tail avec paramètres
echo "----------------------------------"
echo "tail systeme, argument -n 5";
tail test/number.txt -n 5
echo ""
echo "notre du tail, argument -n 5"
./mtail test/number.txt -n 5
echo "----------------------------------"

echo ""

#Test tail 0 ligne
echo "----------------------------------"
echo "tail systeme -n 0";
tail test/number.txt -n 0
echo ""
echo "notre du tail, argument -n 0"
./mtail test/number.txt -n 0
echo "----------------------------------"


#Test tail nombre de ligne < 0
echo "----------------------------------"
echo "tail systeme -m -10";
tail test/number.txt -n -10
echo ""
echo "notre du tail, argument -n -10"
./mtail test/number.txt -n -10
echo "----------------------------------"
