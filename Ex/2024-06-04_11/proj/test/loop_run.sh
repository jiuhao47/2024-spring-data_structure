#!/bin/bash
gcc ../src/sort.c -g -o sort
loop_count=$1
count=$((loop_count+0))

filename="output"

for((input_mode=2;input_mode<5;input_mode++))
do
    for((sort_mode=1;sort_mode<9;sort_mode++))
    do
        length=1
        for((l=0;l<17;l++))
        do
            sum=0
            for((i=0; i<count; i++))
            do
                result=$(echo $length $input_mode $sort_mode | ./sort)
                sum=$(echo "$sum + $result" | bc)
            done
            average=$(echo "scale=7; $sum / $count" | bc)
            average=$(printf "%.7f" $average)
            mkdir -p ../output/output_$loop_count
            echo $average >> ../output/output_$loop_count/$filename"_"$input_mode"_"$sort_mode"_"$loop_count".txt"
            length=$(echo "$length * 2" | bc)
        done
        
    done
done


rm sort