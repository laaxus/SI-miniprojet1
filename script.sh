#!/bin/bash
echo "Warning! This execution might take up to 5 mins, 
as it tries to gather significant data for all algorithms.
You can always check for its advancement in the 'Measures'
directory as the files '.csv' grow one at a time."
{
    #create_csv() is a function that will compute the command passed as argument 5 times
    #with N threads (N ranging from 1 to 8) and will store the result in a file
    # $1 is the filename
    # $2 is the command to call from the MakeFile
    # $3 is the first MakeFile command argument
    # $4 is the second MakeFile command argument (optionnal)
    # /!\ à mettre -R ou -C dans $3, car ils sont prioritaires

    create_csv() {
        echo "NB_THREADS,TIME_1,TIME_2,TIME_3,TIME_4,TIME_5" > ./Measures/"$1".csv

        for i in 1 2 3 4 5 6 7 8
        do

            echo -n "$i" >> ./Measures/"$1".csv
            for j in 1 2 3 4 5
            do
                
                make clean
                make $2
                
                if [ $3 = "-N" ]
                then
                    cTime=$(/usr/bin/time -f "%e" ./"$2" "$3" $i 2>&1)
                else
                    if [ $((i%2)) -eq 0 ]
                    then
                        cTime=$(/usr/bin/time -f "%e" ./"$2" "$3" $i/2 "$4" $i/2 2>&1)
                    else
                        cTime=$(/usr/bin/time -f "%e" ./"$2" "$3" $i/2+1 "$4" $i/2 2>&1)
                    fi
                fi

                echo -n ",$cTime" >> ./Measures/"$1".csv
            
            done
            echo "" >> ./Measures/"$1".csv
        done
    }
    
    create_csv MeasuresRW rw -R -W
    create_csv MeasuresPH ph -N
    create_csv MeasuresPC pc -C -P
    create_csv MeasuresTS ts -N
    create_csv MeasuresTTS tts -N
    create_csv MeasuresRW2 rw2 -R -W
    create_csv MeasuresPH2 ph2 -N
    create_csv MeasuresPC2 pc2 -C -P
    chmod +x graphing.py

} &> /dev/null
./graphing.py
