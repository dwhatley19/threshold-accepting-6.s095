#!/bin/bash
for i in `seq 204 400`;
do
	./tad 1500000 $1

	read line < "$1d.out" 
    	echo "$i: $line" >> "$1d_lengths.out"

	./cta "$1d.out" "$1d$i.asy"
	asy "$1d$i.asy"
done
