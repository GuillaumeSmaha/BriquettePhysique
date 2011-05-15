FILE="rapport.tex"

all: build

build:
	pdflatex $(FILE)
	
rebuild: clean
	pdflatex $(FILE)
	pdflatex $(FILE)

clean:
	rm -f *.aux
	rm -f *.glo
	rm -f *.ist
	rm -f *.lot
	rm -f *.lof
	rm -f *.log
	rm -f *.out
	rm -f *.toc
	rm -f *.pdf

