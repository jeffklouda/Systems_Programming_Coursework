#!/bin/sh

# ethnic.sh

URL=https://www3.nd.edu/~pbui/teaching/cse.20289.sp17/static/csv/demographics.csv

count_ethnic() {
    column=	# TODO: Determine appropriate column from first argument
    ethnic=	# TODO:	Ethnic group is second argument
    # TODO extract ethnic data for specified year and group
}

for year in $(seq 2013 2018); do
    echo $year $(count_ethnic $year C) \
    	       $(count_ethnic $year O) \
    	       $(count_ethnic $year S) \
    	       $(count_ethnic $year B) \
    	       $(count_ethnic $year N) \
    	       $(count_ethnic $year T) \
    	       $(count_ethnic $year U)
done
