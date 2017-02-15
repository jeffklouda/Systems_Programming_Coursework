set terminal png
set xrange [2012:2020]
set yrange [0:100]
set grid
set key left
set style data histogram
set style fill solid border
set boxwidth 0.075
set xtics 2012,1,2019
set xlabel 'Class'
set ylabel 'Students'

plot	'ethnic.dat' using ($1-0.25):2 title "Caucasian" with boxes,\
	'ethnic.dat' using ($1-0.15):3 title "Asian" with boxes,\
	'ethnic.dat' using ($1-0.05):4 title "Hispanic" with boxes,\
	'ethnic.dat' using ($1+0.05):5 title "African" with boxes,\
	'ethnic.dat' using ($1+0.15):6 title "Native" with boxes,\
	'ethnic.dat' using ($1+0.25):7 title "Multiple" with boxes,\
	'ethnic.dat' using ($1+0.35):8 title "Undeclared" with boxes
