# configuration du graph
set logscale x
set logscale y
set dgrid3d 6,7
set pm3d

# enregistrement sous forme d'image PNG
set term png
set output "resultat.png"
splot "resultat.dat" using 1:2:3 with lines

# affichage du graphique dans une fenêtre interactive
set term wxt
splot "resultat.dat" using 1:2:3 with lines
