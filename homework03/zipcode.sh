#!/bin/sh

download_page () {
    curl -s http://www.zipcodestogo.com/${STATE}/
}

find_city () {
    grep -E "/$CITY/"
}

find_zipcodes () {
    grep -Eo "/[A-Z]{2}/[0-9]*/"
}

get_zip () {
    grep -Eo "[0-9]+" | sort | uniq
}

csv_it () {
    awk -vORS=, '{ print }' | sed "s/,$/\n/" 
}

STATE="Indiana"
CITY="empty"
FORMAT="text"
LIST="empty"
while [ $# -gt "0" ]; do
    if [ $1 = "-h" ]; then
        echo "Usage: zipcodes.sh"
        echo ""
        echo "  -c  CITY    Which city to search"
        echo "  -f  FORMAT  Which format (text, csv)"
        echo "  -s  STATE   Which state to search (Indiana)"
        exit 0
    elif [ $1 = "-c" ]; then
        CITY=$2
        shift
    elif [ $1 = "-f" ]; then
        FORMAT=$2
        shift
    elif [ $1 = "-s" ]; then
        STATE=$2
        shift
    fi
    shift
done

STATE=`echo $STATE | sed -r "s/ /%20/"`

if [ $FORMAT = "csv" ]; then
    if [ "$CITY" != "empty" ]; then
        download_page | find_city | find_zipcodes | get_zip | csv_it
    else 
        download_page | find_zipcodes | get_zip | csv_it
    fi
else
    if [ "$CITY" != "empty" ]; then
        download_page | find_city | find_zipcodes | get_zip
    else 
        download_page | find_zipcodes | get_zip
    fi
fi
