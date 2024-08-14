#!/bin/bash
gcc sort.c -g -o sort
cat input_insert_sort.txt | ./sort
echo ""
cat input_bubble_sort.txt | ./sort

