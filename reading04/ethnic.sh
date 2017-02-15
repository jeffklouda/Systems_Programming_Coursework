#!/bin/sh

# ethnic.sh

URL=https://www3.nd.edu/~pbui/teaching/cse.20289.sp17/static/csv/demographics.csv

count_ethnic() {
    # Determine appropriate column from first argument
    column=$((2 + (${1} - 2013) * 2))
    # Ethnic group is second argument
    ethnic=${2}
  
    # extract ethnic data for specified year and group
    curl -s $URL | cut -d , -f $column | grep $ethnic | wc -l
}

for year in $(seq 2013 2019); do
    echo $year $(count_ethnic $year C) \
    	       $(count_ethnic $year O) \
    	       $(count_ethnic $year S) \
    	       $(count_ethnic $year B) \
    	       $(count_ethnic $year N) \
    	       $(count_ethnic $year T) \
    	       $(count_ethnic $year U)
done
