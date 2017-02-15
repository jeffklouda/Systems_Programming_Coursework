set terminal png
set xrange [2012:2020]
set yrange [0:100]
set grid
set key left
set style data histogram
set style fill solid border
set boxwidth 0.40
set xtics 2012,1,2019
set xlabel 'Class'
set ylabel 'Students'

plot	'gender.dat' using ($1-0.2):2 title "Females" with boxes,\
	'gender.dat' using ($1+0.2):3 title "Males" with boxes
