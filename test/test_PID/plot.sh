#!/bin/bash

rm *.png

for csv in `ls *.csv`
do
    echo "Create: "
    base=`basename $csv .csv`
    echo " - "$base
    echo " - "$csv
    img=$base".png"
    echo " - "$img

    plotstr='set datafile separator ";" ; set title "'$base'" ; set term png ; set output "'$img'" ; plot "'$csv'" using 1:2 with lines title "Value", "'$csv'" using 1:3 with lines title "Setpoint", "'$csv'" using 1:4 with lines title "Output"'

    #echo $plotstr
    echo $plotstr | gnuplot &
    echo
done

echo "Done"
exit 0
