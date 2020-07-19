#!/usr/bin/env bash
set -x -e -u

rm -f tlb_measure.dat
gcc -O0 -o measure  tlb_measuerment.c -lpthread 

pages=0

for i in {1..400}
do
    ./measure $pages
    pages=$((4 + $pages))
done

python3 plot.py