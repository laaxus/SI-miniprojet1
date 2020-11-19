#!/bin/bash

filename="measurespc"

echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./"$filename".csv

for i in 2 4 8 16
do

    echo -n "$i" >> ./"$filename".csv
    for j in 1 2 3 4 5
    do
    
        make clean
        make pc
        cTime=$(/usr/bin/time -f "%e" ./pc -P $i/2 -C $i/2 | tail -n 1) 
        #echo "$cTime"
        echo -n ",$cTime" >> ./"$filename".csv
    
    done
    echo -n "\n" >> ./"$filename".csv
done


