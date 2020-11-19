#!/bin/bash


'rw' 'ph' 'pc'

filename="measuresrw"

echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./"$filename".csv

for i in 2 4 8 16
do

    echo -n "$i" > ./"$filename".csv
    for j in 1 2 3 4 5
    do
    
        make clean
        make rw
        cTime=$(/usr/bin/time -f "%e" ./rw -R $i/2 -W $i/2 | tail -n 1) >&-
        echo -n ",$cTime" > ./"$filename".csv
    
    done
    echo -n "\n" > ./"$filename".csv
done

filename="measuresph"

echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./"$filename".csv

for i in 1 2 4 8 16
do

    echo -n "$i" > ./"$filename".csv
    for j in 1 2 3 4 5
    do
    
        make clean
        make ph
        cTime=$(/usr/bin/time -f "%e" ./ph -P $i | tail -n 1) >&-
        echo -n ",$cTime" > ./"$filename".csv
    
    done
    echo -n "\n" > ./"$filename".csv
done

filename="measurespc"

echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./"$filename".csv

for i in 2 4 8 16
do

    echo -n "$i" > ./"$filename".csv
    for j in 1 2 3 4 5
    do
    
        make clean
        make pc
        cTime=$(/usr/bin/time -f "%e" ./pc -P $i/2 -C $i/2 | tail -n 1) >&-
        echo -n ",$cTime" > ./"$filename".csv
    
    done
    echo -n "\n" > ./"$filename".csv
done


SQUISH_NO_CAPTURE_OUTPUT=0
