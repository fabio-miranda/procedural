set encoding iso_8859_1
set title "Número de terrenos vizinhos fixo"
set xlabel "Tempo (s)"
set ylabel "FPS"
set key outside below 
set datafile separator ";"
set terminal png
set output "teste1.png"
plot "teste1.csv" using 1:2 t"Octaves: 4" with linespoints 1, \
"teste1.csv" using 1:3 t"Octaves: 16" with linespoints 2, \
"teste1.csv" using 1:4 t"Octaves: 32" with linespoints 3