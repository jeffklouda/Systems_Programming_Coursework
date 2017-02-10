#!/bin/sh

DELIM="#"
STRIP="1"

while [ $# -gt "0" ]; do
    if [ $1 = "-h" ]; then
        echo "Usage: broify.sh"
        echo ""
        echo "  -d DELIM    Use this as the comment delimiter."
        echo "  -W          Don't strip empty lines."
        exit 0
    elif [ $1 = "-d" ]; then
        DELIM=$2
        shift
    elif [ $1 = "-W" ]; then
        STRIP=0
    fi
    shift
done

if [ $STRIP = 1 ]; then
    sed -r "s|${DELIM}.*||" | sed -r "s|\s+$||" | sed -r "/^$/d"
else 
    sed -r "s|${DELIM}.*||" | sed -r "s|\s+$||"
fi
