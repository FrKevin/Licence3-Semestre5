set title "Temps et vitesse d'execution"
set logscale x
set xlabel "taille en lignes"
set logscale y
set ylabel "temps en s ou vitesse en octets/s"
set style data linespoints
plot "ex2.dat" using 1:2 title "temps", \
     "ex2.dat" using 1:3 title "vitesse"
