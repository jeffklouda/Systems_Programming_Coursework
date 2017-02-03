#!/bin/sh

while [ ${#} -gt -0 ] 
do
    ./jklouda1.lockbox ${1}
   
    shift
done
