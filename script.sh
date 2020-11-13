#!/bin/bash

SQUISH_NO_CAPTURE_OUTPUT=1

for file in 'rw' 'ph' 'pc'
    do

    filename="measures"
    filename+="$file"

    echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./"$filename".csv

    for i in 1 2 4 8 16
    do

        echo -n "$i" > ./"$filename".csv
        for j in 1 2 3 4 5
        do
        
            make clean
            cTime=$(/usr/bin/time -f "%e" make -"$file" $i 2>&1 | tail -n 1)
            echo -n ",$cTime" > ./"$filename".csv
        
        done
        echo -n "\n" > ./"$filename".csv
    done
done

SQUISH_NO_CAPTURE_OUTPUT=0
