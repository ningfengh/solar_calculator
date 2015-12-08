set terminal postscript enhanced color font 'Helvetica,18'
set output 'spectra.eps'
set title "Reflection and Transmission Spectra"
set xlabel "Wavelength (nm)"
set ylabel "R/T"
plot "my_eqe.txt" using 1:2 title 'reflection' with lines, \
"my_eqe_fine.txt" using 1:2  title 'transmission'with dots



