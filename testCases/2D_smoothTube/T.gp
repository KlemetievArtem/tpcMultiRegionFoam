reset
set term x11 0
set title ""
set ylabel 'Outer Wall Temperature in K'
set xlabel 'Time in s'
plot 'postProcessing/tube/patchAverage/0/surfaceFieldValue.dat' title '' with lines, \
 
 
pause 100
reread

