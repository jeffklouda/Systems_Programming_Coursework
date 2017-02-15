#!/bin/sh

# gender.sh

URL=https://www3.nd.edu/~pbui/teaching/cse.20289.sp17/static/csv/demographics.csv

count_gender() {
    column=$((1 + ( ${1} - 2013 ) * 2)) # find column number based on year
    gender=${2} # take gender as second argument
    
    # extract gender data for specified year and group
    curl -s $URL | cut -d , -f $column | grep $gender | wc -l
}

for year in $(seq 2013 2019); do
    echo $year $(count_gender $year F) $(count_gender $year M)
done
