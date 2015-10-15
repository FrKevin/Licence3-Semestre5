set title "Temps et vitesse d'execution"
set logscale x
set xlabel "taille du buffer en octet"
set logscale y
set ylabel "temps d'exécution"
set style data linespoints
set term png
set output "mcat.png"
plot "time.dat" using 1:2 title "real", \
     "time.dat" using 1:3 title "user", \
     "time.dat" using 1:4 title "sys"
