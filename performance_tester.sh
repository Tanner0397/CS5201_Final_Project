#!/usr/bin/env bash


INT_DIVS=10
FINAL_DIVS=30
NUM_RUNS=20

for (( i=INT_DIVS; i<=FINAL_DIVS; i++ ))
do
  ./driver $i $NUM_RUNS 0 > "cholesky/$i.txt"
  ./driver $i $NUM_RUNS 1 > "gauss/$i.txt"
done
