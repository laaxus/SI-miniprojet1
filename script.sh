#!/bin/bash
{
    filename="measuresrw"

    echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./Measures/"$filename".csv

    for i in 2 4 8 16
    do

        echo -n "$i" >> ./Measures/"$filename".csv
        for j in 1 2 3 4 5
        do
        
            make clean
            make rw
            cTime=$(/usr/bin/time -f "%e" ./rw -R $i/2 -W $i/2 2>&1)
            echo -n ",$cTime" >> ./Measures/"$filename".csv
        
        done
        echo "" >> ./Measures/"$filename".csv
    done

    filename="measuresph"

    echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./Measures/"$filename".csv

    for i in 2 4 8 16
    do

        echo -n "$i" >> ./Measures/"$filename".csv
        for j in 1 2 3 4 5
        do
        
            make clean
            make ph
            cTime=$(/usr/bin/time -f "%e" ./ph -N $i 2>&1)
            echo -n ",$cTime" >> ./Measures/"$filename".csv
        
        done
        echo "" >> ./Measures/"$filename".csv
    done

    filename="measurespc"

    echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./Measures/"$filename".csv

    for i in 2 4 8 16
    do

        echo -n "$i" >> ./Measures/"$filename".csv
        for j in 1 2 3 4 5
        do
        
            make clean
            make pc
            cTime=$(/usr/bin/time -f "%e" ./pc -P $i/2 -C $i/2 2>&1) 
            echo -n ",$cTime" >> ./Measures/"$filename".csv
        
        done
        echo "" >> ./Measures/"$filename".csv
    done
} &> /dev/null