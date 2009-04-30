set encoding iso_8859_1
set title "Número de octaves fixo"
set xlabel "Tempo (s)"
set ylabel "FPS"
set key outside below 
set datafile separator ";"
set terminal png
set output "teste2.png"
plot "teste2.csv" using 1:2 t"Terrenos vizinhos: 2" with linespoints 1, \
"teste2.csv" using 1:3 t"Terrenos vizinhos: 4" with linespoints 2, \
"teste2.csv" using 1:4 t"Terrenos vizinhos: 8" with linespoints 3