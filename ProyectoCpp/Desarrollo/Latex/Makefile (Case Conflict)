# makefile for dvips

#text.dvi: text.tex
#	latex text.tex

#text.ps: text.dvi
#	dvips -Ppdf -G0 text.dvi
	# the -G0 fixes the ligature problem.

#text.pdf: text.ps
#	ps2pdf text.ps

#PDF: text.pdf
#	xpdf text.pdf

#### makefile for pdflatex ####

*.pdf: *.tex
	pdflatex *.tex

PDF: *.pdf
	okular *.pdf

#Al ejecutar make clean se borrarán todos los archivos compilados
clean:
	rm -f *.pdf && rm -f *.aux && rm -f *.dvi && rm -f *.log && rm -f *.nav && rm -f *.out && rm -f *.pdfsync && rm -f *.snm && rm -f *.syctex && rm -f *.toc && rm -f *.vrb && rm -f imagenes/*.pdf
