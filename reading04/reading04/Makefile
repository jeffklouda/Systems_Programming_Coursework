all:	reading04.pdf

gender.dat:	gender.sh
	./gender.sh > gender.dat

gender.png:	gender.plt gender.dat
	gnuplot < gender.plt > gender.png

ethnic.dat:	ethnic.sh
	./ethnic.sh > ethnic.dat

ethnic.png:	ethnic.plt ethnic.dat
	gnuplot < ethnic.plt > ethnic.png

reading04.pdf:	reading04.tex gender.png ethnic.png
	pdflatex reading04.tex
	pdflatex reading04.tex

clean:
	rm -f gender.dat ethnic.dat gender.png ethnic.png reading04.pdf reading04.log reading04.aux reading04.out
