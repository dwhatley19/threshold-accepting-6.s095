#!/bin/bash
g++ deterministic_ta.cpp -o main
for i in `seq 1 400`;
do
	./main $i $1

	read line < "$1.out" 
    	echo "$i: $line" >> "$1_lengths.out"

	./cta "$1.out" "$1$i.asy"
	asy "$1$i.asy"
done
