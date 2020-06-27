#!/usr/bin/env bash
set -x -e -u

rm -f tlb_measure.dat
gcc -O0 -o measure  tlb_measuerment.c

pages=0

for i in {1..500}
do
    ./measure $pages
    pages=$((1 + $pages))
done

python3 plot.py