#!/bin/bash

rm ./report_jander_asam.log report_jander_asam.pdf report_jander_asam.toc report_jander_asam.dvi report_jander_asam.blg report_jander_asam.bbl report_jander_asam.aux;
pdflatex report_jander_asam.tex && pdflatex ./report_jander_asam.tex && acroread -openInNewInstance ./report_jander_asam.pdf
