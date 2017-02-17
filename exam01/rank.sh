#!/bin/sh

# rank.sh

DESCEND=0
ITEMS=5

usage() {
    cat <<EOF
Usage: $(basename $0)

    -n N        Returns N items (default is 5).
    -D          Rank in descending order.
EOF
    exit $1
}

rank() {
    if [ $DESCEND -eq 0 ] ; then
        sort -n
    else 
        sort -rn
    fi
}

while [ $# -gt 0 ] ; do
    case $1 in
        -n) ITEMS=$2 shift;;
        -N) ITEMS=$2 shift;;
        -D) DESCEND=1;;
        *)  usage 0;;
    esac
    shift
done

rank | head -n $ITEMS
