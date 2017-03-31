#!/bin/sh

# benchmark.sh

# echo "| NITEMS   | SORT     | TIME     | SPACE    |"
# echo "| -------- | -------- | -------- | -------- |"

for num in 1 10 100 1000 10000 100000 1000000 10000000; do
    echo  "|" $num "|" "Merge" "|"
    shuf -i1-$num -n $num | ./measure ./lsort -n | grep -Eo "\d+\.\d{2}"
    echo  "|" $num "|" "Quick" "|"
    shuf -i1-$num -n $num | ./measure ./lsort -n -q | grep -Eo "\d+\.\d{2}"
done

