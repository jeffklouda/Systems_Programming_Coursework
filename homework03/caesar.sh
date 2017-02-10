#!/bin/sh

if [ ${#} -gt 0 ]; then
    if [ ${1} = "-h" ]; then
        echo "Usage: caesar.sh [rotation]" 
        echo "This program will read from stdin and rotate (shift right) the text by the specified rotation.  If none is specified, then the default value is 13."
        exit 1
    else
        KEY=${1}
        KEY=`expr $KEY % 26`
    fi
else
    KEY="13"
fi

while read line; do
    for i in `seq 1 $KEY`; do
        line=`echo $line | tr [a-z] [b-za] | tr [A-Z] [B-ZA]`
    done
    echo $line
done
exit 0
