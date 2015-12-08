set terminal postscript enhanced color font 'Helvetica,18'
set output 'map.eps'
set title "EQE"
set xlabel "Wavelength (nm)"
set ylabel "Theta"

set pm3d
set palette
set pm3d map
set palette defined ( 0 '#000090',\
                      1 '#000fff',\
                      2 '#0090ff',\
                      3 '#0fffee',\
                      4 '#90ff70',\
                      5 '#ffee00',\
                      6 '#ff7000',\
                      7 '#ee0000',\
                      8 '#7f0000')
splot "my_eqe.txt" matrix 



