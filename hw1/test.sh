#!/bin/bash
g++ $1 -o a.out
while :
do
    python3 generator.py > test.in
    ./a.out < test.in > test.out
    if [ `cat test.out | grep -c "\-1"` -gt 0 ]
    then
        echo "failed"
        break
    else
        echo "success"
    fi
done
