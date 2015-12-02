# configuration du graph
set logscale x
set dgrid3d 10,7
set pm3d

# enregistrement sous forme d'image PNG
set term png
set output "gc_result.png"
splot "gc_result.txt" using 1:2:3 with lines

# affichage du graphique dans une fenêtre interactive
set term wxt
splot "gc_result.txt" using 1:2:3 with lines
