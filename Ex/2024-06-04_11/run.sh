gcc sort.c -g -o sort

length="9999"
echo "----------------------Random Input----------------------"
echo $length" 2 1" | ./sort
echo $length" 2 2" | ./sort
echo $length" 2 3" | ./sort
echo $length" 2 4" | ./sort
echo $length" 2 5" | ./sort
echo $length" 2 6" | ./sort
echo $length" 2 7" | ./sort
echo $length" 2 8" | ./sort
echo "----------------------Orderd Input----------------------"
echo $length" 3 1" | ./sort
echo $length" 3 2" | ./sort
echo $length" 3 3" | ./sort
echo $length" 3 4" | ./sort
echo $length" 3 5" | ./sort
echo $length" 3 6" | ./sort
echo $length" 3 7" | ./sort
echo $length" 3 8" | ./sort
echo "----------------------Reversed Input---------------------"
echo $length" 4 1" | ./sort
echo $length" 4 2" | ./sort
echo $length" 4 3" | ./sort
echo $length" 4 4" | ./sort
echo $length" 4 5" | ./sort
echo $length" 4 6" | ./sort
echo $length" 4 7" | ./sort
echo $length" 4 8" | ./sort
rm sort